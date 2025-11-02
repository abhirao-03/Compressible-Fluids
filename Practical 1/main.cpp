#include "simulation.h"

int main(){
    double X0 = 0.0;
    double X1 = 1.0;

    Simulation DownwindSin(0.0, 1.0, 0.0, 1.0, 1.0, 100, 2, 1, 1, 0.8);

    DownwindSin.PerformTimeSteps(1);

    return 0;
}