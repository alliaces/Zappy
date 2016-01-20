/*
** InfoBullePlayer.h for InfoBullePlayer.h in /home/lelong_t/rendu/zappy_graphique/includes
** 
** Made by Théophile
** Login   <lelong_t@epitech.net>
** 
** Started on  Mon Jun 29 16:14:13 2015 Théophile
** Last update Mon Jun 29 16:14:35 2015 Théophile
*/

#ifndef		INFOBULLEPLAYER_H_
# define	INFOBULLEPLAYER_H_

#include <map>
#include "Text.h"
#include "Utils.hpp"

# define SIZE_CARAC 0.03f

/*
** ressources names and player infos
*/
# define FOOD "Food"
# define LINEMATE "Linemate"
# define DERAUMERE "Deraumere"
# define SIBUR "Sibur"
# define MENDIANE "Mendiane"
# define PHIRAS "Phiras"
# define THYSTAME "Thystane"
# define ID_PLAYER "ID Player"
# define LEVEL_PLAYER "Level Player"
# define TEAM_PLAYER "Team Player"


class InfoBullePlayer
{
public:
	InfoBullePlayer();
	~InfoBullePlayer();
	void initFood();
	void initLinemate();
	void initDeraumere();
	void initSibur();
	void initMendiane();
	void initPhiras();
	void initThystame();
	void initIdPlayer();
	void initLevelPlayer();
	void initTeamPlayer();
	bool update(std::vector<int> infoPlayer, std::string team);
private:
	std::map<std::string, Text*> infoPlayerText;
};

#endif
