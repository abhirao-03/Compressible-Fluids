#include <cmath>
#include <fstream>
#include <vector>
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

        std::vector<double> m_vec_dU;
        std::vector<double> m_vec_dUNext;
        
        double m_dCourantLaxFlewyConstant = m_dAdvectionCoefficient * m_dDeltaT/m_dDeltaX;
    

        // -- The following was implemented using AI
        
        using ProgressionFunction = void (Simulation::*)(const std::vector<double>&, std::vector<double>&, const int&);
        ProgressionFunction m_ProgressionFunction = nullptr;
        
        // --
    public:

        enum class InitialCondition
            {
                SIN = 1,
                BOX = 2,
                EXP = 3
            };
        

        InitialCondition m_eInitialCondition;

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
                    InitialCondition eInitialCondition
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
            m_eInitialCondition(eInitialCondition)
            {
                m_dDeltaX = (m_dXEnd - m_dXStart) / m_iNumPoints;
                m_dDeltaT = m_dRelaxation * m_dDeltaX;
                m_vec_dU.resize(m_iNumGhostCells + m_iNumPoints + 1);
                m_vec_dUNext.resize(m_iNumGhostCells + m_iNumPoints + 1);
                m_dCourantLaxFlewyConstant = m_dAdvectionCoefficient * m_dDeltaT/m_dDeltaX;
            }
        
        // INITIAL CONDITION SETTERS
        void ExponentInitial(std::vector<double>& vec_dU);
        void BoxInitial(std::vector<double>& vec_dU);
        void SinInitial(std::vector<double>& vec_dU);


        void SetInitialCondition()
            {
                switch (m_eInitialCondition)
                    {
                        case InitialCondition::SIN:
                            SinInitial(m_vec_dU);
                            break;
                        
                        case InitialCondition::BOX:
                            BoxInitial(m_vec_dU);
                            break;
                        
                        case InitialCondition::EXP:
                            ExponentInitial(m_vec_dU);
                            break;
                    }
            }

        void PerformTimeSteps();
};