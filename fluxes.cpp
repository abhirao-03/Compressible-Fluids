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

void Simulation::m_fvm_Richtmyer()
    {
        std::vector<double> u_halfs(m_vec_dU.size());

        for (int i = 0; i < u_halfs.size() - 1; i++)
            {
                double u_left = m_vec_dU[i];
                double u_right = m_vec_dU[i + 1];

                double u_FluxLeft = m_BurgersFluxFunction(u_left);
                double u_FluxRight = m_BurgersFluxFunction(u_right);

                u_halfs[i] = 0.5 * (u_left + u_right) - 0.5 * (m_dDeltaT / m_dDeltaX) * (u_FluxRight - u_FluxLeft);

                m_vec_dFluxes[i] = m_BurgersFluxFunction(u_halfs[i]);
            }
        
    }

void Simulation::m_fvm_FORCE(){}

void Simulation::m_fvm_Godunov(){}