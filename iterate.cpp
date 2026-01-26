#include <iostream>
#include "simulation.h"

    
void Simulation::m_Evolve()
{
    m_SetInitialCondition();
    
    int n_frames = 60; // How many frames in the GIF
    double dt = m_dTimeEnd / n_frames;

    // Start at a tiny time (1e-5) because t=0 causes divide-by-zero errors
    for (double t = 1e-5; t <= m_dTimeEnd; t += dt)
    {
        for (int i = 0; i < m_iNumPoints; i++)
        {
            double x = m_dXStart + (i + 0.5) * m_dDeltaX;
            
            // Get Primitive Variables directly (Rho, u, P)
            vec3 result = m_GetExactSolution(x, t);
            
            // Output: x, Density, Velocity, Pressure
            std::cout << x << ' ' << result[0] << ' ' << result[1] << ' ' << result[2] << std::endl;
        }
        
        // Two blank lines tell Gnuplot this is the end of a "Frame"
        std::cout << "\n\n";
    }
}