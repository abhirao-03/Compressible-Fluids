# --- Output to a GIF file ---
set terminal gif animate delay 10 optimize size 800,600
set output 'advection.gif'

set xlabel "x"
set ylabel "u(x, t)"
set xrange [0:1]
set yrange [-0.1:2.1]
set title "Lax Friedrichs Flux for Burger's Equation "
set grid

# --- Animation loop ---
do for [i=0:10000] {
    plot 'flux.dat' index i using 1:2 with lines lw 2 lc rgb "blue" title sprintf("Timestep %d", i)
}

unset output
set terminal qt   # switch back to normal interactive mode