#include "IntegrationWindow.hpp"

//--- Standard includes --------------------------------------------------------
#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>

//--- Implementation -----------------------------------------------------------
#include "IntegratorEuler.h"
#include "IntegratorEulerImproved.h"
#include "IntegratorHeun.h"
#include "IntegratorRK3.h"
#include "IntegratorRK4.h"
#include "IntegratorRK5.h"
#include "IntegratorRKF4.h"
#include "IntegratorADB2.h"
#include "IntegratorADB3.h"
#include "IntegratorADB4.h"
#include "IntegratorADB5.h"

using namespace gfx;


IntegrationWindow::Point::Point(double a_x,
                                double a_y,
                                double a_vx,
                                double a_vy,
                                double a_err)
  :x(a_x)
  ,y(a_y)
  ,vx(a_vx)
  ,vy(a_vy)
  ,err(a_err)
{}

//------------------------------------------------------------------------
IntegrationWindow::IntegrationWindow(int width, int height)
  :SDLWindow(width, height)
  ,m_event()
  ,m_Model(0.4)
  ,m_vIntegrator()
  ,m_vResults()
  ,m_dt(0.015)
  ,m_xTrace(1)
  ,m_yTrace(1)
{
  m_vIntegrator.push_back(new IntegratorRK5(&m_Model, m_dt));

//  m_vIntegrator.push_back(new IntegratorEuler(&m_Model, m_dt*0.2));
//  m_vIntegrator.push_back(new IntegratorEulerImproved(&m_Model, m_dt));
//  m_vIntegrator.push_back(new IntegratorHeun(&m_Model, m_dt));
//  m_vIntegrator.push_back(new IntegratorRK3(&m_Model, m_dt));
//  m_vIntegrator.push_back(new IntegratorRK4(&m_Model, m_dt));
//  m_vIntegrator.push_back(new IntegratorRK5(&m_Model, m_dt));
//  m_vIntegrator.push_back(new IntegratorRKF4(&m_Model, m_dt));
//  m_vIntegrator.push_back(new IntegratorADB2(&m_Model, m_dt));
//  m_vIntegrator.push_back(new IntegratorADB3(&m_Model, m_dt));
//  m_vIntegrator.push_back(new IntegratorADB4(&m_Model, m_dt));
//  m_vIntegrator.push_back(new IntegratorADB5(&m_Model, m_dt));

  m_vResults.assign(m_vIntegrator.size(), -1);

  unsigned ct=0;

  // Euler/heun
  m_aColors[ct++] = Color(50, 50, 50);
  m_aColors[ct++] = Color(100, 100, 100);
  m_aColors[ct++] = Color(200, 200, 200);

  // RK/RKF
  m_aColors[ct++] = Color(0,   100, 0);
  m_aColors[ct++] = Color(0,   150, 0);
  m_aColors[ct++] = Color(0,   255, 0);
  m_aColors[ct++] = Color(255, 255, 0);

  // Adams-Moulton
  m_aColors[ct++] = Color(0, 100, 100);
  m_aColors[ct++] = Color(0, 150, 150);
  m_aColors[ct++] = Color(0, 200, 200);
  m_aColors[ct++] = Color(0, 250, 250);
}

//------------------------------------------------------------------------
void IntegrationWindow::Init(double x, double y, double vx, double vy)
{
  double state[4] = { vx, vy, x, y};
  for (std::size_t i=0; i<m_vIntegrator.size(); ++i)
    m_vIntegrator[i]->SetInitialState(state);
}

//------------------------------------------------------------------------
const IntegrationWindow::result_type& IntegrationWindow::Calculate(double xstart, double ystart, bool bDumpFile = false)
{
  double state[4] = { 0, 0, xstart, ystart};
  for (std::size_t i=0; i<m_vIntegrator.size(); ++i)
    m_vIntegrator[i]->SetInitialState(state);

  trace_type vTrace;
  vTrace.reserve(1000);

  SDL_FillRect(Surface(), NULL, 0);

  for (std::size_t i=0; i<m_vIntegrator.size(); ++i)
  {
    vTrace.clear();
    m_vResults[i] = -1;

    for (std::size_t len=0; len<100000; ++len)
    {
      m_vIntegrator[i]->SingleStep();
      double *state = m_vIntegrator[i]->GetState();
      double x  = state[2],    y = state[3],
             vx = state[0],   vy = state[1];
      vTrace.push_back( Point(x, y, vx, vy, 0) );
      if (m_Model.IsFinished(state))
      {
        m_vResults[i] = m_Model.GetStopIdx();
        break;
      }
    } // calculate trace

    DrawTrace(vTrace, i, bDumpFile);

  } // for all integration schemes

  SDL_UpdateRect(Surface(), 0, 0, GetWidth(), GetHeight());

  return m_vResults;
}

//------------------------------------------------------------------------
void IntegrationWindow::Render()
{
  SDL_UpdateRect(Surface(), 0, 0, GetWidth(), GetHeight());
}

//------------------------------------------------------------------------
void IntegrationWindow::DrawModel()
{
  ModelMagPend::src_vec vec_src = m_Model.GetSources();
  int w_2 = GetWidth()/2;
  int h_2 = GetHeight()/2;

  for (std::size_t i=0; i<vec_src.size(); ++i)
  {
    const ModelMagPend::Source &src = vec_src[i];
    if (src.type==0)
    {
      filledCircleRGBA(Surface(),
                       w_2 + src.x * w_2,
                       h_2 + src.y * h_2,
                       src.r*w_2,
                       src.col.r,
                       src.col.g,
                       src.col.b,
                       255);
    }
    else
    {
      hlineRGBA(Surface(),
                w_2 + (src.x - src.r) * w_2,
                w_2 + (src.x + src.r) * w_2,
                h_2 + src.y * h_2,
                src.col.r,
                src.col.g,
                src.col.b,
                255);

      vlineRGBA(Surface(),
                w_2 + src.x * w_2,
                h_2 + (src.y - src.r) * h_2,
                h_2 + (src.y + src.r) * h_2,
                src.col.r,
                src.col.g,
                src.col.b,
                255);
    }
  }
}

//------------------------------------------------------------------------
void IntegrationWindow::DrawTrace(const trace_type &trace, int color, bool bDumpFile)
{
  DrawModel();

  // Draw the trace
  int w_2 = GetWidth()/2;
  int h_2 = GetHeight()/2;

  std::auto_ptr<std::ofstream> pFile;
  
  if (bDumpFile)
  {
    pFile.reset(new std::ofstream());
    std::string sName = std::string("trace_") + m_vIntegrator[color]->GetID() + ".dat";
    pFile->open(sName.c_str());
  }

  for (std::size_t a=1; a<trace.size(); ++a)
  {
    const Point &pt1 = trace[a-1];
    const Point &pt2 = trace[a];

    if (pFile.get())
      *pFile << pt1.x << ", " << pt1.y << "\n";

    Color &col = m_aColors[color];
    lineRGBA(Surface(),
             w_2 + pt1.x * w_2,
             h_2 + pt1.y * h_2,
             w_2 + pt2.x * w_2,
             h_2 + pt2.y * h_2,
             col.r,
             col.g,
             col.b,
             255);
  }

  if (pFile.get())
    *pFile << std::flush;

}

//------------------------------------------------------------------------
IntegrationWindow::integrator_buf IntegrationWindow::GetIntegratorBuffer()
{
  return m_vIntegrator;
}

//------------------------------------------------------------------------
const gfx::Color& IntegrationWindow::GetColor(int i) const
{
  return m_aColors[i];
}

//------------------------------------------------------------------------
void IntegrationWindow::PollMessages()
{
//  return;
  
  while (SDL_PollEvent(&m_event))
  {
    switch (m_event.type)
    {
    case SDL_QUIT:
        ExitMainLoop();
        break;

    case SDL_MOUSEBUTTONDOWN:
         {
           SDL_FillRect(Surface(), NULL, 0);
           m_xTrace = 2 * ((double)m_event.button.x / GetWidth()) - 1;
           m_yTrace = 2 * ((double)m_event.button.y / GetHeight()) - 1;
           const result_type &res = Calculate(m_xTrace, m_yTrace, true);

           std::cout << "Trace results: \n";
           for (std::size_t i=0; i<res.size(); ++i)
             std::cout << m_vIntegrator[i]->GetID() << " : " << res[i] << "\n";
         }
         break;
/*

      case SDL_KEYDOWN:
        switch (m_event.key.keysym.sym)
        {
          case SDLK_PLUS:
            m_fov *= 1.2;
            break;
          case SDLK_MINUS:
            m_fov *= 0.8;
            break;
          case SDLK_s:
            m_bShowSolarSystem ^= true;
            break;
          case SDLK_r:
            m_bShowResonance ^= true;
            break;
          case SDLK_c:
            m_bContSource ^= true;
            break;
          case SDLK_0:
            if (m_pPlanets->GetNumPlanets()>=5)
              m_center = 4;
            break;
          case SDLK_1:
            if (m_pPlanets->GetNumPlanets()>=1)
              m_center = 0;
            break;
          case SDLK_2:
            if (m_pPlanets->GetNumPlanets()>=2)
              m_center = 1;
            break;
          case SDLK_3:
            if (m_pPlanets->GetNumPlanets()>=3)
              m_center = 2;
            break;
          case SDLK_4:
            if (m_pPlanets->GetNumPlanets()>=4)
              m_center = 3;
            break;
          case SDLK_F1:
            m_resonance ^= 1<<0;
            break;
          case SDLK_F2:
            m_resonance ^= 1<<1;
            break;
          case SDLK_F3:
            m_resonance ^= 1<<2;
            break;
          case SDLK_F4:
            m_resonance ^= 1<<3;
            break;
          case SDLK_KP_MINUS:
            m_frameTime -= 5000;
            m_frameTime = std::max(0, m_frameTime);
            break;
          case SDLK_KP_PLUS:
            m_frameTime += 5000;
            break;
          default:
            break;
        }
        break;
 */

      default:
        break;
    } // switch event type
  }
}
