#include "simulation.h"

int main(){
    double X0 = 0.0;
    double X1 = 1.0;
    double T0 = 0.0;
    double TEND = 1.0;
    double ADVCOEFF = 1.0;
    int NUMPOINTS = 100;
    int NUMGHOST = 2;
    int INITCOND = 1;
    int DIFFMETHOD = 1;
    double RELAXATION = 1.0;


    Simulation DownwindSin(X0, X1, T0, TEND, ADVCOEFF, NUMPOINTS, NUMGHOST, INITCOND, DIFFMETHOD, RELAXATION);
    DownwindSin.PerformTimeSteps();

    return 0;
}