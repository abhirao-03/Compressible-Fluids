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

vec3 Simulation::GetPrimitives(const vec3& f_vec3_U)
    {
        double density = f_vec3_U[0];
        double velocity = f_vec3_U[1] / density;
        double pressure = (m_dGamma - 1) * (f_vec3_U[2] - (1.0/2.0)*(density * (pow(velocity, 2.0))));

        return vec3(density, velocity, pressure);
    }