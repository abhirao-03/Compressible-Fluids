#include "simulation.h"

double Simulation::m_dRarefactionVelocityMovement(const vec3& u_vPrimitiveInputState, const double& u_dPressureGuess)
    {
        double f_dEntropyConstantSoundSpeed = std::pow(m_dGamma * u_vPrimitiveInputState[2] / u_vPrimitiveInputState[0], (1.0/2.0));
        
        double f_dAcousticTerm = 2 * f_dEntropyConstantSoundSpeed / (m_dGamma - 1);
        double f_dPressureExponent = (m_dGamma - 1)/(2*m_dGamma);
        double f_dPressureTerm = std::pow((u_dPressureGuess/u_vPrimitiveInputState[2]), f_dPressureExponent) - 1;
        
        return f_dAcousticTerm * f_dPressureTerm;
    }

double Simulation::m_dShockwaveVelocityMovement(const vec3& u_vPrimitiveInputState, const double& u_dPressureGuess)
    {
        double f_dATerm = 2/((m_dGamma + 1)*u_vPrimitiveInputState[0]);
        double f_dBTerm = ((m_dGamma - 1)/(m_dGamma + 1)) * u_vPrimitiveInputState[2];
        
        double f_dRootTerm = std::pow(((f_dATerm)/(u_dPressureGuess + f_dBTerm)), 0.5);
        
        return (u_dPressureGuess - u_vPrimitiveInputState[2]) * f_dRootTerm;
    }
