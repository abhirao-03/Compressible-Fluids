remove-gifs :
	rm -f *.gif

clean :
	rm -f *.dat *.out *.h.*

sim_SLIC : main.cpp simulation.h fluxes.cpp helpers.cpp initials.cpp iterate.cpp slope_logic.cpp limiters.cpp
	g++ main.cpp simulation.h fluxes.cpp helpers.cpp initials.cpp iterate.cpp slope_logic.cpp limiters.cpp
	echo 9 | ./a.out > flux.dat
	-gnuplot plotting.gp
	mv name_holder.gif visualisations/SLICToroFive.gif
	make clean