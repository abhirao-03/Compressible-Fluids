#include <vector>
#include <iostream>
#include <cmath>

double fluxfunction(const double& u)
    {
        return (1.0/2.0)*u*u;
    }

double chooseTimeStep(const std::vector<double>& u, const double& dx, const double& relaxation)
    {
        double max_u = 0.0;
        
        for (double curr_u : u)
        {
            if (std::abs(curr_u) > max_u)
            {
                max_u = std::abs(curr_u);
            }
        }

        if (max_u == 0.0)
            {
                return 1e-3;
            }
        
        
        return relaxation * dx / max_u;
    }

int main()
{
    double u_X0 = 0.0;
    double u_X1 = 1.0;

    double u_ADVCOEFF = 1.0;
    
    double u_TEND = 1.0;
    double u_T0 = 0.0;
    
    int u_NUMPOINTS = 400;
    int u_NUMGHOST = 2;
    double u_RELAXATION = 0.8;
    
    double d_X = (u_X1 - u_X0 )/u_NUMPOINTS;

    std::vector<double> vec_dU;
    vec_dU.resize(u_NUMGHOST + u_NUMPOINTS);

    std::vector<double> fluxes;
    fluxes.resize(vec_dU.size());

    std::vector<double> new_vec_dU;
    new_vec_dU.resize(vec_dU.size());

    // INITIAL CONDITION
    for(int i = 0; i < vec_dU.size(); i++)
        {
            double x = u_X0 + (i - 0.5) * d_X;
            
            if (x < 0.5)
                {
                    vec_dU[i] = 2;
                }
            else 
                {
                    vec_dU[i] = 1;   
                }
            
            // std::cout << x << ' ' << vec_dU[i] << std::endl;
        }


    double t = u_T0;
    
    do
        {
            // update t
            double d_T = chooseTimeStep(vec_dU, d_X, u_RELAXATION);
            t += d_T;


            //boundary conditions
            vec_dU[0] = vec_dU[1];
            vec_dU[u_NUMPOINTS + u_NUMGHOST - 1] = vec_dU[u_NUMPOINTS];

            //updating fluxes vector
            for (int i = 0; i < vec_dU.size() - 1; i++)
                {
                    double uL = vec_dU[i];
                    double uR = vec_dU[i + 1];

                    double fL = fluxfunction(uL);
                    double fR = fluxfunction(uR);

                    fluxes[i] = 0.5 * (fL + fR) + 0.5 * (d_X / d_T) * (uL - uR);
                }

            std::cout << "# time = " << t << std::endl;

            //update new_vec_dU based on fluxes.
            for (int i = 1; i < vec_dU.size() - 1; i++)
                {
                    double x = u_X0 + (i - 0.5) * d_X;

                    new_vec_dU[i] = vec_dU[i] - (d_T / d_X) * (fluxes[i] - fluxes[i-1]);

                    std::cout << x << ' ' << new_vec_dU[i] << std::endl;
                }

                std::cout << "\n\n";

            vec_dU = new_vec_dU;

        } while (t < u_TEND);
    
    return 1;
}