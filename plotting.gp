# --- Configuration ---
set terminal gif animate delay 15 optimize size 900,800 font "Arial,10"
set output 'name_holder.gif'

# Physics Constant (Must match your C++ code)
GAMMA = 1.4

# --- Scan the file first to count the number of time steps ---
# This prevents hardcoding "499" and breaking if you change T_END
stats 'flux.dat' nooutput
N = STATS_blocks - 1

# --- Style Settings ---
set style line 1 lc rgb '#D70039' lt 1 lw 2 # Red for Density
set style line 2 lc rgb '#0088D7' lt 1 lw 2 # Blue for Velocity
set style line 3 lc rgb '#00994D' lt 1 lw 2 # Green for Pressure
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0

# --- Animation Loop ---
do for [i=0:N] {
    
    # Set up a 3x1 grid for the plots
    set multiplot layout 3,1 title sprintf("Euler Equations - Frame %d", i) font ",14"

    # Common X-axis settings
    set xrange [0:1]
    
    # --- PLOT 1: DENSITY (Column 2) ---
    set ylabel "Density"
    set yrange [0:*]  # Density should never be negative
    set format x ""   # Hide x-labels for top plots
    set tmargin 2
    plot 'flux.dat' index i using 1:2 with lines ls 1 title "rho"

    # --- PLOT 2: VELOCITY (Column 3 / Column 2) ---
    # v = (rho*v) / rho
    set ylabel "Velocity"
    set yrange [*:*] # Autoscale
    plot 'flux.dat' index i using 1:($3/$2) with lines ls 2 title "v"

    # --- PLOT 3: PRESSURE (Derived from Energy) ---
    # P = (gamma-1) * (E - 0.5 * rho * v^2)
    # P = (gamma-1) * (Col4 - 0.5 * (Col3^2 / Col2))
    set ylabel "Pressure"
    set xlabel "Position (x)"
    set format x "%g" # Show x-labels for bottom plot
    set yrange [0:*]
    plot 'flux.dat' index i using 1:((GAMMA-1)*($4 - 0.5*($3**2)/$2)) with lines ls 3 title "P"

    unset multiplot
}

unset output