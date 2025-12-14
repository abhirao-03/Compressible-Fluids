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
    double u_RELAXATION = 0.8;

    int u_iInitialCondition;
    std::cin >> u_iInitialCondition;
    
    Simulation::InitialCondition u_eInitialCondition = static_cast<Simulation::InitialCondition>(u_iInitialCondition);
    Simulation::ProgressionMethod u_eProgressionMethod = Simulation::ProgressionMethod::FORCE;

    return 0;
}