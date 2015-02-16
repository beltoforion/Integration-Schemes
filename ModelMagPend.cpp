/* 
 * File:   ModelMagneticPendulum.cpp
 * Author: user
 *
 * Created on 29. April 2009, 23:08
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include "ModelMagPend.h"

using namespace std;

ModelMagPend::Source::Source(double a_x,
                             double a_y,
                             double a_z,
                             double a_r,
                             double a_s,
                             int a_type,
                             const gfx::Color &a_col)
  :x(a_x)
  ,y(a_y)
  ,r(a_r)
  ,s(a_s)
  ,col(a_col)
  ,type(a_type)
{}

//------------------------------------------------------------------------
ModelMagPend::ModelMagPend(double rad)
  :IModel("Magnetisches Pendel (2D)", 4)
  ,m_rk(0.2)
  ,m_k(0.3)
  ,m_magnets()
  ,m_nIdxMag(-1)
{

  // The pendulum
  m_magnets.push_back(Source(0,       // xpos
                             0,       // ypos
                             0,       // zpos
                             0.05,    // rad
                             m_k,     // strength
                             1,
                             gfx::Color(255, 255, 255)));

  int col=1;
  rad = 0.7;
  // Magnets are located at a ring with radius 0.5
  for (int i=0; i<360; i+=72, ++col)
  {
    m_magnets.push_back( Source(rad*sin(i*M_PI/180.0), // xpos
                                rad*cos(i*M_PI/180.0), // ypos
                                -0.02,                 // zpos
                                0.04,                  // rad
                                0.2,                   // strength
                                0,                     // index of the force law
                                gfx::Color::FromPalette(col)) );
  }

  rad = 0.4;
  for (int i=36; i<396; i+=72, ++col)
  {
    m_magnets.push_back( Source(rad*sin(i*M_PI/180.0), // xpos
                                rad*cos(i*M_PI/180.0), // ypos
                                -0.02,
                                0.04,                  // rad
                                0.1,                   // strength
                                0,
                                gfx::Color::FromPalette(col)) ); 
  }


//  m_magnets.push_back( Source(0,  0.5, 0.05, 1.0, 0) );
//  m_magnets.push_back( Source(0, -0.5, 0.05, 1.0, 0) );
}

//------------------------------------------------------------------------
void ModelMagPend::Eval(double *state, double time, double *deriv)
{
  // velocity
  double &vel_x(state[0]);
  double &vel_y(state[1]);

  // position
  double &pos_x(state[2]);
  double &pos_y(state[3]);

  // Pendel
  double acc_x(0);
  double acc_y(0);
  bool bCheckAbort = false;

  for (unsigned i=0; i<m_magnets.size(); ++i)
  {
    Source &src = m_magnets[i];

    if (src.type==1)
    {
      acc_x += src.s * (src.x - pos_x);
      acc_y += src.s * (src.y - pos_y);
    }
    else
    {
      double d = sqrt( (src.x - pos_x) * (src.x - pos_x) +
                       (src.y - pos_y) * (src.y - pos_y) );
      bCheckAbort |= (d<src.r);
      //d += 0.0025;  // soften the forcefield a bit for very close range to avoid div by zero
      double dddd = d*d*d*d;
      acc_x += (src.s / (dddd+0.001)) * (src.x - pos_x);
      acc_y += (src.s / (dddd+0.001)) * (src.y - pos_y);
    }
  }

  // Friction
  acc_x -= m_rk * vel_x;
  acc_y -= m_rk * vel_y;

  // derivation of the state array
  deriv[0] = acc_x;
  deriv[1] = acc_y;
  deriv[2] = vel_x;
  deriv[3] = vel_y;

  m_bAbort = bCheckAbort && (/*(acc_x*acc_x + acc_y*acc_y) < 1e-2 &&*/
                             (vel_x*vel_x + vel_y*vel_y) < 0.005);
}

//------------------------------------------------------------------------
int ModelMagPend::GetMagNum() const
{
  return m_magnets.size();
}

//------------------------------------------------------------------------
int ModelMagPend::GetStopIdx() const
{
  return m_nIdxMag;
}

//------------------------------------------------------------------------
const ModelMagPend::src_vec& ModelMagPend::GetSources() const
{
  return m_magnets;
}

//------------------------------------------------------------------------
bool ModelMagPend::IsFinished(double *state) 
{
  if (m_bAbort)
  {
    double &pos_x(state[2]);
    double &pos_y(state[3]);

    double minDist = 999;
    for (unsigned i=0; i<m_magnets.size(); ++i)
    {
      const Source &src = m_magnets[i];

      double dist = sqrt( (src.x-pos_x) * (src.x-pos_x) +
                          (src.y-pos_y) * (src.y-pos_y) );

      if (dist<minDist)
      {
        m_nIdxMag = i;
        minDist = dist;
      }
    }
  }

  return m_bAbort;
/*


  double v = sqrt(vel_x*vel_x + vel_y*vel_y);

  m_nIdxMag = -1;
  std::cout << "v=" << v << " ";
  
  // Stopbedingung:
  // Pendel ist langsam und in der Nähe einer Quelle
  if (v<0.0001)
  {
    for (unsigned i=0; i<m_magnets.size(); ++i)
    {
      const Source &src = m_magnets[i];

      double dist = sqrt( (src.x-pos_x) * (src.x-pos_x) +
                          (src.y-pos_y) * (src.y-pos_y) );
      std::cout << "d=" << dist << " ";

      if (dist<src.r)
      {
        m_nIdxMag = i;
        return true;
      }
    }
  }

  return false;
   */
}
