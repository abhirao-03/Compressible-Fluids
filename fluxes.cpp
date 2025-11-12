#include "simulation.h"
#include <cmath>

void Simulation::m_fvm_LaxFriedrichs(const std::vector<double>& vec_dOldU, std::vector<double>& vec_dNewU, const int& i_IndexUpdate)
{
    double uL = vec_dOldU[i_IndexUpdate];
    double uR = vec_dOldU[i_IndexUpdate + 1];

    double fL = 0.5*pow(uL, 2.0);
    double fR = 0.5*pow(uR, 2.0);

    double LaxFlux_One = (1.0/2.0) * (fL + fR);

    // need to do the above computation ONE MORE TIME and then pass LaxFlux_two
    // this is draft code, this will be changed relatively soon.
    vec_dNewU[i] = uL + m_dDeltaT / m_dDeltaX * (LaxFlux_One);

}

void Simulation::m_fvm_Richtmyer(const std::vector<double>& vec_dOldU, std::vector<double>& vec_dNewU, const int& i_IndexUpdate)
{

}

void Simulation::m_fvm_FORCE(const std::vector<double>& vec_dOldU, std::vector<double>& vec_dNewU, const int& i_IndexUpdate)
{

}

void Simulation::m_fvm_Godunov(const std::vector<double>& vec_dOldU, std::vector<double>& vec_dNewU, const int& i_IndexUpdate)
{

}
