#include "Egg.h"


Egg::Egg(int id, int x, int y, const std::string &nameMat, Ogre::SceneManager* sceneManager)
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->sceneManager = sceneManager;
	this->player = sceneManager->createEntity("egg.mesh");
	this->player->setMaterialName(nameMat);
	node = sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
	node->attachObject(this->player);
	node->scale(0.1f, 0.1f, 0.1f);
	node->setPosition(Ogre::Vector3(x, 0.0f, y));
}

void Egg::setId(int newId)
{
	this->id = newId;
}

int Egg::getId() const
{
	return (id);
}

void Egg::endFork(const std::string &nameMat)
{
	this->player->setMaterialName(nameMat);
}

void Egg::deathEgg()
{
	this->node->detachAllObjects();
}

Egg::~Egg()
{
}
