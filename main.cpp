#include <iostream>
#include "simulation.h"

int main(){
    double u_X0 = 0.0;
    double u_X1 = 1.0;
    
    double u_T0 = 0.0;
    double u_TEND = 1.0;
    
    double u_RELAXATION = 0.8;
    double u_GAMMA = 1.4;

    int u_NUMPOINTS = 400;
    int u_NUMGHOST = 2;

    int u_iInitialCondition;
    std::cin >> u_iInitialCondition;
    
    Simulation::InitialCondition u_eInitialCondition = static_cast<Simulation::InitialCondition>(u_iInitialCondition);
    Simulation::SlopeLimiter u_eSlopeLimiter = Simulation::SlopeLimiter::VAN_ALBADA;

    Simulation EulerEquations = Simulation(u_X0, u_X1, u_T0, u_TEND, u_RELAXATION, u_GAMMA, u_NUMPOINTS, u_NUMGHOST, u_eInitialCondition, u_eSlopeLimiter);

    EulerEquations.Evolve();

    return 0;
}