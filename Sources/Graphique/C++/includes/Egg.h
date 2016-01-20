#pragma once

#include <Ogre.h>

class Egg
{
public:
	Egg(int id, int x, int y, const std::string &nameMat,
		Ogre::SceneManager* sceneManager);
	~Egg();
	void setId(int newId);
	int getId() const;
	void endFork(const std::string &nameMat);
	void deathEgg();
private:
	int id;
	int x;
	int y;
	Ogre::SceneNode *node;
	Ogre::Entity *player;
	Ogre::SceneManager* sceneManager;
};