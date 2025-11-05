#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

int main(){
    // constants
    double x0 = 0.0;
    double x1 = 1.0;
    int numPoints = 100;

    double tStart = 0.0;
    double tStop = 1.0;

    double a = 1.0;
    double pi = 4*atan(1);

    // derived constants:
    double dx = (x1 - x0)/numPoints;
    double dt = 0.8*dx;

    // GHOST ZONE
    int numGhostZone = 2;

    std::vector<double> u;
    u.resize(numPoints + numGhostZone + 1);
    //std::cout << u.size() << std::endl;

    // SETTING INITIAL DATA
    for (int i = 0; i < u.size(); i++){
        double x = x0 + ((i - 1) * dx);
        u[i] = sin(2 * pi * x);
        //std::cout << x << ' ' << u[i] << std::endl;     // to verify initial data after plotting.
    }

    std::vector<double> uNext;
    uNext.resize(u.size());

    // UPDATING DATA THROUGH TIME
    double t = tStart;

    // [-1, 0, 1, 2, 3, 4, ..., 100, 101]
    //   0  1  2, ...,          101, 102
    // [_, 1c, 2c, ...,         101c, _]
    // 

    do {
        t = t + dt;

        u[0] = u[1];
        u[numPoints + numGhostZone] = u[numPoints + numGhostZone - 1];


        for (int i = 1; i <= numPoints; i++){
            double x = x0 + ((i - 1) * dx);
            uNext[i] = u[i] - a * (dt/dx) * (u[i] - u[i - 1]);
            
            std::cout << x << ' ' << u[i] << std::endl;
        }
        std::cout << "\n\n";

        u = uNext;

    } while (t < tStop);

    return 0;
}