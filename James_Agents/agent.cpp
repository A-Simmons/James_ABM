#include "stdafx.h"
#include "agent.h"
#include "lattice.h"
#include <vector>


bool agent::chooseSite(std::vector<lattice*>* adj)
{
	if (adj->size() > 0) // Check the vector has elements
	{
		// Choose a random node and modify node
		int randomIndex = rand() % adj->size();
		lattice* node = (*adj)[randomIndex];

		this->location->filled = nullptr; // Remove this agent from old location
		node->filled = this; // Add this agent to new location
		this->location = node; // Update location in this agent
		return true;
	} else 
		return false;	
}

bool agent::moveAgent(int type)
{
	return this->chooseSite((type == 0) ? &this->location->getEmptyAdjacencies() : this->location->getAdjacencies());
}

// Constructor
agent::agent(lattice* node)
{
	this->location = node;
	node->filled = this;
}

// Deconstructor
agent::~agent()
{
	this->location->filled = 0;
}
