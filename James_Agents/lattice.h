#pragma once

#include <vector>
#include <list>

class agent;

class lattice
{
public:
	agent* filled;
	std::vector<lattice*> adjacencies;
	int index; // Not used. Helps with debugging and graphing.

	bool isEmpty();
	std::vector<lattice*> getEmptyAdjacencies();
	std::vector<lattice*>* getAdjacencies();
	lattice(int);
	~lattice();
};

