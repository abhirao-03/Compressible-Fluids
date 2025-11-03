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
                    DifferenceMethod eDifferenceMethod,
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
            m_eDifferenceMethod(eDifferenceMethod),
            m_dRelaxation(dRelaxation)
            {
                m_dDeltaX = (m_dXEnd - m_dXStart) / m_iNumPoints;
                m_dDeltaT = m_dRelaxation * m_dDeltaX;
                m_vec_dU.resize(m_iNumGhostCells + m_iNumPoints + 1);
                m_vec_dUNext.resize(m_iNumGhostCells + m_iNumPoints + 1);
            }

        void SetInitialCondition(){

            if (m_iInitialCondition == 1)
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

        void BackwardDifference(const std::vector<double>& vec_dOldU, std::vector<double>& vec_dNewU, const int& i_IndexUpdate)
        {
            vec_dNewU[i_IndexUpdate] = vec_dOldU[i_IndexUpdate] - m_dAdvectionCoefficient * (m_dDeltaT/m_dDeltaX) * (vec_dOldU[i_IndexUpdate] - vec_dOldU[i_IndexUpdate - 1]); 
        }

        void ForwardDifference(const std::vector<double>& vec_dOldU, std::vector<double>& vec_dNewU, const int& i_IndexUpdate)
        {
            vec_dNewU[i_IndexUpdate] = vec_dOldU[i_IndexUpdate] - m_dAdvectionCoefficient * (m_dDeltaT/m_dDeltaX) * (vec_dOldU[i_IndexUpdate + 1] - vec_dOldU[i_IndexUpdate]);
        }

        void CentralDifference(const std::vector<double>& vec_dOldU, std::vector<double>& vec_dNewU, const int& i_IndexUpdate)
        {
            vec_dNewU[i_IndexUpdate] = vec_dOldU[i_IndexUpdate] - m_dAdvectionCoefficient * (m_dDeltaT/m_dDeltaX) * (1.0/2.0) * (vec_dOldU[i_IndexUpdate + 1] - vec_dOldU[i_IndexUpdate - 1]);
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