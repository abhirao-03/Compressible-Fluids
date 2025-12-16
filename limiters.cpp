#include "simulation.h"

vec3 Simulation::GetSlopeMeasure(const int& t_iCellValue)
    {
        if (t_iCellValue == 0)
            {
                return vec3(0.0, 0.0, 0.0);
            } 

        else if (t_iCellValue == m_vec_dU.size() - 1)
            {
                return vec3(0.0, 0.0, 0.0);
            }
        else
            {
                vec3 t_vec3Current = m_vec_dU[t_iCellValue];
                vec3 t_vec3Previous = m_vec_dU[t_iCellValue - 1];
                vec3 t_vec3Future = m_vec_dU[t_iCellValue + 1];

                vec3 t_vec3FirstTerm = (1.0/2.0) * (1 + m_dOmega) * (t_vec3Current - t_vec3Previous);
                vec3 t_vec3SecondTerm = (1.0/2.0) * (1 - m_dOmega) * (t_vec3Future - t_vec3Current);

                return t_vec3FirstTerm + t_vec3SecondTerm;
            }
    }

double Simulation::m_SL_Superbee()
    {
        if (m_dSlopeLimitingR <= 0.0)
            {
                return 0.0;
            }
        else if (m_dSlopeLimitingR > 0.0 && m_dSlopeLimitingR <= 1.0/2.0)
            {
                return 2.0 * m_dSlopeLimitingR;
            }
        else if (m_dSlopeLimitingR > 1.0/2.0 and m_dSlopeLimitingR <= 1.0)
            {
                return 1.0;
            }
        else
            {
                return std::min(m_dSlopeLimitingR, std::min(m_dRightSlopeLimit, 2.0));
            }
    }

double Simulation::m_SL_VanLeer()
    {
        if (m_dSlopeLimitingR <= 0.0)
            {
                return 0.0;
            }
        else
            {
                return std::min(m_dLeftSlopeLimit, m_dRightSlopeLimit);
            }
        
    }

double Simulation::m_SL_VanAlbada()
    {
        if (m_dSlopeLimitingR <= 0.0)
            {
                return 0.0;
            }
        else
            {
                double l_dFirstTerm = m_dSlopeLimitingR * (1 + m_dSlopeLimitingR) / (1 + m_dSlopeLimitingR * m_dSlopeLimitingR);
                return std::min(l_dFirstTerm, m_dRightSlopeLimit);
            }
    }

double Simulation::m_SL_Minbee()
    {
        if (m_dSlopeLimitingR <= 0.0)
            {
                return 0.0;
            }
        else if (m_dSlopeLimitingR > 0.0 && m_dSlopeLimitingR <= 1.0)
            {
                return m_dSlopeLimitingR;
            }
        else 
            {
                return std::min(1.0, m_dRightSlopeLimit);
            }
    }

