#include "simulation.h"

void Simulation::PerformTimeSteps()
{
    // SET 
    SetProgressionMethod();
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
                    (this->*m_ProgressionFunction)(m_vec_dU, m_vec_dUNext, i);

                    output << d_CurrentX << ' ' << m_vec_dU[i] << std::endl;
                }

            output << "\n\n";
            m_vec_dU = m_vec_dUNext;

        } while (d_Time < m_dTimeEnd);
}