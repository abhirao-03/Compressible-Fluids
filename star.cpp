#include "simulation.h"

double Simulation::m_dRarefactionVelocityMovement(const vec3& u_vPrimitiveInputState, const double& u_dPressureGuess)
    {
        double f_dEntropyConstantSoundSpeed = std::pow(m_dGamma * u_vPrimitiveInputState[2] / u_vPrimitiveInputState[0], (1.0/2.0));
        
        double f_dAcousticTerm = 2 * f_dEntropyConstantSoundSpeed / (m_dGamma - 1);
        double f_dPressureExponent = (m_dGamma - 1)/(2*m_dGamma);
        double f_dPressureTerm = std::pow((u_dPressureGuess/u_vPrimitiveInputState[2]), f_dPressureExponent) - 1;
        
        return f_dAcousticTerm * f_dPressureTerm;
    }
    
double Simulation::m_dDerivativeRVM(const vec3& u_vPrimitiveInputState, const double& u_dPressureGuess)
    {
        double f_dEntropyConstantSoundSpeed = std::pow(m_dGamma * u_vPrimitiveInputState[2] / u_vPrimitiveInputState[0], (1.0/2.0));
        double f_dPressureExponent = -(m_dGamma + 1)/(2 * m_dGamma);

        return ((1)/(u_vPrimitiveInputState[0] * f_dEntropyConstantSoundSpeed)) * std::pow((u_dPressureGuess/u_vPrimitiveInputState[2]),f_dPressureExponent);
    }

double Simulation::m_dShockwaveVelocityMovement(const vec3& u_vPrimitiveInputState, const double& u_dPressureGuess)
    {
        double f_dATerm = 2/((m_dGamma + 1)*u_vPrimitiveInputState[0]);
        double f_dBTerm = ((m_dGamma - 1)/(m_dGamma + 1)) * u_vPrimitiveInputState[2];
        
        double f_dRootTerm = std::pow(((f_dATerm)/(u_dPressureGuess + f_dBTerm)), 0.5);
        
        return (u_dPressureGuess - u_vPrimitiveInputState[2]) * f_dRootTerm;
    }
    
double Simulation::m_dDerivativeSVM(const vec3& u_vPrimitiveInputState, const double& u_dPressureGuess)
    {
        double f_dATerm = 2/((m_dGamma + 1)*u_vPrimitiveInputState[0]);
        double f_dBTerm = ((m_dGamma - 1)/(m_dGamma + 1)) * u_vPrimitiveInputState[2];
        
        double f_dRootTerm = std::pow(((f_dATerm)/(u_dPressureGuess + f_dBTerm)), 0.5);
        
        return f_dRootTerm * (1 - ((u_dPressureGuess - u_vPrimitiveInputState[2])/(2*(u_dPressureGuess + f_dBTerm))));
    }

double Simulation::m_CalculateStarPressure(const vec3& u_vLeftPrimitiveState, const vec3& u_vRightPrimitiveState)
    {
        int f_iIterations = 20;
        double f_dCurrentPressureGuess = (1.0/2.0) * (u_vLeftPrimitiveState[2] + u_vRightPrimitiveState[2]);
        double f_dOldPressureGuess = f_dCurrentPressureGuess;
        
        for(int i = 0; i <= f_iIterations; i++)
            {
                // std::cout << "On iteration " << i << std::endl;
                
                double f_dLeftFullValue;
                double f_dLeftDerivative;
                
                double f_dRightFullValue;
                double f_dRightDerivative;
                
                if (f_dOldPressureGuess > u_vLeftPrimitiveState[2])
                    {
                        f_dLeftFullValue  = m_dShockwaveVelocityMovement(u_vLeftPrimitiveState, f_dOldPressureGuess);
                        f_dLeftDerivative = m_dDerivativeSVM(u_vLeftPrimitiveState, f_dOldPressureGuess);
                    }
                
                else
                    {
                        f_dLeftFullValue  = m_dRarefactionVelocityMovement(u_vLeftPrimitiveState, f_dOldPressureGuess);
                        f_dLeftDerivative = m_dDerivativeRVM(u_vLeftPrimitiveState, f_dOldPressureGuess);
                    }
                
                if (f_dOldPressureGuess > u_vRightPrimitiveState[2])
                    {
                        f_dRightFullValue  = m_dShockwaveVelocityMovement(u_vRightPrimitiveState, f_dOldPressureGuess);
                        f_dRightDerivative = m_dDerivativeSVM(u_vRightPrimitiveState, f_dOldPressureGuess);
                    }
                else
                    {
                        f_dRightFullValue  = m_dRarefactionVelocityMovement(u_vRightPrimitiveState, f_dOldPressureGuess);
                        f_dRightDerivative = m_dDerivativeRVM(u_vRightPrimitiveState, f_dOldPressureGuess);
                    }
                    
                double f_dTotalFunction = f_dRightFullValue + f_dLeftFullValue + (u_vRightPrimitiveState[1] - u_vLeftPrimitiveState[1]);
                double f_dTotalDerivative = f_dRightDerivative + f_dLeftDerivative;
                
                f_dCurrentPressureGuess = f_dOldPressureGuess - (f_dTotalFunction/f_dTotalDerivative);
                f_dOldPressureGuess = f_dCurrentPressureGuess;
            }
        return f_dCurrentPressureGuess;
    }

double Simulation::m_CalculateStarVelocity(const vec3& u_vLeftPrimitiveState, const vec3& u_vRightPrimitiveState)
    {
        double f_dPressure = m_CalculateStarPressure(u_vLeftPrimitiveState, u_vRightPrimitiveState);
        
        double f_dStarVel;
        
        if (f_dPressure > u_vLeftPrimitiveState[2])
            {
                f_dStarVel = u_vLeftPrimitiveState[1] - m_dShockwaveVelocityMovement(u_vLeftPrimitiveState, f_dPressure);
            }
        else
            {
                f_dStarVel = u_vLeftPrimitiveState[1] - m_dRarefactionVelocityMovement(u_vLeftPrimitiveState, f_dPressure);
            }
            
        return f_dStarVel;
    }
    
std::vector<double> Simulation::m_CalculateStarDensities(const vec3& u_vLeftPrimitiveState, const vec3& u_vRightPrimitiveState)
    {
        double f_dPressure = m_CalculateStarPressure(u_vLeftPrimitiveState, u_vRightPrimitiveState);
        
        double f_dStarDensityLeft;
        double f_dStarDensityRight;
        
        if (f_dPressure <= u_vLeftPrimitiveState[2])
            {
                f_dStarDensityLeft = u_vLeftPrimitiveState[0] * std::pow((f_dPressure/u_vLeftPrimitiveState[2]), 1/m_dGamma);
                
            }
        else
            {
                f_dStarDensityLeft = u_vLeftPrimitiveState[0] * \
                    ((f_dPressure/u_vLeftPrimitiveState[2]) + (m_dGamma - 1)/(m_dGamma + 1))/ \
                    (1 + ((f_dPressure/u_vLeftPrimitiveState[2]) * (m_dGamma - 1)/(m_dGamma + 1)));
            }
            
        if (f_dPressure <= u_vRightPrimitiveState[2])
            {
                f_dStarDensityRight = u_vRightPrimitiveState[0] * std::pow((f_dPressure/u_vRightPrimitiveState[2]), 1/m_dGamma);
            }
        else
            {
                f_dStarDensityRight = u_vRightPrimitiveState[0] * \
                    ((f_dPressure/u_vRightPrimitiveState[2]) + (m_dGamma - 1)/(m_dGamma + 1))/ \
                    (1 + ((f_dPressure/u_vRightPrimitiveState[2]) * (m_dGamma - 1)/(m_dGamma + 1)));
            }
        
        return {f_dStarDensityLeft, f_dStarDensityRight};
    }

