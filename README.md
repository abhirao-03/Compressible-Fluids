# Compressible-Fluids
Numerical Methods for Compressible Fluid Dynamics

## Practical 1
Finite differences for 1D linear Advection equation for different initial conditions. We simulate:

$$
\frac{\partial u}{\partial t} + a\frac{\partial u}{\partial x} = 0.
$$

![Sine Wave Initial Condition](Practical1/sin_advection.gif)
![Square Wave Initial Condition](Practical1/square_advection.gif)


1. With `a = 1.0` the backward difference is stable, but the forward and centered difference are unstable.
2. When we set `a = -1.0`, the backward difference becomes unstable and the forward and centered difference methods are now stable.
3. With `a = 0.5`, backward difference is stable, forward and centered differences are unstable. However, changing to `a = 2` results in instability across all differences.
4. When we make $a$ smaller, we are in effect slowing down the progression of the $\sin$ wave, thus to keep the animation the same we must scale up the time horizon we consider, and vice versa when we increase $a$.
5. Setting a relaxation of $0.9$ results in the discontinuity becoming smoothed out.
6. By increasing the number of points from 100 to 400 we are in effect increasing the spatial quality of the simulation by 4 times, not only do we increase the spatial resolution, but to mantain stability using the downwind method, we must also increase the temporal resolution.