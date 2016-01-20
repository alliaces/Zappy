#pragma once

#include <Ogre.h>
#include <vector>
#include "Utils.hpp"

class Player
{
public:
	Player(int id, int x, int y, char orient, char level, std::string team,
		float speedAnim,
		int sizeMapX,
		int sizeMapY,
		Ogre::ColourValue color, Ogre::SceneManager* sceneManager);
	~Player();
	void move(int x, int y, int o);
	void takeRes();
	void dropRes();
	void doDead();
	int getId();
	char getLevel() const;
	void setLevel(char newLevel, Ogre::ColourValue color);
	void setResources(std::vector<int> newResources);
	const std::vector<int> &getResources() const;
	const std::string &getTeam() const;
	Ogre::SceneNode *getNode() const;
	bool update(Ogre::Real time);
	int x;
	int y;
private:
	int id;
	char orient;
	char level;
	int xOld;
	int yOld;
	int sizeMapX;
	int sizeMapY;
	std::string team;
	std::vector<int> resources;
	Ogre::Entity *player;
	Ogre::ColourValue color;
	Ogre::SceneNode *node;
	Ogre::SceneManager* sceneManager;
//	Ogre::MaterialPtr *mat;
	Ogre::AnimationState *anim;
	Ogre::AnimationState *take;
	Ogre::AnimationState *dead;
	float speedAnim;
	void resetO();
	void updateO();
};

