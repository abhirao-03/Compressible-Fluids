#include <vector>
#include <iostream>

double fluxfunction(const double& u)
    {
        return (1.0/2.0)*u*u;
    }


int main()
{
    double u_X0 = 0.0;
    double u_X1 = 1.0;

    double u_ADVCOEFF = 1.0;
    
    double u_TEND = 1.0;
    double u_T0 = 0.0;
    
    int u_NUMPOINTS = 100;
    int u_NUMGHOST = 4;
    double u_RELAXATION = 0.8;
    
    double d_X = (u_X1 - u_X0 )/u_NUMPOINTS;
    double d_T = u_RELAXATION * d_X;

    std::vector<double> vec_dU;
    vec_dU.resize(u_NUMGHOST + u_NUMPOINTS + 1);

    std::vector<double> new_vec_dU;
    new_vec_dU.resize(u_NUMGHOST + u_NUMPOINTS + 1);

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
            t += d_T;

            vec_dU[0] = vec_dU[u_NUMPOINTS + u_NUMGHOST - 1];
            vec_dU[u_NUMPOINTS + u_NUMGHOST] = vec_dU[1];

            std::cout << "# time = " << t << std::endl;

            for (int i = 0; i < vec_dU.size() - u_NUMGHOST/2; i++)
            {
                double x = u_X0 + (i - 0.5) * d_X;

                double uL = vec_dU[i];
                double uR = vec_dU[i+1];
                double fL = fluxfunction(uL);
                double fR = fluxfunction(uR);

                double LF_flux_left = 0.5 * (d_X/d_T) * (vec_dU[i] - vec_dU[i+1]) + 0.5 * (fluxfunction(vec_dU[i]) + fluxfunction(vec_dU[i+1]));
                double LF_flux_right = 0.5 * (d_X/d_T) * (vec_dU[i+1] - vec_dU[i+2]) + 0.5 * (fluxfunction(vec_dU[i+1]) + fluxfunction(vec_dU[i+2]));

                new_vec_dU[i] = uL - d_T / d_X * (LF_flux_left - LF_flux_right);

                std::cout << x << ' ' << new_vec_dU[i] << std::endl;

            }

            std::cout << "\n\n";

            vec_dU = new_vec_dU;

        } while (t < u_TEND);
    
    return 1;
}