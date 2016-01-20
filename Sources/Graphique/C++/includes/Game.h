#pragma once

#ifndef GAME_H_
#define GAME_H_

#include <Ogre.h>
#include <vector>
#include <map>
#include "Menu.h"
#include "Input.h"
#include "Map.h"
#include "Team.h"
#include "Player.h"
#include "Egg.h"
#include "Incantation.h"
#include "InfoBullePlayer.h"
#include "Utils.hpp"

/*
** levels colors
*/
#define WHITE 1
#define GREEN 2
#define PINK 3
#define RED 4
#define PURPLE 5
#define BROWN 6
#define BLUE 7
#define GOLD 8

#define SPEED_ANIM 0.00199

class NetworkManager;

class Game
{
public:
	Game();
	virtual ~Game();
	void setSpeedAnim(float newSpeedAnim);
	void init(Ogre::Root *mRoot, Ogre::RenderWindow* mWindow, Menu *menuManager, NetworkManager* net);
	void createMenu();
	void createMap(int sizeX, int sizeY);
	void OnUpdateMap(int x, int y, int *content);
	void OnNewTeam(std::string team);
	void OnError(std::string error);
	void fillMap(int x, int y, std::vector<int> data);
	void createTeam(std::string name);
	void createPlayer(int id, int x, int y, char orient, char level, std::string teamName);
	void createEgg(int id);
	void eggEndFork(int id, int idPlayer, int x, int y);
	void createIncantation(int x, int y, int level, int id);
	void deleteEgg(int id);
	void deleteIncantation(int x, int y, bool success);
	void dead(int id);
	void selectPlayer(Ogre::SceneNode *player);
	void movePlayer(int id, int x, int y, int o);
	void update(Ogre::Real time);
	void take(int id);
	void drop(int id);
	void levelUp(int id, int level);
	void updateInventoryPlayer(int id, int x, int y, std::vector<int> resources);
private:
	Ogre::SceneManager* mSceneMgr;
	Ogre::RenderWindow* mWindow;
	Ogre::Camera* mCamera;
	Input *input;
	Menu *menuManager;
	Map *map;
	int sizeMapX;
	int sizeMapY;
	std::vector<Team> teams;
	std::vector<Player> players;
	bool initInfoPlayer;
	InfoBullePlayer* infoPlayer;
	std::vector<int> infosPlayer;
	std::vector<Egg> eggs;
	std::vector<Incantation> incantation;
	std::map<int, Ogre::ColourValue> colorLevelPlayer;
	float speedAnim;
};

#endif