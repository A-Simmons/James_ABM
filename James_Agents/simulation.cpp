#include "stdafx.h"
#include <algorithm>
#include "agent.h"
#include "lattice.h"
#include "simulation.h"

void simulation::step()
{
	// Chose random agent
	int r = rand() % this->agents.size();
	agent * agent = &this->agents[r];
	bool result = this->moveAgent(agent);
}

bool simulation::moveAgent(agent* agent)
{	
	return agent->moveAgent(this->simParameters.moveType);
}

void simulation::spawnAgent(lattice* node)
{
	this->agents.emplace_back(agent(node));
	node->filled = &this->agents.back();
}

void simulation::spawnAgent() 
{
	
}

void simulation::addNode(int index) 
{
	this->nodes.emplace_back(lattice(index));
}

void simulation::initialiseAgents()
{
	// Get number of agents and find the total 
	std::vector<int> numAgents = this->simParameters.initialAgents;
	int totalNodes = this->nodes.size(); // Number of Nodes

	// Number of Agents
	int totalAgents = 0;  
	for (int n : numAgents)
		totalAgents += n;

	// Random permuation of lattice node indexes to spawn to 
	std::vector<int> result(totalAgents);
	for (int i = 0; i < totalAgents; ++i)
	{
		int r;
		do
		{
			r = rand() % totalNodes;
		} while (std::find(result.begin(), result.end(), r) != result.end());
		result[i] = r;
		this->spawnAgent(&this->nodes[r]);
	}
}

void simulation::initialiseLattice()
{
	int N = this->simParameters.xNodes * this->simParameters.yNodes;
	// Spawn Nodes
	for (int ii = 0; ii < N; ++ii)
		this->addNode(ii);

	// Add adjacencies
	this->initialiseLatticeAdjacencies();

}

void simulation::initialiseLatticeAdjacencies()
{
	int N;
	// Spawn Nodes
	for (int jj = 0; jj < this->simParameters.xNodes; ++jj)
	{
		for (int ii = 0; ii < this->simParameters.yNodes; ++ii)
		{
			N = jj*this->simParameters.yNodes + ii;
			this->nodes[N].adjacencies = this->determineAdjacencies(ii,jj);
		}			
	}
}

std::vector<lattice*> simulation::determineAdjacencies(int ii, int jj) 
{
	int xNodes = this->simParameters.xNodes;
	int yNodes = this->simParameters.yNodes;

	int index = jj*this->simParameters.yNodes + ii;
	int degreesofMovement = 8;
	std::vector<lattice*> adj;
	// N/E/S/W movement
	for (int kk = 0; kk < 4; ++kk)
	{
		switch (kk) {
		case 0: // North Adjacency
			if (ii != 0) {
				adj.emplace_back(&this->nodes[index - 1]);
			}
			break;
		case 2: // South Adjacency
			if (ii != (yNodes - 1)) {
				adj.emplace_back(&this->nodes[index + 1]);
			}
			break;
		case 1: // East Adjacency
			if (jj != (xNodes-1)) {
				adj.emplace_back(&this->nodes[index + yNodes]);
			}
			break;
		case 3: // West Adjacency
			if (jj != 0) {
				adj.emplace_back(&this->nodes[index - yNodes]);
			}
			break;
		}
	}

	// NE/SE/NE/SE movement
	if (degreesofMovement == 8)
	{
		for (int kk = 0; kk < 4; ++kk)
		{
			switch (kk) {
			case 0: // NorthEast Adjacency
				if (ii != 0 && jj != (xNodes-1)) {
					adj.emplace_back(&this->nodes[index - 1 + yNodes]);
				}
				break;
			case 2: // SouthEast Adjacency
				if (ii != (yNodes - 1) && jj != (xNodes - 1)) {
					adj.emplace_back(&this->nodes[index + 1 + yNodes]);
				}
				break;
			case 1: // NorthWest Adjacency
				if (ii != 0 && jj != 0) {
					adj.emplace_back(&this->nodes[index - 1 - yNodes]);
				}
				break;
			case 3: // SouthWest Adjacency
				if (ii != (yNodes - 1) && jj != 0) {
					adj.emplace_back(&this->nodes[index + 1 - yNodes]);
				}
				break;
			}
		}
	}
	return adj;
}

simulation::simulation() {

}

simulation::simulation(int moveType, int xNodes, int yNodes, std::vector<int> initialAgents)
{
	this->simParameters.moveType = moveType;
	this->simParameters.xNodes = xNodes;
	this->simParameters.yNodes = yNodes;
	this->simParameters.initialAgents = initialAgents;
	this->initialiseLattice();

}

simulation::simulation(int moveType, int xNodes, int yNodes, int initialAgents)
{
	this->simParameters.moveType = moveType;
	this->simParameters.xNodes = xNodes;
	this->simParameters.yNodes = yNodes;
	this->simParameters.initialAgents.emplace_back(initialAgents);
	this->initialiseLattice();
	this->initialiseAgents();
}

simulation::~simulation()
{
}
