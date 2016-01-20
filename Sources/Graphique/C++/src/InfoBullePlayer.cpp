//
// InfoBullePlayer.cpp for InfoBullePlayer.cpp in /home/lelong_t/rendu/zappy_graphique/src
// 
// Made by Théophile
// Login   <lelong_t@epitech.net>
// 
// Started on  Mon Jun 29 16:21:19 2015 Théophile
// Last update Mon Jun 29 16:21:21 2015 Théophile
//

#include "InfoBullePlayer.h"

InfoBullePlayer::InfoBullePlayer()
{
	this->initFood();
	this->initLinemate();
	this->initDeraumere();
	this->initSibur();
	this->initMendiane();
	this->initPhiras();
	this->initThystame();
	this->initIdPlayer();
	this->initLevelPlayer();
	this->initTeamPlayer();
}

InfoBullePlayer::~InfoBullePlayer()
{
}

void InfoBullePlayer::initFood()
{
	infoPlayerText[FOOD] = new Text;
	infoPlayerText[FOOD]->setText((std::string) FOOD + " : 0", SIZE_CARAC);
	infoPlayerText[FOOD]->setCol(1.0f, 0, 0, 0.8f);
	infoPlayerText[FOOD]->setPos(0.01f, 0.02f);
}

void InfoBullePlayer::initLinemate()
{
	infoPlayerText[LINEMATE] = new Text;
	infoPlayerText[LINEMATE]->setText((std::string) LINEMATE + " : 0", SIZE_CARAC);
	infoPlayerText[LINEMATE]->setCol(0, 1.0f, 0, 0.8f);
	infoPlayerText[LINEMATE]->setPos(0.01f, 0.05f);
}

void InfoBullePlayer::initDeraumere()
{
	infoPlayerText[DERAUMERE] = new Text;
	infoPlayerText[DERAUMERE]->setText((std::string) DERAUMERE + " : 0", SIZE_CARAC);
	infoPlayerText[DERAUMERE]->setCol(0, 0, 1.0f, 0.8f);
	infoPlayerText[DERAUMERE]->setPos(0.01f, 0.08f);
}

void InfoBullePlayer::initSibur()
{
	infoPlayerText[SIBUR] = new Text;
	infoPlayerText[SIBUR]->setText((std::string) SIBUR + " : 0", SIZE_CARAC);
	infoPlayerText[SIBUR]->setCol(1.0f, 1.0f, 0, 0.8f);
	infoPlayerText[SIBUR]->setPos(0.01f, 0.11f);
}

void InfoBullePlayer::initMendiane()
{
	infoPlayerText[MENDIANE] = new Text;
	infoPlayerText[MENDIANE]->setText((std::string) MENDIANE + " : 0", SIZE_CARAC);
	infoPlayerText[MENDIANE]->setCol(1.0f, 0.41f, 0.59f, 0.8f);
	infoPlayerText[MENDIANE]->setPos(0.01f, 0.14f);
}

void InfoBullePlayer::initPhiras()
{
	infoPlayerText[PHIRAS] = new Text;
	infoPlayerText[PHIRAS]->setText((std::string) PHIRAS + " : 0", SIZE_CARAC);
	infoPlayerText[PHIRAS]->setCol(0.25f, 0.88f, 0.81f, 0.8f);
	infoPlayerText[PHIRAS]->setPos(0.01f, 0.17f);
}

void InfoBullePlayer::initThystame()
{
	infoPlayerText[THYSTAME] = new Text;
	infoPlayerText[THYSTAME]->setText((std::string) THYSTAME + " : 0", SIZE_CARAC);
	infoPlayerText[THYSTAME]->setCol(0.5f, 0.5f, 0.5f, 0.8f);
	infoPlayerText[THYSTAME]->setPos(0.01f, 0.20f);
}

void InfoBullePlayer::initIdPlayer()
{
	infoPlayerText[ID_PLAYER] = new Text;
	infoPlayerText[ID_PLAYER]->setText((std::string) ID_PLAYER + " : 0", SIZE_CARAC);
	infoPlayerText[ID_PLAYER]->setCol(1.0f, 1.0f, 1.0f, 0.8f);
	infoPlayerText[ID_PLAYER]->setPos(0.01f, 0.23f);
}

void InfoBullePlayer::initLevelPlayer()
{
	infoPlayerText[LEVEL_PLAYER] = new Text;
	infoPlayerText[LEVEL_PLAYER]->setText((std::string) LEVEL_PLAYER + " : 0", SIZE_CARAC);
	infoPlayerText[LEVEL_PLAYER]->setCol(1.0f, 1.0f, 1.0f, 0.8f);
	infoPlayerText[LEVEL_PLAYER]->setPos(0.01f, 0.26f);
}

void InfoBullePlayer::initTeamPlayer()
{
	infoPlayerText[TEAM_PLAYER] = new Text;
	infoPlayerText[TEAM_PLAYER]->setText((std::string) TEAM_PLAYER + " : 0", SIZE_CARAC);
	infoPlayerText[TEAM_PLAYER]->setCol(1.0f, 1.0f, 1.0f, 0.8f);
	infoPlayerText[TEAM_PLAYER]->setPos(0.01f, 0.29f);
}



bool InfoBullePlayer::update(std::vector<int> infoPlayer, std::string team)
{
	if (infoPlayer.size() != 9)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[InfoBullePlayer] Bad nb args for infoPlayer");
		return (false);
	}
	infoPlayerText[FOOD]->setText((std::string) FOOD + " : " + Utils::intToString(infoPlayer[0]), SIZE_CARAC);
	infoPlayerText[LINEMATE]->setText((std::string) LINEMATE + " : " + Utils::intToString(infoPlayer[1]), SIZE_CARAC);
	infoPlayerText[DERAUMERE]->setText((std::string) DERAUMERE + " : " + Utils::intToString(infoPlayer[2]), SIZE_CARAC);
	infoPlayerText[SIBUR]->setText((std::string) SIBUR + " : " + Utils::intToString(infoPlayer[3]), SIZE_CARAC);
	infoPlayerText[MENDIANE]->setText((std::string) MENDIANE + " : " + Utils::intToString(infoPlayer[4]), SIZE_CARAC);
	infoPlayerText[PHIRAS]->setText((std::string) PHIRAS + " : " + Utils::intToString(infoPlayer[5]), SIZE_CARAC);
	infoPlayerText[THYSTAME]->setText((std::string) THYSTAME + " : " + Utils::intToString(infoPlayer[6]), SIZE_CARAC);
	infoPlayerText[ID_PLAYER]->setText((std::string) ID_PLAYER + " : " + Utils::intToString(infoPlayer[7]), SIZE_CARAC);
	infoPlayerText[LEVEL_PLAYER]->setText((std::string) LEVEL_PLAYER + " : " + Utils::intToString(infoPlayer[8]), SIZE_CARAC);
	infoPlayerText[TEAM_PLAYER]->setText((std::string) TEAM_PLAYER + " : " + team, SIZE_CARAC);
	return (true);
}
