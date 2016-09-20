// James_Agents.cpp :
//


#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "lattice.h"
#include "agent.h"
#include "simulation.h"

// Parameters
int moveType = 0; // 0: Attempt to move to random empty adjacency. 1: Attempt to move to any random adjacency
int xNodes = 3000;
int yNodes = 3000;
int numAgents = 10000;
int totalSteps = 1e9;

simulation initialise() {
	// Initialise Simulation
	clock_t begin = clock();
	simulation sim(moveType, xNodes, yNodes, numAgents);
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Initialisation:\t" << elapsed_secs << "seconds" << std::endl;
	return sim;
}

double steps(simulation* sim) {
	// Run a few steps
	clock_t begin = clock();
	for (int ii = 0; ii < totalSteps; ++ii)
		sim->step();
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	return elapsed_secs;
}

int main()
{
	
	simulation sim = initialise();
	double time_steps = steps(&sim);


	std::cout << "Time to run simulation: \t" << time_steps << "seconds" << std::endl;
	std::cout << "Time per 10M steps: \t\t" << time_steps / totalSteps*1e7 << "seconds" << std::endl;
	std::cout << "Steps per second: \t\t" << totalSteps / time_steps << "steps" << std::endl;

	std::cin.get();

    return 0;
}

