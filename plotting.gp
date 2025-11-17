# --- Output to a GIF file ---
set terminal gif animate delay 10 optimize size 800,600
set output 'advection.gif'

set xlabel "x"
set ylabel "u(x, t)"
set title "1D Linear Advection"
set xrange [0:1]
set yrange [-1.2:1.2]
set grid

# --- Animation loop ---
do for [i=0:500] {
    plot 'advectionResults.dat' index i using 1:2 with lines lw 2 lc rgb "blue" title sprintf("Timestep %d", i)
}

unset output
set terminal qt   # switch back to normal interactive mode