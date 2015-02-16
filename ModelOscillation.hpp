/* 
 * File:   ModelOscillation.hpp
 * Author: user
 *
 * Created on 29. April 2009, 23:09
 */

#ifndef _MODELOSCILLATION_HPP
#define	_MODELOSCILLATION_HPP

#include "IModel.h"

//---------------------------------------------------------------------
class ModelOscillation : public IModel
{
public:
    ModelOscillation(double rk, double k, double mass);
    virtual void Eval(double *state, double time, double *deriv);
    virtual bool IsFinished(double *state);
    double GetK() const;
    double GetRK() const;
    double GetMass() const;

private:
    double m_rk;
    double m_k;
    double m_mass;
    double m_posPend;
};

#endif	/* _MODELOSCILLATION_HPP */

