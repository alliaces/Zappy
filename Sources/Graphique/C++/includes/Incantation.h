/*
** Incantation.h for Incantation.h in /home/lelong_t/rendu/zappy_graphique/includes
** 
** Made by Théophile
** Login   <lelong_t@epitech.net>
** 
** Started on  Fri Jul  3 12:22:09 2015 Théophile
** Last update Fri Jul  3 12:22:32 2015 Théophile
*/

#ifndef		INCANTATION_H_
# define	INCANTATION_H_

#include <Ogre.h>
#include "Utils.hpp"

class Incantation
{
public:
	Incantation(int id, int x, int y, int level,
		Ogre::ColourValue color,
		Ogre::SceneManager* sceneManager);
	~Incantation();
	int getId() const;
	int getPosX() const;
	int getPosY() const;
	void endIncantation();
private:
	int id_;
	int x_;
	int y_;
	int level_;
	Ogre::ColourValue color_;
	Ogre::Entity *incantation_;
	Ogre::SceneNode *node_;
	Ogre::SceneManager* sceneManager_;
};

#endif
