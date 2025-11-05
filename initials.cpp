#include <cmath>
#include <vector>
#include <iostream>
#include "simulation.h"

void Simulation::ExponentInitial(std::vector<double>& vec_dU)
    {
        for (int i = 0; i < vec_dU.size(); i++)
            {
                double tmp_dXVal = m_dXStart + (i - m_iNumGhostCells/2) * m_dDeltaX;
                vec_dU[i] = exp(-8.0*pow(tmp_dXVal, 2.0));
            }
    }


void Simulation::BoxInitial(std::vector<double>& vec_dU)
    {
        for (int i = 0; i < vec_dU.size(); i++)
            {
                double tmp_dXVal = m_dXStart + (i - m_iNumGhostCells/2) * m_dDeltaX;
                
                if (tmp_dXVal >= 0.3 and tmp_dXVal <= 0.7)
                    {
                        m_vec_dU[i] = 1;
                    }
                else
                    {
                        m_vec_dU[i] = 0;
                    }
            }
    }

void Simulation::SinInitial(std::vector<double>& vec_dU)
    {
        for (int i = 0; i < vec_dU.size(); i++)
            {
                double tmp_dXVal = m_dXStart + (i - m_iNumGhostCells/2) * m_dDeltaX;
                vec_dU[i] = sin(2 * PI * tmp_dXVal);
            }
    }