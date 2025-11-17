remove-gifs :
	rm *.gif

clean :
	rm *.dat *.out *.h.*


sim-first-LF : main.cpp simulation.h fluxes.cpp helpers.cpp initials.cpp iterate.cpp
	g++ main.cpp simulation.h fluxes.cpp helpers.cpp initials.cpp iterate.cpp
	echo 1 | ./a.out > flux.dat
	gnuplot plotting.gp
	mv name_holder.gif FirstInitial.gif
	make clean

sim-second-LF : main.cpp simulation.h fluxes.cpp helpers.cpp initials.cpp iterate.cpp
	g++ main.cpp simulation.h fluxes.cpp helpers.cpp initials.cpp iterate.cpp
	echo 2 | ./a.out > flux.dat
	gnuplot plotting.gp
	mv name_holder.gif SecondInitial.gif
	make clean