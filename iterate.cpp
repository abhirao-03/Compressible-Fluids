#include <iostream>
#include "simulation.h"

void Simulation::m_EvolveHalfTimeStep()
    {
        for (int i = 0; i < m_vec_dU.size(); i++)
            {
                vec3 t_dULeft = m_vec_LeftReconstructed[i];
                vec3 t_dURight = m_vec_RightReconstructed[i];
                
                vec3 t_fFluxLext = m_EulerFluxFunction(t_dULeft);
                vec3 t_fFluxRight = m_EulerFluxFunction(t_dURight);
                
                vec3 l_vdUpdatePortion = (0.5 * m_dDeltaT / m_dDeltaX) * (t_fFluxLext - t_fFluxRight);
                
                m_vec_LeftReconstructed[i] += l_vdUpdatePortion;
                m_vec_RightReconstructed[i] += l_vdUpdatePortion;
            }
    }
    
void Simulation::Evolve()
    {
        SetInitialCondition();
        SetLimitingFunction();
        SetBoundaryConditions();
        SetTimeStep();
        
        double t = m_dTimeStart;

        do
            {
                t += m_dDeltaT;
                
                SetBoundaryConditions();
                m_ReconstructData();
                m_EvolveHalfTimeStep();
                m_GetReconstructedFluxes();
                
                std::cout << "# time = " << t << std::endl;

                for (int i = 1; i < m_vec_dU.size() - 1; i++)
                    {
                        double x = m_dXStart + (i - m_iNumGhostCells + 0.5) * m_dDeltaX;
                        
                        m_vec_dUNext[i] = m_vec_dU[i] - (m_dDeltaT / m_dDeltaX) * (m_vec_dFluxesReconstructed[i] - m_vec_dFluxesReconstructed[i-1]);
                        
                        std::cout << x << ' ' << m_vec_dUNext[i] << std::endl;
                    }

                std::cout << "\n\n";

                m_vec_dU = m_vec_dUNext;
                
                SetTimeStep();

            } while (t < m_dTimeEnd);
    }