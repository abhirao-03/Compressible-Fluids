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

        double m_dDeltaX = (m_dXStart - m_dXEnd) / m_iNumPoints;
        double m_dRelaxation;
        double m_dDeltaT = m_dRelaxation * m_dDeltaX;
        double m_dGamma = 1.4;

        std::vector<vec3> m_vec_dU;
        std::vector<vec3> m_vec_dFluxes;
        std::vector<vec3> m_vec_dUNext;

        // ---------------------------------- The following was implemented using Copilot ----------------------------------
        
        using ProgressionFunction = void (Simulation::*)();
        ProgressionFunction m_ProgressionFunction = nullptr;
        
        // ------------------------------------------------------------------------------------------------------------
    
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
            };

        enum ProgressionMethod
            {
                LAXFRIEDRICHS = 1,
                RICHTMYER = 2,
                FORCE = 3
            };
        

        InitialCondition m_eInitialCondition;
        ProgressionMethod m_eProgressionMethod;

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
                    ProgressionMethod eProgressionMethod
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
            m_eProgressionMethod(eProgressionMethod)
            {
                m_dDeltaX = (m_dXEnd - m_dXStart) / m_iNumPoints;
                m_dDeltaT = m_dRelaxation * m_dDeltaX;
                m_vec_dU.resize(m_iNumGhostCells + m_iNumPoints);
                m_vec_dUNext.resize(m_iNumGhostCells + m_iNumPoints);
                m_vec_dFluxes.resize(m_iNumGhostCells + m_iNumPoints);
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

        void m_fvm_LaxFriedrichs();
        void m_fvm_Richtmyer();
        void m_fvm_FORCE();

        void GetU();
        vec3 GetPrimitives(const vec3& f_vec3_U);
        double GetEnergy(const double& u_dDensity, const double& u_dVelocity, const double& u_dPressure);

        double m_BurgersFluxFunction(const double& u)
            {
                return 0.5 * pow(u, 2.0);
            }

        vec3 m_EulerFluxFunction(const vec3& f_vec3_U)
            {
                vec3 prims = GetPrimitives(f_vec3_U);

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

                for (vec3& l_vec3_Cell : m_vec_dU)
                    {
                        vec3 l_vec3_Primitive = GetPrimitives(l_vec3_Cell);
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
                    }
            }

        void SetProgressionMethod()
            {
                switch (m_eProgressionMethod)
                    {
                        case ProgressionMethod::LAXFRIEDRICHS:
                            m_ProgressionFunction = &Simulation::m_fvm_LaxFriedrichs;
                            break;
                        
                        case ProgressionMethod::RICHTMYER:
                            m_ProgressionFunction = &Simulation::m_fvm_Richtmyer;
                            break;

                        case ProgressionMethod::FORCE:
                            m_ProgressionFunction = &Simulation::m_fvm_FORCE;
                            break;
                        
                        default:
                            m_ProgressionFunction = &Simulation::m_fvm_FORCE;
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