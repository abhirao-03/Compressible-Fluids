#include "simulation.h"

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

        for (int i = 0; i < vec_dUpdateVector.size(); i++)
            {
                vec_dUpdateVector[i] = 0.5 * (t_vec_LFFluxes[i] + t_vec_RichtmyerFluxes[i]);
            }
    }