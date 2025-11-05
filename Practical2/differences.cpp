#include "../Practical1/simulation.h"

void Simulation::BackwardDifference(const std::vector<double>& vec_dOldU, std::vector<double>& vec_dNewU, const int& i_IndexUpdate)
{
    vec_dNewU[i_IndexUpdate] = vec_dOldU[i_IndexUpdate] - m_dAdvectionCoefficient * (m_dDeltaT/m_dDeltaX) * (vec_dOldU[i_IndexUpdate] - vec_dOldU[i_IndexUpdate - 1]); 
}


void Simulation::ForwardDifference(const std::vector<double>& vec_dOldU, std::vector<double>& vec_dNewU, const int& i_IndexUpdate)
{
    vec_dNewU[i_IndexUpdate] = vec_dOldU[i_IndexUpdate] - m_dAdvectionCoefficient * (m_dDeltaT/m_dDeltaX) * (vec_dOldU[i_IndexUpdate + 1] - vec_dOldU[i_IndexUpdate]);
}


void Simulation::CentralDifference(const std::vector<double>& vec_dOldU, std::vector<double>& vec_dNewU, const int& i_IndexUpdate)
{
    vec_dNewU[i_IndexUpdate] = vec_dOldU[i_IndexUpdate] - m_dAdvectionCoefficient * (m_dDeltaT/m_dDeltaX) * (1.0/2.0) * (vec_dOldU[i_IndexUpdate + 1] - vec_dOldU[i_IndexUpdate - 1]);
}


void Simulation::LaxFriedrichs(const std::vector<double>& vec_dOldU, std::vector<double>& vec_dNewU, const int& i_IndexUpdate)
{
    vec_dNewU[i_IndexUpdate] = (1.0/2.0)*(1 + m_dCourantLaxFlewyConstant)*vec_dOldU[i_IndexUpdate - 1] + (1.0/2.0)*(1 - m_dCourantLaxFlewyConstant)*vec_dOldU[i_IndexUpdate + 1];
}


void Simulation::LaxWendroff(const std::vector<double>& vec_dOldU, std::vector<double>& vec_dNewU, const int& i_IndexUpdate)
{
    double tmp_dPastContribution = (1.0/2.0) * m_dCourantLaxFlewyConstant * (1 + m_dCourantLaxFlewyConstant) * vec_dOldU[i_IndexUpdate - 1];
    double tmp_dCurrentContribution = (1 - pow(m_dCourantLaxFlewyConstant, 2.0)) * vec_dOldU[i_IndexUpdate];
    double tmp_dFutureContribution = (1.0/2.0) * m_dCourantLaxFlewyConstant * (1 - m_dCourantLaxFlewyConstant) * vec_dOldU[i_IndexUpdate + 1];

    vec_dNewU[i_IndexUpdate] = tmp_dPastContribution + tmp_dCurrentContribution - tmp_dFutureContribution;
}


void Simulation::WarmingBeam(const std::vector<double>& vec_dOldU, std::vector<double>& vec_dNewU, const int& i_IndexUpdate)
{

}