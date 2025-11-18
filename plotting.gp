# --- Output to a GIF file ---
set terminal gif animate delay 10 optimize size 800,600
set output 'name_holder.gif'

set xlabel "x"
set ylabel "u(x, t)"
set title "Finite Volume Method for Burger's Equation"
set xrange [0:1]
set yrange [-1.1:1.1]
set grid

# --- Animation loop ---
do for [i=0:499] {
    plot 'flux.dat' index i using 1:2 with lines lw 2 lc rgb "blue" title sprintf("Timestep %d", i)
}

unset output
set terminal qt   # switch back to normal interactive mode