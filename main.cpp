//--- Standard includes ------------------------------------------------------
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <cmath>
#include <sys/time.h>
#include <omp.h>

//--- SDL includes -----------------------------------------------------------
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

//--- Simulation -------------------------------------------------------------
#include "IntegrationWindow.hpp"
#include "Types.h"

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
#include "ModelOscillation.hpp"
#include "DampedHarmonicOscillator.h"

using namespace gfx;


//----------------------------------------------------------------------------
void Verify()
{
  std::vector<IIntegrator*> vInt;
  double rk = 4;
  double k = 1000;
  double mass = 1;
  double x0 = 1;
  double v0 = 0;

  ModelOscillation slnApprox(rk, k, mass);
  DampedHarmonicOscillator slnExact(rk, k, mass, x0, v0);

  double dt = 0.005;
  vInt.push_back(new IntegratorADB5(&slnApprox, dt));
  vInt.push_back(new IntegratorEulerImproved(&slnApprox, dt));
  vInt.push_back(new IntegratorRK4(&slnApprox, dt));
  vInt.push_back(new IntegratorRK3(&slnApprox, dt));
  vInt.push_back(new IntegratorEuler(&slnApprox, dt));
  vInt.push_back(new IntegratorHeun(&slnApprox, dt));
  vInt.push_back(new IntegratorRK5(&slnApprox, dt));
  vInt.push_back(new IntegratorADB2(&slnApprox, dt));
  vInt.push_back(new IntegratorADB3(&slnApprox, dt));
  vInt.push_back(new IntegratorADB4(&slnApprox, dt));

  // Set initial state
  for (std::size_t i=0; i<vInt.size(); ++i)
  {
    double state[2] = {v0, x0};
    vInt[i]->SetInitialState(state);
  }

  // Do calculation
  // write header
  double *state;

  // calculate

  for (std::size_t i=0; i<vInt.size(); ++i)
  {
    IIntegrator *m_pInt = vInt[i];

    std::ofstream of_err( (std::string("error_") + m_pInt->GetID() +".dat").c_str());

    double dt = 0.1;
    double sqr_err = 0;

    for (;dt>=4e-9;)
    {
      timeval ts;
      gettimeofday(&ts,0);

      long long tm=0,
                ct = 0,
                start = (long long)(ts.tv_sec * 1000 + (ts.tv_usec / 1000));

      while (tm<1000)
      {
        ++ct;

//#define DUMP_TRACE
#ifdef DUMP_TRACE
        std::ofstream of_vel( (std::string("osci_vel_") + m_pInt->GetID() +".dat").c_str()),
                      of_pos( (std::string("osci_pos_") + m_pInt->GetID() +".dat").c_str());
        of_vel << "# Velocities for " << m_pInt->GetID() << "\n";
        of_vel << "#\"time in s\", \"v0 approx\", \"v0 exact\", \"diff\"\n";
        of_pos << "# Positions for " << m_pInt->GetID() << "\n";
        of_pos << "#\"time in s\", \"x0 approx\", \"x0 exact\", \"diff\"\n";
#endif

        sqr_err = 0;
        double init[2] = {v0, x0};
        m_pInt->SetStepSize(dt);
        m_pInt->SetInitialState(init);
                
        for (;m_pInt->GetTime()<1;)
        {
          m_pInt->SingleStep();
          state = m_pInt->GetState();
          double t = m_pInt->GetTime(),
//                 va = state[0],
                 xa = state[1],
//                 ve = slnExact.v(t),
                 xe = slnExact.x(t);

  #ifdef DUMP_TRACE
          of_vel << t << ", " << va << ", " << ve << ", " << (va - ve) << std::endl;
          of_pos << t << ", " << xa << ", " << xe << ", " << (xa - xe) << std::endl;
  #endif

          sqr_err += (xa-xe)*(xa-xe);
        }

        gettimeofday(&ts,0);
        tm = (long long)(ts.tv_sec * 1000 + (ts.tv_usec / 1000)) - start;
      }

      of_err << dt << ", " << sqr_err << ", " << (double)tm/(double)ct << std::endl;
      std::cout << m_pInt->GetID() << "(iterations=" << ct << ") : " << dt << ", " << sqr_err << ", " << (double)tm/(double)ct << std::endl;

//      double dd = pow(10,(std::floor(std::log10(dt))));
      double dd = pow(10,(std::floor(std::log10(dt)-1)));
      dt -= 5*dd;
    }
  }
}

//------------------------------------------------------------------------
std::vector<int> CalculateArea(int num,
                               IIntegrator *pInt,
                               ModelMagPend &model,
                               long long &tm)
{
  std::vector<int> vResults(num*num, -1);

  // Calculate result for a reference line

  double min = -1,
         max = 1,
         d = (max-min) / (double)num;

  timeval ts;
  gettimeofday(&ts,0);
  long long start = (long long)(ts.tv_sec * 1000 + (ts.tv_usec / 1000));

  for (int yy=0; yy<num; ++yy)
  {
    for (int xx=0; xx<num; ++xx)
    {
      // Set initial state
      double state[4] = { 0, 0, min + d*xx, min + d*yy};
      pInt->SetInitialState(state);

      // Calculate a complete line and store the magnet indices
      for (std::size_t len=0; len<1000000; ++len)
      {
        pInt->SingleStep();

        double *state = pInt->GetState();
        if (model.IsFinished(state))
        {
          vResults[xx+yy*num] = model.GetStopIdx();
          break;
        }
      } // calculate trace
    } // xx
  } // yy

  gettimeofday(&ts,0);
  tm = (long long)(ts.tv_sec * 1000 + (ts.tv_usec / 1000)) - start;

  return vResults;
}

//----------------------------------------------------------------------------
void Benchmark()
{
  std::vector<int> result, ref;
  double dt = 0.0005;
  int dim = 50;
  ModelMagPend model(.4);
  std::vector<IIntegrator*> vInt;

  vInt.push_back(new IntegratorEuler(&model, dt));
  vInt.push_back(new IntegratorEulerImproved(&model, dt));
  vInt.push_back(new IntegratorHeun(&model, dt));
  vInt.push_back(new IntegratorRK3(&model, dt));
  vInt.push_back(new IntegratorRK4(&model, dt));
  vInt.push_back(new IntegratorRK5(&model, dt));
  vInt.push_back(new IntegratorADB2(&model, dt));
  vInt.push_back(new IntegratorADB3(&model, dt));
  vInt.push_back(new IntegratorADB4(&model, dt));
  vInt.push_back(new IntegratorADB5(&model, dt));

  for (std::size_t i=0; i<vInt.size(); ++i)
  {
    IIntegrator &sim = *vInt[i];

    std::string sName = std::string("Accuracy_") + vInt[i]->GetID() + ".dat";
    std::ofstream of(sName.c_str());
    of << "# Accuracy and timing\n";
    of << "# Method: " << sim.GetID() << "\n";
    of << "# Dim: " << dim << " x " << dim << "\n";
    of << "# \"h\", \"diff in perc\", \"time in ms\"\n";
    dt = 0.0005;
    ref.clear();
    
    for (;dt<=0.1;)
    {
      sim.SetStepSize(dt);
      long long tm;
      result = CalculateArea(dim, &sim, model, tm);

      if (ref.size()==0)
        ref = result;

      assert(ref.size()==result.size());
      assert(ref.size());

      // Calculate difference to reference calculation
      int diff = 0;
      for (std::size_t i=0; i<ref.size(); ++i)
      {
        diff += (ref[i]!=result[i]);
        assert(ref[i]!=-1);
      }

      double diffRel = (double)diff / ref.size();
      of << dt << ", " << diffRel << ", " << tm << std::endl;

      if (diffRel>0.5)
        break;

      double dd = pow(10,(std::floor(std::log10(dt))));
      dt += dd*0.25;
    }
  }
}


//----------------------------------------------------------------------------
void CalcPattern(int xdim, int ydim)
{
  try
  {
    std::auto_ptr<IntegrationWindow> pWin(new IntegrationWindow(800, 800));
    IntegrationWindow::integrator_buf vInt = pWin->GetIntegratorBuffer();

    std::ofstream all("number_of_equal_results.ppm");
    all << "P3\n" << xdim << " " << ydim << "\n255\n";

    std::ofstream of[vInt.size()];
    for (std::size_t i=0; i<vInt.size(); ++i)
    {
      std::string sName = vInt[i]->GetID() + ".ppm";
      of[i].open(sName.c_str());
      of[i] << "P3\n" << xdim << " " << ydim << "\n255\n";
    }

    for (int nx=0; nx<xdim; ++nx)
    {
      int ct[11];  // maximum number of magnets

      for (int ny=0; ny<ydim; ++ny)
      {
        double fx = 4.0*nx/xdim - 2;
        double fy = 4.0*ny/ydim - 2;
        const IntegrationWindow::result_type &res = pWin->Calculate(fx, fy, false);

        // Auszählen, wie wiele verschiedene Ergebnisse es gibt
        for (std::size_t i=0; i<res.size(); ++i)
        {
          int idxMag = res[i];
          ct[idxMag]++;   // xheck number of different results
          const Color &c = Color::FromPalette( (idxMag>=0) ? idxMag : 11);
          of[i] << c.r << " " << c.g << " " << c.b << " ";
        }

        int num = 0;
        std::size_t n = res.size();
        for (std::size_t i=0; i<n; ++i)
        {
          num += (ct[i]!=-1) ? 1 : 0;
          ct[i] = 0;
        }

        int c = 250-(num-1)*25;
        all << c << " " << c << " " << c << " ";
      }
    }

    for (std::size_t i=0; i<vInt.size(); ++i)
      of[i] << std::endl;

    all << std::endl;

    pWin->Init(0,0,1,1);
    pWin->MainLoop();
  }
  catch(std::exception & exc)
  {
    std::cout << exc.what();
  }
  catch(...)
  {
    std::cout << "fatal error\n";
  }

}

//------------------------------------------------------------------------
void CalcOMP(int dim)
{
  const int num_threads = 4;

  IIntegrator *pInt[num_threads];
  ModelMagPend *pModel[num_threads];

  // each thread gets its own integrator
  for (int i=0; i<num_threads; ++i)
  {
    pModel[i] = new ModelMagPend(.4);
    pInt[i] = new IntegratorRK5(pModel[i], 0.015);
  }

  std::string sName = pInt[0]->GetID() + ".ppm";
  std::ofstream of(sName.c_str());
  of << "P3\n" << dim << " " << dim << "\n255\n";

  omp_set_num_threads(num_threads);

  // there is a shared array to store the results
  int **aResult;
  aResult = new int*[dim];
  for (int i=0; i<dim; ++i)
    aResult[i] = new int[dim];

  double min(-2), max(2), d((max-min) / (double)dim);
  int idx(0), th_id(0), line(-1);

  #pragma omp parallel default(shared) private(th_id)
  while(line<dim)
  {
    int yy;

    #pragma omp critical
    {
      line++;
      th_id = omp_get_thread_num();
      std::cout << "Thread " << th_id << " calculating line " << line << "\n";
      yy = line;
    }

    for (int xx=0; xx<dim; ++xx)
    {
      // Set initial state
      double state[4] = { 0, 0, min + d*xx, min + d*yy};
      pInt[th_id]->SetInitialState(state);

      // Calculate a complete line and store the magnet indices
      for (std::size_t len=0; len<1000000; ++len)
      {
        pInt[th_id]->SingleStep();

        double *state = pInt[th_id]->GetState();
        if (pModel[th_id]->IsFinished(state))
        {
          aResult[xx][yy] = pModel[th_id]->GetStopIdx();
          break;
        }
      }
    } // xx

//    #pragma omp barrier
  } // yy

  // Write image to ppm file
  std::cout << "Dumping result\n";
  for (int yy=0; yy<dim; ++yy)
  {
        for (int xx=0; xx<dim; ++xx)
        {
          int idxMag = aResult[xx][yy];
          const Color &c = Color::FromPalette( (idxMag>=0) ? idxMag : 11);
          of << c.r << " " << c.g << " " << c.b << " ";
        }
   }

  of << std::flush;

  // Cleanup
  for (int i=0; i<num_threads; ++i)
  {
    delete pInt[i];
    delete pModel[i];
  }

  for (int i=0; i<dim; ++i)
    delete aResult[i];

  delete aResult;
}

//----------------------------------------------------------------------------
int main(int argc, char** argv)
{
  // Uncomment to verify against the analytic model of the damped harmonic oscillation
  //  Verify();

  // Uncomment to calculate benchmark for the magnetic pendulum
  //  Benchmark();

  // Calculation on multiple cores using openMP
  CalcOMP(500);

  // Uncomment to calculate large patterns using multiple integration schemes
  // output goes directly to ppm file
  //CalcMultiPattern(500, 500);

  return (EXIT_SUCCESS);
}

