#pragma once

#include <Ogre.h>
#include <time.h>
#include <cstdlib>

class Team
{
public:
	Team(std::string name);
	~Team();
	std::string name;
	Ogre::ColourValue color;
};

