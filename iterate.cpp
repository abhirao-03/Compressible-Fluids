#include <iostream>
#include "simulation.h"

    
void Simulation::m_Evolve()
    {
        m_SetInitialCondition();
        
        for (int i = 0; i < m_iNumPoints; i++)
            {
                double x = m_dXStart + (i + 0.5) * m_dDeltaX;
                vec3 result = m_GetExactSolution(x, m_dTimeEnd);
                
                double momentum = result[1] * result[0];
                double energy = m_GetEnergy(result[0], result[1], result[2]);
                
                m_vec_dU[i] = vec3{result[0], momentum, energy};
                
                std::cout << x << ' ' << result[0] << ' ' << result[1] << ' ' << result[2] << std::endl;
            }
    }