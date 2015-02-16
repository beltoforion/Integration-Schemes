#include "DampedHarmonicOscillator.h"
#include <cmath>

//------------------------------------------------------------------------------
DampedHarmonicOscillator::DampedHarmonicOscillator(double rk,
                                                   double k,
                                                   double mass,
                                                   double x0,
                                                   double v0)
  :m_k(k)
  ,m_rk(rk)
  ,m_mass(mass)
  ,m_delta(0.5*m_rk/m_mass)
  ,m_omega_0(std::sqrt(m_k/m_mass))
  ,m_omega_d(std::sqrt(m_omega_0*m_omega_0 - m_delta*m_delta))
  ,m_x0(x0)
  ,m_v0(v0)
{}

//------------------------------------------------------------------------------
double DampedHarmonicOscillator::x(double t) const
{
  double odt = m_omega_d*t;
  return m_x0 * exp(-m_delta * t) * (cos(odt) + m_delta/m_omega_d * sin(odt));
}

//------------------------------------------------------------------------------
double DampedHarmonicOscillator::v(double t) const
{
  double A = m_x0;
  double B = m_x0*m_delta / m_omega_d;
  return -exp(-m_delta * t) * ((A*m_delta - B*m_omega_d)*cos(m_omega_d*t) +
                               (B*m_delta + A*m_omega_d)*sin(m_omega_d*t));
}
