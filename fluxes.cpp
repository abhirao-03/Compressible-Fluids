#include "simulation.h"
#include <cmath>

void Simulation::m_fvm_LaxFriedrichs()
    {
        for (int i = 0; i < m_vec_dU.size() - 1; i++)
            {
                double t_dULeft = m_vec_dU[i];
                double t_dURight = m_vec_dU[i + 1];

                double t_dFluxLeft = m_BurgersFluxFunction(t_dULeft);
                double t_dFluxRight = m_BurgersFluxFunction(t_dURight);

                m_vec_dFluxes[i] = 0.5 * (t_dFluxLeft + t_dFluxRight) + 0.5 * (m_dDeltaX/m_dDeltaT) * (t_dULeft - t_dURight);
            }
    }

void Simulation::m_fvm_Richtmyer()
    {
        double u_halfs;

        for (int i = 0; i < m_vec_dFluxes.size() - 1; i++)
            {
                double u_left = m_vec_dU[i];
                double u_right = m_vec_dU[i + 1];

                double u_FluxLeft = m_BurgersFluxFunction(u_left);
                double u_FluxRight = m_BurgersFluxFunction(u_right);

                u_halfs = 0.5 * (u_left + u_right) - 0.5 * (m_dDeltaT / m_dDeltaX) * (u_FluxRight - u_FluxLeft);

                m_vec_dFluxes[i] = m_BurgersFluxFunction(u_halfs);
            }   
    }

void Simulation::m_fvm_FORCE()
    {
        m_fvm_LaxFriedrichs();
        std::vector<double> t_vec_LFFluxes = m_vec_dFluxes;

        m_fvm_Richtmyer();
        std::vector<double> t_vec_RichtmyerFluxes = m_vec_dFluxes;

        for (int i = 0; i < m_vec_dFluxes.size() - 1; i++)
            {
                m_vec_dFluxes[i] = 0.5 * (t_vec_LFFluxes[i] + t_vec_RichtmyerFluxes[i]);
            }
    }

void Simulation::m_fvm_Godunov()
    {
        for (int i = 0; i < m_vec_dU.size() - 1; i++)
            {
                double t_dSelectedU;
                double t_dCurrentU = m_vec_dU[i];
                double t_dNextU = m_vec_dU[i + 1];

                if (t_dCurrentU > t_dNextU)
                    {
                        double t_dShockSpeed = 0.5 * (m_vec_dU[i] + m_vec_dU[i + 1]);

                        if (t_dShockSpeed > 0)
                            {
                                t_dSelectedU = t_dCurrentU;

                            }
                        else
                            {
                                t_dSelectedU = t_dNextU;
                            }
                    }
                    
                else 
                    {
                        if (t_dCurrentU > 0)
                            {  
                                t_dSelectedU = t_dCurrentU;
                            }
                        else if (t_dCurrentU <= 0 && 0 <= t_dNextU)
                            {
                                t_dSelectedU = 0;
                            }
                        else if (t_dNextU <= 0)
                            {
                                t_dSelectedU = t_dNextU;
                            }
                    }
                
            m_vec_dFluxes[i] = m_BurgersFluxFunction(t_dSelectedU);
            }
    }