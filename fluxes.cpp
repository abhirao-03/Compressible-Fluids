#include "simulation.h"
#include <cmath>

void Simulation::m_fvm_LaxFriedrichs(std::vector<vec3>& vec_dInputVector, std::vector<vec3>& vec_dUpdateVector)
    {
        for (int i = 0; i < vec_dInputVector.size() - 1; i++)
            {
                vec3 t_dULeft = vec_dInputVector[i];
                vec3 t_dURight = vec_dInputVector[i + 1];

                vec3 t_dFluxLeft = m_EulerFluxFunction(t_dULeft);
                vec3 t_dFluxRight = m_EulerFluxFunction(t_dURight);

                vec_dUpdateVector[i] = 0.5 * (t_dFluxLeft + t_dFluxRight) + 0.5 * (m_dDeltaX/m_dDeltaT) * (t_dULeft - t_dURight);
            }
    }

void Simulation::m_fvm_Richtmyer(std::vector<vec3>& vec_dInputVector, std::vector<vec3>& vec_dUpdateVector)
    {
        vec3 u_halfs;

        for (int i = 0; i < vec_dInputVector.size() - 1; i++)
            {
                vec3 u_left = vec_dInputVector[i];
                vec3 u_right = vec_dInputVector[i + 1];

                vec3 u_FluxLeft = m_EulerFluxFunction(u_left);
                vec3 u_FluxRight = m_EulerFluxFunction(u_right);

                u_halfs = 0.5 * (u_left + u_right) - 0.5 * (m_dDeltaT / m_dDeltaX) * (u_FluxRight - u_FluxLeft);

                vec_dUpdateVector[i] = m_EulerFluxFunction(u_halfs);
            }   
    }

void Simulation::m_fvm_FORCE(std::vector<vec3>& vec_dInputVector, std::vector<vec3>& vec_dUpdateVector)
    {
        m_fvm_LaxFriedrichs(vec_dInputVector, vec_dUpdateVector);
        std::vector<vec3> t_vec_LFFluxes = vec_dUpdateVector;

        m_fvm_Richtmyer(vec_dInputVector, vec_dUpdateVector);
        std::vector<vec3> t_vec_RichtmyerFluxes = vec_dUpdateVector;

        for (int i = 0; i < vec_dUpdateVector.size() - 1; i++)
            {
                vec_dUpdateVector[i] = 0.5 * (t_vec_LFFluxes[i] + t_vec_RichtmyerFluxes[i]);
            }
    }

void Simulation::m_CalculateFluxesFromReconstruction()
    {
        for (int i = 0; i < m_vec_dU.size() - 1; i++)
            {
                vec3 u_left = m_vec_RightReconstructed[i];
                vec3 u_right = m_vec_LeftReconstructed[i + 1];

                vec3 F_L = m_EulerFluxFunction(u_left);
                vec3 F_R = m_EulerFluxFunction(u_right);

                vec3 flux_LF = 0.5 * (F_L + F_R) + 0.5 * (m_dDeltaX/m_dDeltaT) * (u_left - u_right);

                vec3 u_half = 0.5 * (u_left + u_right) - 0.5 * (m_dDeltaT/m_dDeltaX) * (F_R - F_L);
                vec3 flux_RI = m_EulerFluxFunction(u_half);

                m_vec_dFluxes[i] = 0.5 * (flux_LF + flux_RI);
            }
    }