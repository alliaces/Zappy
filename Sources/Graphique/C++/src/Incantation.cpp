//
// Incantation.cpp for Incantation.cpp in /home/lelong_t/rendu/zappy_graphique/src
// 
// Made by Théophile
// Login   <lelong_t@epitech.net>
// 
// Started on  Fri Jul  3 12:21:36 2015 Théophile
// Last update Fri Jul  3 12:21:38 2015 Théophile
//

#include "Incantation.h"

Incantation::Incantation(int id, int x, int y, int level, Ogre::ColourValue color, Ogre::SceneManager* sceneManager)
{
	this->id_ = id;
	this->x_ = x;
	this->y_ = y;
	this->level_ = level;
	this->color_ = color;
	this->sceneManager_ = sceneManager;
	this->incantation_ = this->sceneManager_->createEntity("egg.mesh");
	this->incantation_->setMaterialName("incantationlvl" + Utils::intToString(this->level_ + 1));

	this->node_ = this->sceneManager_->getRootSceneNode()->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
	this->node_->attachObject(this->incantation_);
	this->node_->scale(0.15f, 0.15f, 0.15f);
	this->node_->setPosition(Ogre::Vector3(x, 0.0f, y));
}

Incantation::~Incantation()
{
}

int Incantation::getId() const
{
	return (this->id_);
}

int Incantation::getPosX() const
{
	return (this->x_);
}

int Incantation::getPosY() const
{
	return (this->y_);
}

void Incantation::endIncantation()
{
	this->node_->detachAllObjects();
}
