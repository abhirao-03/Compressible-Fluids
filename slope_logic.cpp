#include "simulation.h"

vec3 Simulation::GetSlopeLimitingR(const int& t_iCellValue)
    {
        const double eps = 1e-12;

        vec3 l_dNumerator = m_vec_dU[t_iCellValue] - m_vec_dU[t_iCellValue - 1];
        vec3 l_dDenominator = m_vec_dU[t_iCellValue + 1]  - m_vec_dU[t_iCellValue];

        vec3 i_vec3SlopeLimitingR;

        for (int k = 0; k < l_dNumerator.size(); ++k)
            {
                if (std::abs(l_dDenominator[k]) > eps)
                    {
                        i_vec3SlopeLimitingR[k] = l_dNumerator[k] / l_dDenominator[k];
                    }
                else 
                    {
                        i_vec3SlopeLimitingR[k] = 0.0;
                    }
            }

        return i_vec3SlopeLimitingR;

    }

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

vec3 Simulation::m_SL_Superbee(const int& l_iIterValue)
    {
        vec3 l_dSlopeLimitingR = GetSlopeLimitingR(l_iIterValue);
        vec3 m_dLeftSlopeLimit = (2.0 * l_dSlopeLimitingR) / (1.0 + l_dSlopeLimitingR);
        vec3 m_dRightSlopeLimit = 2.0 / (1.0 + l_dSlopeLimitingR);

        vec3 l_vResults = vec3();

        for (int i = 0; i < l_dSlopeLimitingR.size(); i++)
            {
            if (l_dSlopeLimitingR[i] <= 0.0)
                {
                    l_vResults[i] = 0.0;
                }
            else if (l_dSlopeLimitingR[i] > 0.0 && l_dSlopeLimitingR[i] <= 1.0/2.0)
                {
                    l_vResults[i] = 2.0 * l_dSlopeLimitingR[i];
                }
            else if (l_dSlopeLimitingR[i] > 1.0/2.0 and l_dSlopeLimitingR[i] <= 1.0)
                {
                    l_vResults[i] = 1.0;
                }
            else
                {
                    l_vResults[i] = std::min(l_dSlopeLimitingR[i], std::min(m_dRightSlopeLimit[i], 2.0));
                }
            }
        
        return l_vResults;
    }

vec3 Simulation::m_SL_VanLeer(const int& l_iIterValue)
    {
        vec3 l_dSlopeLimitingR = GetSlopeLimitingR(l_iIterValue);
        vec3 m_dLeftSlopeLimit = (2.0 * l_dSlopeLimitingR) / (1.0 + l_dSlopeLimitingR);
        vec3 m_dRightSlopeLimit = 2.0 / (1.0 + l_dSlopeLimitingR);

        vec3 l_vResults = vec3();

        for (int i = 0; i < l_dSlopeLimitingR.size(); i++)
            {
                if (l_dSlopeLimitingR[i] <= 0.0)
                    {
                        l_vResults[i] = 0.0;
                    }
                else
                    {
                        l_vResults[i] = std::min(m_dLeftSlopeLimit[i], m_dRightSlopeLimit[i]);
                    }
            }
        
        return l_vResults;
    }

vec3 Simulation::m_SL_VanAlbada(const int& l_iIterValue)
    {
        vec3 l_dSlopeLimitingR = GetSlopeLimitingR(l_iIterValue);
        vec3 m_dLeftSlopeLimit = (2.0 * l_dSlopeLimitingR) / (1.0 + l_dSlopeLimitingR);
        vec3 m_dRightSlopeLimit = 2.0 / (1.0 + l_dSlopeLimitingR);

        vec3 l_vResults = vec3();
        
        for (int i = 0; i < l_dSlopeLimitingR.size(); i++)
            {
                if (l_dSlopeLimitingR[i] <= 0.0)
                    {
                        l_vResults[i] = 0.0;
                    }
                else
                    {
                        double l_dFirstTerm = l_dSlopeLimitingR[i] * (1 + l_dSlopeLimitingR[i]) / (1 + l_dSlopeLimitingR[i] * l_dSlopeLimitingR[i]);
                        l_vResults[i] = std::min(l_dFirstTerm, m_dRightSlopeLimit[i]);
                    }
            }

        return l_vResults;
    }

vec3 Simulation::m_SL_Minbee(const int& l_iIterValue)
    {
        vec3 l_dSlopeLimitingR = GetSlopeLimitingR(l_iIterValue);
        vec3 m_dLeftSlopeLimit = (2.0 * l_dSlopeLimitingR) / (1.0 + l_dSlopeLimitingR);
        vec3 m_dRightSlopeLimit = 2.0 / (1.0 + l_dSlopeLimitingR);

        vec3 l_vResults = vec3();
        
        for (int i = 0; i < l_dSlopeLimitingR.size(); i++)
            {
                if (l_dSlopeLimitingR[i] <= 0.0)
                    {
                        l_vResults[i] = 0.0;
                    }
                else if (l_dSlopeLimitingR[i] > 0.0 && l_dSlopeLimitingR[i] <= 1.0)
                    {
                        l_vResults[i] = l_dSlopeLimitingR[i];
                    }
                else 
                    {
                        l_vResults[i] = std::min(1.0, m_dRightSlopeLimit[i]);
                    }   
            }
        
        return l_vResults;
    }
