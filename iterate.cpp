#include <iostream>
#include "simulation.h"


void Simulation::Evolve()
    {
        SetInitialCondition();
        SetProgressionMethod();

        double t = m_dTimeStart;

        do
            {
                SetBoundaryConditions();
                SetTimeStep();
                (this->*m_ProgressionFunction)();

                t += m_dDeltaT;

                std::cout << "# time = " << t << std::endl;

                for (int i = 1; i < m_vec_dU.size() - 1; i++)
                    {
                        double x = m_dXStart + (i - 0.5) * m_dDeltaX;

                        m_vec_dUNext[i] = m_vec_dU[i] - (m_dDeltaT / m_dDeltaX) * (m_vec_dFluxes[i] - m_vec_dFluxes[i - 1]);

                        std::cout << x << ' ' << m_vec_dUNext[i] << std::endl;
                    }

                std::cout << "\n\n";

                m_vec_dU = m_vec_dUNext;

            } while (t < m_dTimeEnd);
    }