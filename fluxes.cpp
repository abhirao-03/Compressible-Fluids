#include "simulation.h"
#include <cmath>

void Simulation::m_fvm_LaxFriedrichs()
    {
        for (int i = 0; i < m_vec_dU.size() - 1; i++)
            {
                double t_dULeft = m_vec_dU[i];
                double t_dURight = m_vec_dU[i + 1];

                double t_dFluxLeft = m_BurgersFluxFunction(t_dULeft);
                double t_dFluxRight = m_BurgersFluxFunction(t_dURight);

                m_vec_dFluxes[i] = 0.5 * (t_dFluxLeft + t_dFluxRight) + 0.5 * (m_dDeltaX/m_dDeltaT) * (t_dULeft - t_dURight);
            }
    }

void Simulation::m_fvm_Richtmyer(){}

void Simulation::m_fvm_FORCE(){}

void Simulation::m_fvm_Godunov(){}