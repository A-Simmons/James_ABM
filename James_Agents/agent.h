#pragma once
#include <vector>
class lattice;

class agent
{
public:

	lattice* location;

	bool moveAgent(int);
	bool chooseSite(std::vector<lattice*>*);
	agent(lattice*);
	~agent();
};
