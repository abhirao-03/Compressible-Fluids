remove-gifs :
	rm *.gif

clean :
	rm *.dat *.out *.h.*

plot-square : main.cpp simulation.h differences.cpp initials.cpp
	g++ main.cpp simulation.h differences.cpp initials.cpp
	echo 1 | ./a.out
	gnuplot plotting.gp
	mv advection.gif /visualisations/SquareAdvection.gif

plot-sin : main.cpp simulation.h differences.cpp initials.cpp
	g++ main.cpp simulation.h differences.cpp initials.cpp
	echo 2 | ./a.out
	gnuplot plotting.gp
	mv advection.gif /visualisations/SinAdvection.gif

plot-exp : main.cpp simulation.h differences.cpp initials.cpp
	g++ main.cpp simulation.h differences.cpp initials.cpp
	echo 3 | ./a.out
	gnuplot plotting.gp
	mv advection.gif /visualisations/ExponentAdvection.gif