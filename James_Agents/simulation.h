#pragma once
#include <vector>

class lattice;
class agent;


struct parameters
{
	int moveType; // 0: Move to any empty node. 1: Choose random adjacency and move if free.
	int xNodes;
	int yNodes;
	std::vector<int> initialAgents;
};

class simulation
{
public:
	parameters simParameters;
	std::vector<lattice> nodes;
	std::vector<agent> agents;

	void step();
	void spawnAgent(lattice*);
	void spawnAgent();
	bool moveAgent(agent*);
	void addNode(int);
	void initialiseAgents();
	void initialiseLattice();
	void initialiseLatticeAdjacencies();
	std::vector<lattice*> determineAdjacencies(int, int);


	simulation();
	simulation(int,int,int,int);
	simulation(int, int, int, std::vector<int>);
	~simulation();
};

