remove-gifs :
	rm *.gif

clean :
	rm *.dat *.out *.h.*

executable : main.cpp simulation.h fluxes.cpp helpers.cpp initials.cpp iterate.cpp
	g++ main.cpp simulation.h fluxes.cpp helpers.cpp initials.cpp iterate.cpp
	rm *.h.*

sim-FORCE : main.cpp simulation.h fluxes.cpp helpers.cpp initials.cpp iterate.cpp
	g++ main.cpp simulation.h fluxes.cpp helpers.cpp initials.cpp iterate.cpp
	echo 4 | ./a.out > flux.dat
	gnuplot plotting.gp
	mv ./name_holder.gif ./visualisations/name_holder.gif
	make clean