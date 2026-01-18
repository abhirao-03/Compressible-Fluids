#include <iostream>
#include "simulation.h"

    
void Simulation::Evolve()
    {
        SetInitialCondition();
        SetBoundaryConditions();
        SetTimeStep();
        
        double t = m_dTimeStart;

        do
            {
                t += m_dDeltaT;
                
                SetBoundaryConditions();

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