remove-gifs :
	rm *.gif

clean :
	rm *.dat *.out *.h.*

executable : main.cpp simulation.h fluxes.cpp helpers.cpp initials.cpp iterate.cpp
	g++ main.cpp simulation.h fluxes.cpp helpers.cpp initials.cpp iterate.cpp
	rm *.h.*

sim_FORCE : main.cpp simulation.h fluxes.cpp helpers.cpp initials.cpp iterate.cpp slope_logic.cpp limiters.cpp
	g++ main.cpp simulation.h fluxes.cpp helpers.cpp initials.cpp iterate.cpp slope_logic.cpp limiters.cpp
	echo 5 | ./a.out > flux.dat
	gnuplot plotting.gp
	mv name_holder.gif visualisations/
	make clean