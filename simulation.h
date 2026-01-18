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

        double m_dDeltaX;
        double m_dDeltaT;

        double m_dGamma = 1.4;

        std::vector<vec3> m_vec_dU;
        std::vector<vec3> m_vec_dFluxes;
        std::vector<vec3> m_vec_dUNext;
        

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

        InitialCondition m_eInitialCondition;

        // MEMBER INITIALISATION -------------------------------------------------------------------------------
        Simulation(
                    double dxStart,
                    double dxEnd,
                    double dTimeStart,
                    double dTimeEnd,
                    double dGamma,
                    int iNumPoints,
                    InitialCondition eInitialCondition
                )
            :
            m_dXStart(dxStart),
            m_dXEnd(dxEnd),
            m_dTimeStart(dTimeStart),
            m_dTimeEnd(dTimeEnd),
            m_dGamma(dGamma),
            m_eInitialCondition(eInitialCondition)
            {
                m_dDeltaX = (m_dXEnd - m_dXStart) / m_iNumPoints;
                m_vec_dU.resize(m_iNumPoints);
                m_vec_dFluxes.resize(m_iNumPoints);
                m_vec_dUNext.resize(m_iNumPoints);

            }
        // -----------------------------------------------------------------------------------------------------


        // INITIAL CONDITION -----------------------------------------------------------------------------------
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
        // -------------------------------------------------------------------------------------------------------------
        


        // PHYSICS -----------------------------------------------------------------------------------------------------
        void m_GetU();
        double m_GetEnergy(const double& u_dDensity, const double& u_dVelocity, const double& u_dPressure);
        vec3 m_GetPrimitives(const vec3& f_vec3_U);
        vec3 m_EulerFluxFunction(const vec3& f_vec3_U);
        // -------------------------------------------------------------------------------------------------------------



        // ITERATOR ----------------------------------------------------------------------------------------------------
        void Evolve();
        // -------------------------------------------------------------------------------------------------------------
};
