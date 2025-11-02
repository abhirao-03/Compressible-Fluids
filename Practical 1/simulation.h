#include <cmath>
#include <fstream>
#include <vector>
static const double PI = 4*atan(1);

class Simulation{
    private:
        double m_dXStart;
        double m_dXEnd;
        double m_dTimeStart;
        double m_dTimeEnd;
        double m_dAdvectionCoefficient;

        int m_iNumPoints;
        int m_iNumGhostCells;

        int m_iInitialCondition;
        int m_iDifferenceMethod;

        double m_dDeltaX = (m_dXStart - m_dXEnd) / m_iNumPoints;
        double m_dRelaxation;
        double m_dDeltaT = m_dRelaxation * m_dDeltaX;

        std::vector<double> m_vec_dU;
        std::vector<double> m_vec_dUNext;

    public:
        // member initialization
        Simulation(
                    double dxStart,
                    double dxEnd,
                    double dTimeStart,
                    double dTimeEnd,
                    double dAdvectionCoefficient,
                    int iNumPoints,
                    int iNumGhostCells,
                    int iInitialCondition,
                    int iDifferenceMethod,
                    double dRelaxation)
            : 
            m_dXStart(dxStart),
            m_dXEnd(dxEnd),
            m_dTimeStart(dTimeStart),
            m_dTimeEnd(dTimeEnd),
            m_dAdvectionCoefficient(dAdvectionCoefficient),
            m_iNumPoints(iNumPoints),
            m_iNumGhostCells(iNumGhostCells),
            m_iInitialCondition(iInitialCondition),
            m_iDifferenceMethod(iDifferenceMethod),
            m_dRelaxation(dRelaxation)
            {
                m_dDeltaX = (m_dXStart - m_dXEnd) / m_iNumPoints;
                m_dDeltaT = m_dRelaxation * m_dDeltaX;
                m_vec_dU.resize(m_iNumGhostCells + m_iNumPoints + 1);
                m_vec_dUNext.resize(m_iNumGhostCells + m_iNumPoints + 1);
            }

        void SetInitialCondition(const int& initial_condition){

            if (initial_condition == 1)
            {
                    for (int i = 0; i < m_vec_dU.size(); i++)
                    {
                        double tmp_dX = m_dXStart + (i - 1) * m_dDeltaX;
                        m_vec_dU[i] = sin(2 * PI * tmp_dX);
                    }
            } else {

                for (int i = 0; i < m_vec_dU.size(); i++)
                {
                    double tmp_dX = m_dXStart + (i - 1) * m_dDeltaX;

                    if (tmp_dX >= 0.25 and tmp_dX <= 0.75)
                    {
                        m_vec_dU[i] = 1;
                    } else {
                        m_vec_dU[i] = 0;
                    }
                }
            }
        }

        void PerformTimeSteps(const int& InitialCondition){
            SetInitialCondition(InitialCondition);
            std::ofstream output("advectionResults.dat");

            double d_Time = m_dTimeStart;

            do 
            {
                d_Time += m_dDeltaT;

                m_vec_dU[0] = m_vec_dU[1];
                m_vec_dU[m_iNumPoints + m_iNumGhostCells] = m_vec_dU[m_iNumPoints + m_iNumGhostCells - 1];

                for (int i = 1; i <= m_iNumPoints; i++)
                {
                    double d_CurrentX = m_dXStart + (i - 1) * m_dDeltaX;
                    m_vec_dUNext[i] = m_vec_dU[i] - m_dAdvectionCoefficient * (m_dDeltaT/m_dDeltaX) * (m_vec_dU[i] - m_vec_dU[i - 1]);

                    output << d_CurrentX << ' ' << m_vec_dU[i] << std::endl;

                }
                output << "\n\n";

            } while (d_Time < m_dTimeEnd);
        }

};