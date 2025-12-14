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
        double m_dAdvectionCoefficient;

        int m_iNumPoints;
        int m_iNumGhostCells;

        double m_dDeltaX = (m_dXStart - m_dXEnd) / m_iNumPoints;
        double m_dRelaxation;
        double m_dDeltaT = m_dRelaxation * m_dDeltaX;

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
                SHOCKWAVE = 1,
                RAREFACTION = 2,
                TOROINITIAL = 3,
                COSINE = 4
            };

        enum ProgressionMethod
            {
                LAXFRIEDRICHS = 1,
                RICHTMYER = 2,
                FORCE = 3,
                GODUNOV = 4
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
                    double dAdvectionCoefficient,
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
            m_dAdvectionCoefficient(dAdvectionCoefficient),
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
        
        // INITIAL CONDITION SETTERS
        void ShockWave(std::vector<double>& vec_dU);
        void Rarefaction(std::vector<double>& vec_dU);
        void ToroInitial(std::vector<double>& vec_dU);
        void Cosine(std::vector<double>& vec_dU);

        void m_fvm_LaxFriedrichs();
        void m_fvm_Richtmyer();
        void m_fvm_FORCE();
        void m_fvm_Godunov();

        void GetU();

        double m_BurgersFluxFunction(const double& u)
            {
                return 0.5 * pow(u, 2.0);
            }

        void SetTimeStep()
            {};

        // void SetInitialCondition()
        //     {
        //         switch (m_eInitialCondition)
        //             {
        //                 case InitialCondition::SHOCKWAVE:
        //                     ShockWave(m_vec_dU);
        //                     break;
                        
        //                 case InitialCondition::RAREFACTION:
        //                     Rarefaction(m_vec_dU);
        //                     break;
                        
        //                 case InitialCondition::TOROINITIAL:
        //                     m_dTimeEnd = 1.5;
        //                     m_dXEnd = 1.5;
        //                     m_dDeltaX = (m_dXEnd - m_dXStart) / m_iNumPoints;
        //                     m_dDeltaT = m_dRelaxation * m_dDeltaX;
        //                     m_vec_dU.resize(m_iNumGhostCells + m_iNumPoints + 1);
        //                     m_vec_dUNext.resize(m_iNumGhostCells + m_iNumPoints + 1);
        //                     ToroInitial(m_vec_dU);
        //                     break;
                        
        //                 case InitialCondition::COSINE:
        //                     Cosine(m_vec_dU);
        //                     break;
        //             }
        //     }

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
                        
                        case ProgressionMethod::GODUNOV:
                            m_ProgressionFunction = &Simulation::m_fvm_Godunov;
                            break;
                        
                        default:
                            m_ProgressionFunction = &Simulation::m_fvm_LaxFriedrichs;
                            break;
                    }

            }
            
        void SetBoundaryConditions()
            {
                m_vec_dU[0] = m_vec_dU[1];
                m_vec_dU[m_iNumGhostCells + m_iNumPoints - 1] = m_vec_dU[m_iNumPoints];
            }

        void SetFluxes();
        void Evolve();
};