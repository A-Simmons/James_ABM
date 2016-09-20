#include "stdafx.h"
#include <iostream>
#include "lattice.h"
#include <list>


std::vector<lattice*> lattice::getEmptyAdjacencies()
{
	// Get pointer to vector of pointers that point to adjacencies
	std::vector<lattice*>* adj = this->getAdjacencies();
	// Initialise list for adjacencies which are empty
	std::vector<lattice*> emptyAdj;
	// Iterate over the adjacency vector
	for (std::vector<lattice*>::iterator it = adj->begin(); it != adj->end(); ++it) {
		// If adjacent node is empty, push to emptyAdj
		if ((*it)->isEmpty())
			emptyAdj.push_back((*it));
	}
	return emptyAdj;
}

bool lattice::isEmpty()
{
	return (this->filled) ? true : false;
}

std::vector<lattice*>* lattice::getAdjacencies()
{
	return(&this->adjacencies);
}

lattice::lattice(int index)
{
	this->index = index;
}


lattice::~lattice()
{
}
