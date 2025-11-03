clean-meta :
	rm *.dat *.out *.h.pch

clean :
	rm *.dat *.out *.h.pch *.gif

plot-square : 
	g++ main.cpp simulation.h
	echo 0 | ./a.out
	gnuplot plotting.gp
	mv advection.gif square_advection.gif

plot-sin : 
	g++ main.cpp simulation.h
	echo 1 | ./a.out
	gnuplot plotting.gp
	mv advection.gif sin_advection.gif