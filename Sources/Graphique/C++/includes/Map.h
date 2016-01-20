#pragma once

#include <Ogre.h>
#define COEF 6

class Map
{
public:
	Map(Ogre::SceneManager* mSceneMgr, int x, int y);
	~Map();
	void fillMap(int x, int y, std::vector<int> content);
	void updateMap(Ogre::Real time);
private:
	void createTexture();

	int sizex;
	int sizey;
	void updateMap();
	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneNode *mapNode;
	Ogre::SceneNode *contentNode;
	std::vector<Ogre::AnimationState *> anims;
	char ***content;
};

