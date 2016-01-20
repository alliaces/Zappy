#include "Team.h"

Team::Team(std::string name)
{
	this->name = name;
	float a = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float c = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	this->color = Ogre::ColourValue(a, b, c);
}


Team::~Team()
{
}
