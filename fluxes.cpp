#include "simulation.h"
#include <cmath>

void Simulation::m_fvm_LaxFriedrichs()
    {
        for (int i = 0; i < m_vec_dU.size() - 1; i++)
            {
                vec3 t_dULeft = m_vec_dU[i];
                vec3 t_dURight = m_vec_dU[i + 1];

                vec3 t_dFluxLeft = m_EulerFluxFunction(t_dULeft);
                vec3 t_dFluxRight = m_EulerFluxFunction(t_dURight);

                m_vec_dFluxes[i] = 0.5 * (t_dFluxLeft + t_dFluxRight) + 0.5 * (m_dDeltaX/m_dDeltaT) * (t_dULeft - t_dURight);
            }
    }

void Simulation::m_fvm_Richtmyer()
    {
        vec3 u_halfs;

        for (int i = 0; i < m_vec_dFluxes.size() - 1; i++)
            {
                vec3 u_left = m_vec_dU[i];
                vec3 u_right = m_vec_dU[i + 1];

                vec3 u_FluxLeft = m_EulerFluxFunction(u_left);
                vec3 u_FluxRight = m_EulerFluxFunction(u_right);

                u_halfs = 0.5 * (u_left + u_right) - 0.5 * (m_dDeltaT / m_dDeltaX) * (u_FluxRight - u_FluxLeft);

                m_vec_dFluxes[i] = m_EulerFluxFunction(u_halfs);
            }   
    }

void Simulation::m_fvm_FORCE()
    {
        m_fvm_LaxFriedrichs();
        std::vector<vec3> t_vec_LFFluxes = m_vec_dFluxes;

        m_fvm_Richtmyer();
        std::vector<vec3> t_vec_RichtmyerFluxes = m_vec_dFluxes;

        for (int i = 0; i < m_vec_dFluxes.size() - 1; i++)
            {
                m_vec_dFluxes[i] = 0.5 * (t_vec_LFFluxes[i] + t_vec_RichtmyerFluxes[i]);
            }
    }