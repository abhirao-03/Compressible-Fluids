#include <iostream>
#include "simulation.h"


void Simulation::GetU()
{

    for (int i = 0; i < m_vec_dU.size(); i++)
    {
        double x = m_dXStart + (i - 0.5) * m_dDeltaX;
        std::cout << x << ' ' << m_vec_dU[i] << std::endl;
    }

}