# Compressible Fluid Dynamics: Hyperbolic PDE Solvers
*This README.md was written with the aid of Gemini 3 Pro.*

This repository contains a comprehensive suite of numerical and analytical solvers for Hyperbolic Partial Differential Equations (PDEs), developed as part of the **Numerical Methods for Compressible Fluid Dynamics** curriculum.

The project progresses from basic scalar advection to full systems of conservation laws (Euler Equations), implementing Finite Difference, Finite Volume, and High-Resolution Slope-Limited methods.

## Project Structure & Branches

The development history is organized by **Practicals** across specific git branches. Each branch represents a step forward in complexity and accuracy.

### 1. Linear Advection (Finite Difference)
*   **Branch:** `main`
*   **Practicals:** 1 & 2
*   **Equation:** Linear Advection $\left(\frac{\partial u}{\partial t} + a \frac{\partial u}{\partial x} = 0\right)$
*   **Description:** 
    Implementation of basic Finite Difference schemes (Forward-Time Central-Space, Upwind, etc.) to solve scalar transport problems. This stage established the foundations of discretization grids, time-stepping stability (CFL condition), and boundary handling.

### 2. Linear Advection (Finite Volume)
*   **Branch:** `Finite-Flux`
*   **Practical:** 3
*   **Equation:** Linear Advection
*   **Description:** 
    Transitioned from finite difference to **Finite Volume Methods**. This branch explores the concept of numerical flux functions to ensure conservation.
    *   **Schemes Implemented:**
        *   Lax-Friedrichs (Diffusive)
        *   Richtmyer (Oscillatory)
        *   FORCE (First Order Centred)
        *   Godunov (Upwind)

### 3. The Euler Equations (System Solvers)
*   **Branch:** `Euler-Equations`
*   **Practical:** 4
*   **Equation:** 1D Compressible Euler Equations (Mass, Momentum, Energy)
*   **Description:** 
    Extended the solver to handle systems of non-linear conservation laws. This involved moving from scalar variables to vector states ($\vec{U} = [\rho, \rho u, E]^T$).
    *   Implemented the **FORCE Scheme** for systems.
    *   Validated against standard test cases (e.g., Sod Shock Tube).

### 4. High-Resolution Methods (Slope Limiting)
*   **Branch:** `Euler-SLIC`
*   **Practical:** 5
*   **Equation:** 1D Compressible Euler Equations
*   **Description:** 
    Implemented Second-Order accuracy using the **SLIC (Slope Limiter Centred)** method. 
    *   Introduced data reconstruction (Left/Right states) within cells.
    *   Applied Slope Limiters (e.g., Minbee, Superbee, Van Leer) to achieve high resolution near shocks without introducing spurious oscillations (TVD property).

### 5. Exact Riemann Solver
*   **Branch:** `Euler-Exact`
*   **Practical:** 6
*   **Description:** 
    Implementation of an analytical **Exact Riemann Solver** to serve as a "Ground Truth" for validating numerical methods.
    *   Uses an iterative Newton-Raphson method to solve for the pressure in the Star Region ($P^*$).
    *   Correctly models the full wave structure: **Shock Waves** (Rankine-Hugoniot relations), **Rarefaction Fans** (Isentropic relations), and **Contact Discontinuities**.
    *   Capable of solving various wave configurations (Sod Shock Tube, 123 Problem, Collisions, Strong Shocks).

---

## The Euler Equations

For branches `Euler-Equations`, `Euler-Slic`, and `Euler-Exact`, the system solved is:

$$
\frac{\partial}{\partial t}
\begin{pmatrix} \rho \\ \rho u \\ E \end{pmatrix} +
\frac{\partial}{\partial x}
\begin{pmatrix} \rho u \\ \rho u^2 + p \\ u(E + p) \end{pmatrix} = 0
$$

Where pressure is closed via the Ideal Gas Law: $p = (\gamma - 1)(E - \frac{1}{2}\rho u^2)$.

## Visualization

The solvers output data files containing state variables (Density, Velocity, Pressure) across the spatial domain. These are visualized using **Gnuplot** to generate animations of wave propagation (Shocks, Rarefactions, and Contact Discontinuities).

### Example: Sod Shock Tube (Exact Solution)
*   **Left Wave:** Rarefaction (Density drops smoothly)
*   **Middle:** Contact Discontinuity (Density jumps, Pressure/Velocity constant)
*   **Right Wave:** Shock (Abrupt jump in all variables)

## Compilation & Usage

To build and run the solver from any specific branch:

1.  **Checkout the branch:**
    ```bash
    git checkout Euler-Exact  # Or Euler-SLIC, Finite-Flux, etc.
    ```
2.  **Compile:**
    ```bash
    g++ *.cpp -o solver
    ```
3.  **Run:**
    ```bash
    ./solver > flux.dat
    # Enter number to select test case (e.g., 5 for Toro Sod Shock Tube Test)
    ```
4.  **Visualize:**
    ```bash
    gnuplot plotting.gp
    ```