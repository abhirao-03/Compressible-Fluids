#include <iostream>
#include "simulation.h"

void Simulation::m_GetU()
    {
        for (int i = 0; i < m_vec_dU.size(); i++)
            {
                double x = m_dXStart + (i - 0.5) * m_dDeltaX;
                std::cout << x << ' ' << m_vec_dU[i] << std::endl;
            }
    }

vec3 Simulation::m_GetPrimitives(const vec3& f_vec3_U)
    {

        double density = f_vec3_U[0];
        double velocity = f_vec3_U[1] / density;
        double pressure = (m_dGamma - 1) * (f_vec3_U[2] - (1.0/2.0)*(density * (pow(velocity, 2.0))));

        return vec3(density, velocity, pressure);
    }

double Simulation::m_GetEnergy(const double& u_dDensity, const double& u_dVelocity, const double& u_dPressure)
    {
        return u_dPressure/(m_dGamma - 1.0) + (1.0/2.0) * (u_dDensity) * (pow(u_dVelocity, 2.0));
    }

    
vec3 Simulation::m_EulerFluxFunction(const vec3& f_vec3_U)
            {
                vec3 prims = m_GetPrimitives(f_vec3_U);

                double& h_dDensity = prims[0];
                double& h_dVelocity = prims[1];
                double& h_dPressure = prims[2];

                double d_FirstFlux = h_dDensity * h_dVelocity;
                double d_SecondFlux = h_dDensity * pow(h_dVelocity, 2.0) + h_dPressure;
                double d_ThirdFlux = (f_vec3_U[2] + h_dPressure) * h_dVelocity;

                return vec3(d_FirstFlux, d_SecondFlux, d_ThirdFlux);
            }