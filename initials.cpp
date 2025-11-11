#include <cmath>
#include <vector>
#include <iostream>
#include "simulation.h"


void Simulation::ShockWave(std::vector<double>& vec_dU)
    {
        for(int i = 0; i < vec_dU.size(); i++)
            {
                double x = m_dXStart + (i - 0.5) * m_dDeltaX;
                
                if (x < 0.5)
                    {
                        vec_dU[i] = 2;
                    }
                else 
                    {
                        vec_dU[i] = 1;   
                    }
            }
    };

void Simulation::Rarefaction(std::vector<double>& vec_dU)
    {
        for(int i = 0; i < vec_dU.size(); i++)
            {
                double x = m_dXStart + (i - 0.5) * m_dDeltaX;
                
                if (x < 0.5)
                    {
                        vec_dU[i] = 1;
                    }
                else
                    {
                        vec_dU[i] = 2;
                    }
            }
    };

void Simulation::ToroInitial(std::vector<double>& vec_dU)
    {
        for(int i = 0; i < vec_dU.size(); i++)
            {
                double x = m_dXStart + (i - 0.5) * m_dDeltaX;
                
                if (x <= 0.5)
                    {
                        vec_dU[i] = -1.0/2.0;
                    }
                else if (x>= 0.5 && x <= 1)
                    {
                        vec_dU[i] = 1;
                    }
                else 
                    {
                        vec_dU[i] = 0;
                    }
            }
    };


void Simulation::Cosine(std::vector<double>& vec_dU)
    {
        for(int i = 0; i < vec_dU.size(); i++)
            {
                double x = m_dXStart + (i - 0.5) * m_dDeltaX;
                vec_dU[i] = cos(2*PI*x);
            }
    };