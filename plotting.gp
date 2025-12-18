# --- Configuration ---
set terminal gif animate delay 15 optimize size 900,800 font "Arial,10"
set output 'name_holder.gif'

# Physics Constant (Must match your C++ code)
GAMMA = 1.4

# --- Scan the file first to count the number of time steps ---
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
    
    set multiplot layout 3,1 title sprintf("Euler Equations - Frame %d", i) font ",14"

    # Common X-axis settings
    set xrange [0:1]
    
    # --- PLOT 1: DENSITY (Column 2) ---
    set ylabel "Density"
    set yrange [0:*]
    set format x ""
    set tmargin 2
    # Fix: If val is NaN, plot 0
    plot 'flux.dat' index i using 1:(valid(2) ? $2 : 0) with lines ls 1 title "rho"

    # --- PLOT 2: VELOCITY (Column 3 / Column 2) ---
    set ylabel "Velocity"
    set yrange [*:*] 
    # Fix: Check if Density ($2) is almost zero to avoid division by zero
    plot 'flux.dat' index i using 1:(abs($2) > 1e-9 ? $3/$2 : 0) with lines ls 2 title "v"

    # --- PLOT 3: PRESSURE ---
    set ylabel "Pressure"
    set xlabel "Position (x)"
    set format x "%g"
    set yrange [0:*]
    # Fix: Check if Density ($2) is almost zero before dividing
    plot 'flux.dat' index i using 1:(abs($2) > 1e-9 ? (GAMMA-1)*($4 - 0.5*($3**2)/$2) : 0) with lines ls 3 title "P"

    unset multiplot
}

unset output