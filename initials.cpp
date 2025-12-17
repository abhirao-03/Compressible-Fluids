#include "simulation.h"

void Simulation::InitialOne(std::vector<vec3>& vec_dU)
    {
        double l_dDensity = 1.0;
        double l_dVelocity = 0.0;
        double l_dPressure = 1.0;

        double l_dEnergy = GetEnergy(l_dDensity, l_dVelocity, l_dPressure);

        for (vec3& l_vec3ConservedVars : vec_dU)
            {
                l_vec3ConservedVars[0] = l_dDensity;
                l_vec3ConservedVars[1] = l_dDensity*l_dVelocity;
                l_vec3ConservedVars[2] = l_dEnergy;
            }
    }

void Simulation::InitialTwo(std::vector<vec3>& vec_dU)
    {
        double l_dDensity = 2.0;
        double l_dVelocity = 1.0;
        double l_dPressure = 3.0;

        double l_dEnergy = GetEnergy(l_dDensity, l_dVelocity, l_dPressure);
        
        for (vec3& l_vec3ConservedVars : vec_dU)
            {
                l_vec3ConservedVars[0] = l_dDensity;
                l_vec3ConservedVars[1] = l_dDensity*l_dVelocity;
                l_vec3ConservedVars[2] = l_dEnergy;
            }
    }

void Simulation::InitialThree(std::vector<vec3>& vec_dU)
    {
        double l_dLeftDensity = 1.0;
        double l_dLeftVelocity = 0.0;
        double l_dLeftPressure = 1.0;
        double l_dLeftEnergy = GetEnergy(l_dLeftDensity, l_dLeftVelocity, l_dLeftPressure);

        double l_dRightDensity = 0.1;
        double l_dRightVelocity = 0.0;
        double l_dRightPressure = 1.0;
        double l_dRightEnergy = GetEnergy(l_dRightDensity, l_dRightVelocity, l_dRightPressure);

        double l_dDiscontinuityLocation = 0.5;

        for (int i = 0; i < vec_dU.size(); i++)
            {
                vec3& l_vec3ConservedVars = vec_dU[i];

                double l_dXVal = m_dXStart + m_dDeltaX * (i - 0.5);

                if (l_dXVal <= l_dDiscontinuityLocation)
                    {
                        l_vec3ConservedVars[0] = l_dLeftDensity;
                        l_vec3ConservedVars[1] = l_dLeftDensity*l_dLeftVelocity;
                        l_vec3ConservedVars[2] = l_dLeftEnergy;
                    } else {
                        l_vec3ConservedVars[0] = l_dRightDensity;
                        l_vec3ConservedVars[1] = l_dRightDensity*l_dRightVelocity;
                        l_vec3ConservedVars[2] = l_dRightEnergy;
                    }
            }
    }

void Simulation::InitialFour(std::vector<vec3>& vec_dU)
    {
        double l_dLeftDensity = 1.0;
        double l_dLeftVelocity = 1.0;
        double l_dLeftPressure = 1.0;
        double l_dLeftEnergy = GetEnergy(l_dLeftDensity, l_dLeftVelocity, l_dLeftPressure);

        double l_dRightDensity = 0.1;
        double l_dRightVelocity = 1.0;
        double l_dRightPressure = 1.0;
        double l_dRightEnergy = GetEnergy(l_dRightDensity, l_dRightVelocity, l_dRightPressure);

        double l_dDiscontinuityLocation = 0.25;

        for (int i = 0; i < vec_dU.size(); i++)
            {
                vec3& l_vec3ConservedVars = vec_dU[i];

                double l_dXVal = m_dXStart + m_dDeltaX * (i - 0.5);

                if (l_dXVal <= l_dDiscontinuityLocation)
                    {
                        l_vec3ConservedVars[0] = l_dLeftDensity;
                        l_vec3ConservedVars[1] = l_dLeftDensity*l_dLeftVelocity;
                        l_vec3ConservedVars[2] = l_dLeftEnergy;
                    } else {
                        l_vec3ConservedVars[0] = l_dRightDensity;
                        l_vec3ConservedVars[1] = l_dRightDensity*l_dRightVelocity;
                        l_vec3ConservedVars[2] = l_dRightEnergy;
                    }
            }
    }

void Simulation::ToroInitialOne(std::vector<vec3>& vec_dU)
    {
        double l_dLeftDensity = 1.0;
        double l_dLeftVelocity = 0.0;
        double l_dLeftPressure = 1.0;
        double l_dLeftEnergy = GetEnergy(l_dLeftDensity, l_dLeftVelocity, l_dLeftPressure);

        double l_dRightDensity = 0.125;
        double l_dRightVelocity = 0.0;
        double l_dRightPressure = 0.1;
        double l_dRightEnergy = GetEnergy(l_dRightDensity, l_dRightVelocity, l_dRightPressure);

        double l_dDiscontinuityLocation = 0.5;

        for (int i = 0; i < vec_dU.size(); i++)
            {
                vec3& l_vec3ConservedVars = vec_dU[i];

                double l_dXVal = m_dXStart + m_dDeltaX * (i - 0.5);

                if (l_dXVal <= l_dDiscontinuityLocation)
                    {
                        l_vec3ConservedVars[0] = l_dLeftDensity;
                        l_vec3ConservedVars[1] = l_dLeftDensity*l_dLeftVelocity;
                        l_vec3ConservedVars[2] = l_dLeftEnergy;
                    } else {
                        l_vec3ConservedVars[0] = l_dRightDensity;
                        l_vec3ConservedVars[1] = l_dRightDensity*l_dRightVelocity;
                        l_vec3ConservedVars[2] = l_dRightEnergy;
                    }
            }
    }


void Simulation::ToroInitialTwo(std::vector<vec3>& vec_dU)
    {
        double l_dLeftDensity = 1.0;
        double l_dLeftVelocity = -2.0;
        double l_dLeftPressure = 0.4;
        double l_dLeftEnergy = GetEnergy(l_dLeftDensity, l_dLeftVelocity, l_dLeftPressure);

        double l_dRightDensity = 1.0;
        double l_dRightVelocity = 2.0;
        double l_dRightPressure = 0.4;
        double l_dRightEnergy = GetEnergy(l_dRightDensity, l_dRightVelocity, l_dRightPressure);

        double l_dDiscontinuityLocation = 0.5;

        for (int i = 0; i < vec_dU.size(); i++)
            {
                vec3& l_vec3ConservedVars = vec_dU[i];

                double l_dXVal = m_dXStart + m_dDeltaX * (i - 0.5);

                if (l_dXVal <= l_dDiscontinuityLocation)
                    {
                        l_vec3ConservedVars[0] = l_dLeftDensity;
                        l_vec3ConservedVars[1] = l_dLeftDensity*l_dLeftVelocity;
                        l_vec3ConservedVars[2] = l_dLeftEnergy;
                    } else {
                        l_vec3ConservedVars[0] = l_dRightDensity;
                        l_vec3ConservedVars[1] = l_dRightDensity*l_dRightVelocity;
                        l_vec3ConservedVars[2] = l_dRightEnergy;
                    }
            }
    }

void Simulation::ToroInitialThree(std::vector<vec3>& vec_dU)
    {
        double l_dLeftDensity = 1.0;
        double l_dLeftVelocity = 0.0;
        double l_dLeftPressure = 1000.0;
        double l_dLeftEnergy = GetEnergy(l_dLeftDensity, l_dLeftVelocity, l_dLeftPressure);

        double l_dRightDensity = 1.0;
        double l_dRightVelocity = 0.0;
        double l_dRightPressure = 0.01;
        double l_dRightEnergy = GetEnergy(l_dRightDensity, l_dRightVelocity, l_dRightPressure);

        double l_dDiscontinuityLocation = 0.5;

        for (int i = 0; i < vec_dU.size(); i++)
            {
                vec3& l_vec3ConservedVars = vec_dU[i];

                double l_dXVal = m_dXStart + m_dDeltaX * (i - 0.5);

                if (l_dXVal <= l_dDiscontinuityLocation)
                    {
                        l_vec3ConservedVars[0] = l_dLeftDensity;
                        l_vec3ConservedVars[1] = l_dLeftDensity*l_dLeftVelocity;
                        l_vec3ConservedVars[2] = l_dLeftEnergy;
                    } else {
                        l_vec3ConservedVars[0] = l_dRightDensity;
                        l_vec3ConservedVars[1] = l_dRightDensity*l_dRightVelocity;
                        l_vec3ConservedVars[2] = l_dRightEnergy;
                    }
            }
    }

void Simulation::ToroInitialFour(std::vector<vec3>& vec_dU)
    {
        double l_dLeftDensity = 1.0;
        double l_dLeftVelocity = 0.0;
        double l_dLeftPressure = 0.01;
        double l_dLeftEnergy = GetEnergy(l_dLeftDensity, l_dLeftVelocity, l_dLeftPressure);

        double l_dRightDensity = 1.0;
        double l_dRightVelocity = 0.0;
        double l_dRightPressure = 100.0;
        double l_dRightEnergy = GetEnergy(l_dRightDensity, l_dRightVelocity, l_dRightPressure);

        double l_dDiscontinuityLocation = 0.5;

        for (int i = 0; i < vec_dU.size(); i++)
            {
                vec3& l_vec3ConservedVars = vec_dU[i];

                double l_dXVal = m_dXStart + m_dDeltaX * (i - 0.5);

                if (l_dXVal <= l_dDiscontinuityLocation)
                    {
                        l_vec3ConservedVars[0] = l_dLeftDensity;
                        l_vec3ConservedVars[1] = l_dLeftDensity*l_dLeftVelocity;
                        l_vec3ConservedVars[2] = l_dLeftEnergy;
                    } else {
                        l_vec3ConservedVars[0] = l_dRightDensity;
                        l_vec3ConservedVars[1] = l_dRightDensity*l_dRightVelocity;
                        l_vec3ConservedVars[2] = l_dRightEnergy;
                    }
            }
    }

void Simulation::ToroInitialFive(std::vector<vec3>& vec_dU)
    {
        double l_dLeftDensity = 5.99924;
        double l_dLeftVelocity = 19.5975;
        double l_dLeftPressure = 460.894;
        double l_dLeftEnergy = GetEnergy(l_dLeftDensity, l_dLeftVelocity, l_dLeftPressure);

        double l_dRightDensity = 5.99242;
        double l_dRightVelocity = -6.19633;
        double l_dRightPressure = 46.0950;
        double l_dRightEnergy = GetEnergy(l_dRightDensity, l_dRightVelocity, l_dRightPressure);

        double l_dDiscontinuityLocation = 0.5;

        for (int i = 0; i < vec_dU.size(); i++)
            {
                vec3& l_vec3ConservedVars = vec_dU[i];

                double l_dXVal = m_dXStart + m_dDeltaX * (i - 0.5);

                if (l_dXVal <= l_dDiscontinuityLocation)
                    {
                        l_vec3ConservedVars[0] = l_dLeftDensity;
                        l_vec3ConservedVars[1] = l_dLeftDensity*l_dLeftVelocity;
                        l_vec3ConservedVars[2] = l_dLeftEnergy;
                    } else {
                        l_vec3ConservedVars[0] = l_dRightDensity;
                        l_vec3ConservedVars[1] = l_dRightDensity*l_dRightVelocity;
                        l_vec3ConservedVars[2] = l_dRightEnergy;
                    }
            }
    }

void Simulation::InitialSineWave(std::vector<vec3>& vec_dU)
{
    // Parameters
    double l_dVelocity = 1.0;
    double l_dPressure = 1.0;

    for (int i = 0; i < vec_dU.size(); i++)
    {
        vec3& l_vec3ConservedVars = vec_dU[i];

        // Calculate cell center (Account for ghost cells!)
        // If i=0 is ghost, x should be -0.5*dx. 
        double l_dXVal = m_dXStart + (i - 0.5) * m_dDeltaX;

        // Density Sine Wave
        double l_dDensity = 1.0 + 0.2 * sin(2.0 * PI * l_dXVal);

        // Calculate Energy
        double l_dEnergy = GetEnergy(l_dDensity, l_dVelocity, l_dPressure);

        // Set Conserved Variables
        l_vec3ConservedVars[0] = l_dDensity;
        l_vec3ConservedVars[1] = l_dDensity * l_dVelocity; // Momentum
        l_vec3ConservedVars[2] = l_dEnergy;
    }
}