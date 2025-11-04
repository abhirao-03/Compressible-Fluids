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
    
    public:
        enum DifferenceMethod
        {
            BACKWARD = 1,
            FORWARD = 2,
            CENTRAL = 3
        };
        
        DifferenceMethod m_eDifferenceMethod;

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
                    InitialCondition eInitialCondition,
                    DifferenceMethod eDifferenceMethod
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
            m_eDifferenceMethod(eDifferenceMethod)
            {
                m_dDeltaX = (m_dXEnd - m_dXStart) / m_iNumPoints;
                m_dDeltaT = m_dRelaxation * m_dDeltaX;
                m_vec_dU.resize(m_iNumGhostCells + m_iNumPoints + 1);
                m_vec_dUNext.resize(m_iNumGhostCells + m_iNumPoints + 1);
            }

        void ExponentInitial(std::vector<double>& vec_dU);
        void BoxInitial(std::vector<double>& vec_dU);
        void SinInitial(std::vector<double>& vec_dU);

        void BackwardDifference(const std::vector<double>& vec_dOldU, std::vector<double>& vec_dNewU, const int& i_IndexUpdate);
        void ForwardDifference(const std::vector<double>& vec_dOldU, std::vector<double>& vec_dNewU, const int& i_IndexUpdate);
        void CentralDifference(const std::vector<double>& vec_dOldU, std::vector<double>& vec_dNewU, const int& i_IndexUpdate);

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

        void PerformTimeSteps()
        {
            void (Simulation::*difference)(const std::vector<double>&, std::vector<double>&, const int&);

            switch (m_eDifferenceMethod)
                {
                    case DifferenceMethod::BACKWARD:
                        difference = &Simulation::BackwardDifference;
                        break;

                    case DifferenceMethod::FORWARD:
                        difference = &Simulation::ForwardDifference;
                        break;

                    case DifferenceMethod::CENTRAL:
                        difference = &Simulation::ForwardDifference;
                        break;
                }

            SetInitialCondition();
            std::ofstream output("advectionResults.dat");

            double d_Time = m_dTimeStart;

            do 
                {
                    d_Time += m_dDeltaT;

                    m_vec_dU[0] = m_vec_dU[m_iNumPoints + 1];
                    m_vec_dU[m_iNumPoints + 2] = m_vec_dU[1];
                    
                    output << "# time = " << d_Time << std::endl;

                    for (int i = 1; i <= m_iNumPoints; i++)
                        {
                            double d_CurrentX = m_dXStart + (i - 1) * m_dDeltaX;
                            (this->*difference)(m_vec_dU, m_vec_dUNext, i);

                            output << d_CurrentX << ' ' << m_vec_dU[i] << std::endl;
                        }

                    output << "\n\n";
                    m_vec_dU = m_vec_dUNext;

                } while (d_Time < m_dTimeEnd);
        }
};