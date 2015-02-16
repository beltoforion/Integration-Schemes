/* 
 * File:   DampedHarmonicOscillator.h
 * Author: user
 *
 * Created on 7. Juni 2009, 15:41
 */

#ifndef _DAMPEDHARMONICOSCILLATOR_H
#define	_DAMPEDHARMONICOSCILLATOR_H

class DampedHarmonicOscillator
{
public:
  DampedHarmonicOscillator(double rk,
                           double k,
                           double mass,
                           double x0,
                           double v0);
  double x(double t) const;
  double v(double t) const;

private:
  double m_k;
  double m_rk;
  double m_mass;
  double m_delta;
  double m_omega_0;
  double m_omega_d;
  double m_x0;
  double m_v0;
};

#endif	/* _DAMPEDHARMONICOSCILLATOR_H */

