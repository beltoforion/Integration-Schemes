/* 
 * File:   ModelMagneticPendulum.cpp
 * Author: user
 *
 * Created on 29. April 2009, 23:08
 */

#include <cstdlib>
#include <cmath>
#include "ModelOscillation.hpp"

using namespace std;


//------------------------------------------------------------------------
ModelOscillation::ModelOscillation(double rk, double k, double mass)
  :IModel("Gedämpfte Schwingung (1D)", 2)
  ,m_rk(rk)
  ,m_k(k)
  ,m_mass(mass)
  ,m_posPend(0)
{}

//------------------------------------------------------------------------
double ModelOscillation::GetK() const
{
  return m_k;
}

//------------------------------------------------------------------------
double ModelOscillation::GetRK() const
{
  return m_rk;
}

//------------------------------------------------------------------------
double ModelOscillation::GetMass() const
{
  return m_mass;
}

//------------------------------------------------------------------------
void ModelOscillation::Eval(double *state, double time, double *deriv)
{
  // remapping the state array to readable variables:
  double &velocity(state[0]);
  double &position(state[1]);

  // Pendel
  double acceleration = 0;
  acceleration += m_k/m_mass * (m_posPend - position);
  acceleration -= m_rk/m_mass * velocity;

  // derivation of the state array
  deriv[0] = acceleration;
  deriv[1] = velocity;
}

//------------------------------------------------------------------------
bool ModelOscillation::IsFinished(double *state) 
{
  return false;
}
