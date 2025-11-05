#include <iostream>
#include "simulation.h"

int main(){
    double u_X0 = 0.0;
    double u_X1 = 1.0;
    
    double u_ADVCOEFF = 1.0;
    
    double u_TEND = 1.0;
    double u_T0 = 0.0;
    
    int u_NUMPOINTS = 400;
    int u_NUMGHOST = 2;
    double u_RELAXATION = 0.9;

    int u_iInitialCondition;
    std::cin >> u_iInitialCondition;
    
    Simulation::DifferenceMethod u_eDifferenceMethod = Simulation::DifferenceMethod::BACKWARD;
    Simulation::InitialCondition u_eInitialCondition = static_cast<Simulation::InitialCondition>(u_iInitialCondition);

    Simulation DownwindSin(u_X0, u_X1, u_T0, u_TEND, u_RELAXATION, u_ADVCOEFF, u_NUMPOINTS, u_NUMGHOST, u_eInitialCondition, u_eDifferenceMethod);
    DownwindSin.PerformTimeSteps();

    return 0;
}