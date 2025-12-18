#include <cmath>
#include <fstream>
#include <vector>
#include "EulerVectors.h"
static const double PI = 4*atan(1);

class Simulation
{
    private:
        double m_dXStart;
        double m_dXEnd;
        double m_dTimeStart;
        double m_dTimeEnd;

        int m_iNumPoints;
        int m_iNumGhostCells;

        double m_dDeltaX;
        double m_dRelaxation;
        double m_dDeltaT;

        double m_dGamma = 1.4;
        double m_dOmega = 0.0;

        std::vector<vec3> m_vec_dU;
        std::vector<vec3> m_vec_dFluxes;

        std::vector<vec3> m_vec_LeftReconstructed;
        std::vector<vec3> m_vec_RightReconstructed;
        std::vector<vec3> m_vec_dFluxesReconstructed;
    
        std::vector<vec3> m_vec_dUNext;
        


        // ---------------------------------- The following was implemented using Copilot ----------------------------------

        // using ProgressionFunction = void (Simulation::*)(std::vector<vec3>& vec_dInputVector, std::vector<vec3>& vec_dUpdateVector);
        // ProgressionFunction m_ProgressionFunction = nullptr;

        using LimitingFunction = vec3 (Simulation::*)(const int& l_iIterValue);
        LimitingFunction m_LimitingFunction = nullptr;

        // ------------------------------------------------------------------------------------------------------------------

        public:

        enum class InitialCondition
            {
                INITIAL_ONE = 1,
                INITIAL_TWO = 2,
                INITIAL_THREE = 3,
                INITIAL_FOUR = 4,
                TORO_INIT_ONE = 5,
                TORO_INIT_TWO = 6,
                TORO_INIT_THREE = 7,
                TORO_INIT_FOUR = 8,
                TORO_INIT_FIVE = 9,
                SINE_WAVE = 10
            };

        // enum ProgressionMethod
        //     {
        //         LAXFRIEDRICHS = 1,
        //         RICHTMYER = 2,
        //         FORCE = 3
        //     };

        enum SlopeLimiter
            {
                SUPERBEE = 1,
                VAN_LEER = 2,
                VAN_ALBADA = 3,
                MINBEE = 4
            };

        InitialCondition m_eInitialCondition;
        // ProgressionMethod m_eProgressionMethod;
        SlopeLimiter m_eSlopeLimiter;

        // member initialization
        Simulation(
                    double dxStart,
                    double dxEnd,
                    double dTimeStart,
                    double dTimeEnd,
                    double dRelaxation,
                    double dGamma,
                    int iNumPoints,
                    int iNumGhostCells,
                    InitialCondition eInitialCondition,
                    // ProgressionMethod eProgressionMethod,
                    SlopeLimiter eSlopeLimiter
                )
            :
            m_dXStart(dxStart),
            m_dXEnd(dxEnd),
            m_dTimeStart(dTimeStart),
            m_dTimeEnd(dTimeEnd),
            m_dRelaxation(dRelaxation),
            m_dGamma(dGamma),
            m_iNumPoints(iNumPoints),
            m_iNumGhostCells(iNumGhostCells),
            m_eInitialCondition(eInitialCondition),
            // m_eProgressionMethod(eProgressionMethod),
            m_eSlopeLimiter(eSlopeLimiter)
            {
                m_dDeltaX = (m_dXEnd - m_dXStart) / m_iNumPoints;
                m_dDeltaT = m_dRelaxation * m_dDeltaX;

                m_vec_dU.resize(m_iNumGhostCells + m_iNumPoints);
                m_vec_dFluxes.resize(m_iNumGhostCells + m_iNumPoints);
                m_vec_LeftReconstructed.resize(m_iNumGhostCells + m_iNumPoints);
                m_vec_RightReconstructed.resize(m_iNumGhostCells + m_iNumPoints);
                m_vec_dFluxesReconstructed.resize(m_iNumGhostCells + m_iNumPoints);
                m_vec_dUNext.resize(m_iNumGhostCells + m_iNumPoints);

            }

        void InitialOne(std::vector<vec3>& vec_dU);
        void InitialTwo(std::vector<vec3>& vec_dU);
        void InitialThree(std::vector<vec3>& vec_dU);
        void InitialFour(std::vector<vec3>& vec_dU);

        void ToroInitialOne(std::vector<vec3>& vec_dU);
        void ToroInitialTwo(std::vector<vec3>& vec_dU);
        void ToroInitialThree(std::vector<vec3>& vec_dU);
        void ToroInitialFour(std::vector<vec3>& vec_dU);
        void ToroInitialFive(std::vector<vec3>& vec_dU);

        void InitialSineWave(std::vector<vec3>& vec_dU);

        void m_fvm_LaxFriedrichs(std::vector<vec3>& vec_dInputVector, std::vector<vec3>& vec_dUpdateVector);
        void m_fvm_Richtmyer(std::vector<vec3>& vec_dInputVector, std::vector<vec3>& vec_dUpdateVector);
        void m_fvm_FORCE(std::vector<vec3>& vec_dInputVector, std::vector<vec3>& vec_dUpdateVector);

        vec3 m_SL_Superbee(const int& l_iIterValue);
        vec3 m_SL_VanLeer(const int& l_iIterValue);
        vec3 m_SL_VanAlbada(const int& l_iIterValue);
        vec3 m_SL_Minbee(const int& l_iIterValue);


        void GetU();
        double GetEnergy(const double& u_dDensity, const double& u_dVelocity, const double& u_dPressure);

        vec3 m_GetPrimitives(const vec3& f_vec3_U);
        vec3 m_GetSlopeLimitingR(const int& l_iIterValue);
        vec3 m_GetSlopeMeasure(const int& t_iCellValue);

        void m_ReconstructData();
        void m_GetReconstructedFluxes();
        void m_EvolveHalfTimeStep();
        
        vec3 m_EulerFluxFunction(const vec3& f_vec3_U)
            {
                vec3 prims = m_GetPrimitives(f_vec3_U);

                double& h_dDensity = prims[0];
                double& h_dVelocity = prims[1];
                double& h_dPressure = prims[2];

                double d_FirstFlux = h_dDensity * h_dVelocity;
                double d_SecondFlux = h_dDensity * pow(h_dVelocity, 2.0) + h_dPressure;
                double d_ThirdFlux = (f_vec3_U[2] + h_dPressure) * h_dVelocity;

                return vec3(d_FirstFlux, d_SecondFlux, d_ThirdFlux);
            }

        void SetTimeStep()
            {
                double f_dMaxInformationSpeed = 0.0;

                for (int i = 1; i < m_vec_dU.size() - 1; i++)
                    {
                        vec3 l_vec3_Primitive = m_GetPrimitives(m_vec_dU[i]);
                        double l_dDensity = l_vec3_Primitive[0];
                        double l_dVelocity   = l_vec3_Primitive[1];
                        double l_dPressure   = l_vec3_Primitive[2];

                        double l_dSoundSpeed = std::sqrt(m_dGamma * l_dPressure / l_dDensity);

                        double l_dCurrentMax = std::abs(l_dVelocity) + l_dSoundSpeed;

                        if (l_dCurrentMax > f_dMaxInformationSpeed)
                            {
                                f_dMaxInformationSpeed = l_dCurrentMax;
                            }
                    };

                if (f_dMaxInformationSpeed > 0.0)
                {
                    m_dDeltaT = m_dRelaxation * m_dDeltaX / f_dMaxInformationSpeed;
                } else  {
                    m_dDeltaT = 1e-4;
                }
            }

        void SetInitialCondition()
            {
                switch (m_eInitialCondition)
                    {
                        case InitialCondition::INITIAL_ONE:
                            InitialOne(m_vec_dU);
                            break;

                        case InitialCondition::INITIAL_TWO:
                            InitialTwo(m_vec_dU);
                            break;

                        case InitialCondition::INITIAL_THREE:
                            InitialThree(m_vec_dU);
                            break;

                        case InitialCondition::INITIAL_FOUR:
                            InitialFour(m_vec_dU);
                            break;

                        case InitialCondition::TORO_INIT_ONE:
                            m_dTimeEnd = 0.25;
                            ToroInitialOne(m_vec_dU);
                            break;

                        case InitialCondition::TORO_INIT_TWO:
                            m_dTimeEnd = 0.15;
                            ToroInitialTwo(m_vec_dU);
                            break;

                        case InitialCondition::TORO_INIT_THREE:
                            m_dTimeEnd = 0.012;
                            ToroInitialThree(m_vec_dU);
                            break;

                        case InitialCondition::TORO_INIT_FOUR:
                            m_dTimeEnd = 0.035;
                            ToroInitialFour(m_vec_dU);
                            break;

                        case InitialCondition::TORO_INIT_FIVE:
                            m_dTimeEnd = 0.035;
                            ToroInitialFive(m_vec_dU);
                            break;

                        case InitialCondition::SINE_WAVE:
                            m_dTimeEnd = 1.0;
                            InitialSineWave(m_vec_dU);
                            break;

                    }
            }

        // void SetProgressionMethod()
        //     {
        //         switch (m_eProgressionMethod)
        //             {
        //                 case ProgressionMethod::LAXFRIEDRICHS:
        //                     m_ProgressionFunction = &Simulation::m_fvm_LaxFriedrichs;
        //                     break;

        //                 case ProgressionMethod::RICHTMYER:
        //                     m_ProgressionFunction = &Simulation::m_fvm_Richtmyer;
        //                     break;

        //                 case ProgressionMethod::FORCE:
        //                     m_ProgressionFunction = &Simulation::m_fvm_FORCE;
        //                     break;

        //                 default:
        //                     m_ProgressionFunction = &Simulation::m_fvm_FORCE;
        //                     break;
        //             }

        //     }

        void SetLimitingFunction()
            {
                switch (m_eSlopeLimiter)
                    {
                        case SlopeLimiter::SUPERBEE:
                            m_LimitingFunction = &Simulation::m_SL_Superbee;
                            break;

                        case SlopeLimiter::VAN_LEER:
                            m_LimitingFunction = &Simulation::m_SL_VanLeer;
                            break;

                        case SlopeLimiter::VAN_ALBADA:
                            m_LimitingFunction = &Simulation::m_SL_VanAlbada;
                            break;

                        case SlopeLimiter::MINBEE:
                            m_LimitingFunction = &Simulation::m_SL_Minbee;
                            break;

                        default:
                            m_LimitingFunction = &Simulation::m_SL_Minbee;
                            break;
                    }
            }

        void SetBoundaryConditions()
            {
                m_vec_dU[0] = m_vec_dU[1];
                m_vec_dU[m_iNumGhostCells + m_iNumPoints - 1] = m_vec_dU[m_iNumPoints];
            }

        void Evolve();
};
