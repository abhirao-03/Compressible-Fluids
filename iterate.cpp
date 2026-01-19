#include <iostream>
#include "simulation.h"

    
void Simulation::m_Evolve()
    {
        m_SetInitialCondition();

        double t = m_dTimeStart;

        t += m_dDeltaT;

        std::cout << "# time = " << t << std::endl;

        for (int i = 1; i < m_vec_dU.size() - 1; i++)
            {
                double x = m_dXStart + (i + 0.5) * m_dDeltaX;
                
                std::cout << x << ' ' << m_vec_dUNext[i] << std::endl;
            }

        std::cout << "\n\n";

        m_vec_dU = m_vec_dUNext;

    }