#include "simulation.h"

vec3 Simulation::m_GetExactSolution(double x, double t)
    {
        vec3 r_vLeft;
        vec3 r_vRight;
        double r_dX0;
        
        m_GetInitialStates(r_vLeft, r_vRight, r_dX0);
        
        double f_dStarPressure = m_CalculateStarPressure(r_vLeft, r_vRight);
        double f_dStarVelocity = m_CalculateStarVelocity(r_vLeft, r_vRight);
        std::vector f_vStarDensities = m_CalculateStarDensities(r_vLeft, r_vRight);
        
        double f_dStarLeftDensity = f_vStarDensities[0];
        double f_dStarRightDensity = f_vStarDensities[1];
        
        double f_dLeftSoundSpeed = std::pow(m_dGamma * r_vLeft[2] / r_vLeft[0], 0.5);
        double f_dRightSoundSpeed = std::pow(m_dGamma * r_vRight[2] / r_vRight[0], 0.5);
        
        double f_dLeftStarSoundSpeed = std::pow(m_dGamma * f_dStarPressure / f_dStarLeftDensity, 0.5);
        double f_dRightStarSoundSpeed = std::pow(m_dGamma * f_dStarPressure / f_dStarRightDensity, 0.5);
        
        double f_dSampleSpeed = (x - r_dX0) / t;
        
        double f_dGammaConstantPos = (m_dGamma + 1) / (2 * m_dGamma);
        double f_dGammaConstantNeg = (m_dGamma - 1) / (2 * m_dGamma);
        
        
        if (f_dSampleSpeed < f_dStarVelocity)
            {
                if (f_dStarPressure > r_vLeft[2])
                    {
                        double t_dRootTerm = f_dGammaConstantPos * (f_dStarPressure/r_vLeft[2]) + f_dGammaConstantNeg;
                        double t_dLeftShock = r_vLeft[1] - (f_dLeftSoundSpeed * std::pow(t_dRootTerm, 0.5));
                        
                        if (f_dSampleSpeed < t_dLeftShock)
                            {
                                return r_vLeft;
                            }
                        else
                            {
                                return {f_dStarLeftDensity, f_dStarVelocity, f_dStarPressure};
                            }
                    }
                else
                    {
                        double f_dHeadSpeed = r_vLeft[1] - f_dLeftSoundSpeed;
                        double f_dTailSpeed = f_dStarVelocity - f_dLeftStarSoundSpeed;
                        
                        if (f_dSampleSpeed < f_dHeadSpeed)
                            {
                                return r_vLeft;
                            }
                        else if (f_dSampleSpeed > f_dTailSpeed)
                            {
                                return {f_dStarLeftDensity, f_dStarVelocity, f_dStarPressure};
                            }
                        else
                            {
                                double t_dVelocity   = (2/(m_dGamma + 1)) * (f_dLeftSoundSpeed + r_vLeft[1]*(m_dGamma-1)/2 + f_dSampleSpeed);
                                double t_dSoundSpeed = f_dLeftSoundSpeed + ((m_dGamma - 1)/2)*(r_vLeft[1] - t_dVelocity);
                                double t_dDensity    = r_vLeft[0] * std::pow(t_dSoundSpeed / f_dLeftSoundSpeed, (2/(m_dGamma - 1)));
                                double t_dPressure   = r_vLeft[2] * std::pow(t_dSoundSpeed / f_dLeftSoundSpeed, (2*m_dGamma/(m_dGamma - 1)));
                                
                                return vec3{t_dDensity, t_dVelocity, t_dPressure};
                            }
                    }
            }
        else
            {
                if (f_dStarPressure > r_vRight[2])
                    {
                        double t_dRootTerm = f_dGammaConstantPos * (f_dStarPressure/r_vRight[2]) + f_dGammaConstantNeg;
                        double t_dRightShock = r_vRight[1] + (f_dRightSoundSpeed * std::pow(t_dRootTerm, 0.5));
                        
                        if (f_dSampleSpeed > t_dRightShock)
                            {
                                return r_vRight;
                            }
                        else
                            {
                                return vec3{f_dStarRightDensity, f_dStarVelocity, f_dStarPressure};
                            }
                    }
                else
                    {
                        double f_dHeadSpeed = r_vRight[1] + f_dRightSoundSpeed;
                        double f_dTailSpeed = f_dStarVelocity + f_dRightStarSoundSpeed;
                        
                        if (f_dSampleSpeed > f_dHeadSpeed)
                            {
                                return r_vRight;
                            }
                        else if (f_dSampleSpeed < f_dTailSpeed)
                            {
                                return vec3{f_dStarRightDensity, f_dStarVelocity, f_dStarPressure};
                            }
                        else
                            {
                                double t_dVelocity   = (2/(m_dGamma + 1)) * (-f_dRightSoundSpeed + r_vRight[1]*(m_dGamma-1)/2 + f_dSampleSpeed);
                                double t_dSoundSpeed = f_dRightSoundSpeed - ((m_dGamma - 1)/2)*(r_vRight[1] - t_dVelocity);
                                double t_dDensity    = r_vRight[0] * std::pow(t_dSoundSpeed / f_dRightSoundSpeed, (2/(m_dGamma - 1)));
                                double t_dPressure   = r_vRight[2] * std::pow(t_dSoundSpeed / f_dRightSoundSpeed, (2*m_dGamma/(m_dGamma - 1)));
                                
                                return vec3{t_dDensity, t_dVelocity, t_dPressure};
                            }
                    }
            }
    }
