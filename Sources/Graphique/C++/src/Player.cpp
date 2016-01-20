#include "Player.h"


Player::Player(int id, int x, int y, char orient, char level, std::string team,
	float speedAnim,
	int sizeMapX,
	int sizeMapY,
	Ogre::ColourValue color, Ogre::SceneManager* sceneManager)
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->xOld = x;
	this->yOld = y;
	this->sizeMapX = sizeMapX - 1;
	this->sizeMapY = sizeMapY - 1;
	this->orient = 3;
	this->level = level;
	this->team = team;
	this->color = color;
	this->resources.push_back(0);
	this->resources.push_back(0);
	this->resources.push_back(0);
	this->resources.push_back(0);
	this->resources.push_back(0);
	this->resources.push_back(0);
	this->resources.push_back(0);
	this->resources.push_back(0);
	this->resources.push_back(0);
	this->sceneManager = sceneManager;
	this->player = sceneManager->createEntity("Player_level1.mesh");
	this->player->setMaterialName("Tlevel" + Utils::intToString(level));
	anim = this->player->getAnimationState("Walk");
	take = this->player->getAnimationState("Take");
	dead = this->player->getAnimationState("Dead");
	anim->setEnabled(false);
	take->setEnabled(true);
	dead->setLoop(false);
	dead->setEnabled(false);
	take->setLoop(false);
	take->setTimePosition(48);
	dead->setTimePosition(1);
	anim->setLoop(true);
	this->speedAnim = speedAnim;
	
/*	mat = new Ogre::MaterialPtr;
	*mat = this->player->getSubEntity(0)->getMaterial();
	(*mat)->clone(Utils::intToString(color.r) + Utils::intToString(y) + Utils::intToString(x));
//	this->player->setMaterialName(Utils::intToString(color.r) + Utils::intToString(y) + Utils::intToString(x));
	this->player->getSubEntity(0)->getMaterial()->setAmbient(0.01, 0.01, 0.01);
	this->player->getSubEntity(0)->getMaterial()->setDiffuse(color);*/
	node = sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
	node->attachObject(this->player);
	resetO();
	this->orient = orient;
	updateO();
	node->scale(0.6f, 0.6f, 0.6f);
	node->setPosition(Ogre::Vector3(x, -0.3f, y));
}

void Player::resetO()
{
	if (orient == 1)
		node->yaw(Ogre::Degree(180));
	if (orient == 2)
		node->yaw(Ogre::Degree(-90));
	if (orient == 4)
		node->yaw(Ogre::Degree(90));
}

void Player::updateO()
{
	if (orient == 1)
		node->yaw(Ogre::Degree(180));
	if (orient == 2)
		node->yaw(Ogre::Degree(90));
	if (orient == 4)
		node->yaw(Ogre::Degree(-90));
}

bool Player::update(Ogre::Real time)
{
	if (anim->getEnabled() == true)
	{
		anim->addTime(time);
		if (x != this->xOld || y != this->yOld)
		{
			/*
			** up -> down
			*/
			if ((node->getPosition().z >= 0 && node->getPosition().z <= this->sizeMapY) && x == 0 &&
				(y >= 0 && y <= this->sizeMapY) && (this->xOld >= 0 && this->xOld <= this->sizeMapX) && this->orient == 2)
			{
				node->setPosition(Ogre::Vector3(node->getPosition().x - this->sizeMapX, node->getPosition().y, node->getPosition().z));
				anim->setEnabled(false);
				return (true);
			}
			/*
			** down -> up
			*/
			if ((node->getPosition().z >= 0 && node->getPosition().z <= this->sizeMapY) && x == this->sizeMapX &&
				(y >= 0 && y <= this->sizeMapY) && this->xOld >= 0 && this->orient == 4)
			{
				node->setPosition(Ogre::Vector3(node->getPosition().x + this->sizeMapX, node->getPosition().y, node->getPosition().z));
				anim->setEnabled(false);
				return (true);
			}
			/*
			** left -> right
			*/
			if (node->getPosition().z == 0 && (x >= 0 && x <= this->sizeMapX) &&
				y == this->sizeMapY && this->yOld == 0 && this->orient == 1)
			{
				node->setPosition(Ogre::Vector3(node->getPosition().x, node->getPosition().y, node->getPosition().z + this->sizeMapY));
				anim->setEnabled(false);
				return (true);
			}
			/*
			** right -> left
			*/
			if ((x >= 0 && x <= this->sizeMapX) &&
				y == 0 && this->yOld == this->sizeMapY && this->orient == 3)
			{
				node->setPosition(Ogre::Vector3(node->getPosition().x, node->getPosition().y, node->getPosition().z - this->sizeMapY));
				anim->setEnabled(false);
				return (true);
			}
		}
		if (node->getPosition().x < x)
			node->setPosition(Ogre::Vector3(node->getPosition().x + this->speedAnim, node->getPosition().y, node->getPosition().z));
		if (node->getPosition().x > x)
			node->setPosition(Ogre::Vector3(node->getPosition().x - this->speedAnim, node->getPosition().y, node->getPosition().z));
		if (node->getPosition().z < y)
			node->setPosition(Ogre::Vector3(node->getPosition().x, node->getPosition().y, node->getPosition().z + this->speedAnim));
		if (node->getPosition().z > y)
			node->setPosition(Ogre::Vector3(node->getPosition().x, node->getPosition().y, node->getPosition().z - this->speedAnim));

		if ((floor(node->getPosition().x * 100 + 0.1) / 100) == x && (floor(node->getPosition().z * 100 + 0.1) / 100) == y)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("[plop]");
			node->setPosition(Ogre::Vector3(x, -0.3f, y));
			anim->setEnabled(false);
		}
	}
	if (dead->getEnabled() == true)
	{
		if (node->getPosition().y > -1)
			node->setPosition(Ogre::Vector3(node->getPosition().x, node->getPosition().y - this->speedAnim, node->getPosition().z));
		else
		{
			node->detachAllObjects();
			return (false);
		}
	}
	take->addTime(time);
	dead->addTime(time);
	return (true);
}

void Player::takeRes()
{
	take->setTimePosition(1);
}

void Player::doDead()
{
	dead->setEnabled(true);
}

void Player::dropRes()
{
	take->setTimePosition(1);
}

void Player::move(int x, int y, int o)
{
	this->xOld = this->x;
	this->yOld = this->y;
	this->x = x;
	this->y = y;
	resetO();
	this->orient = o;
	updateO();
	anim->setEnabled(true);
	//node->setPosition(Ogre::Vector3(x, -0.3f, y));
}

int Player::getId()
{
	return (id);
}

char Player::getLevel() const
{
	return (this->level);
}

void Player::setLevel(char newLevel, Ogre::ColourValue color)
{
	this->level = newLevel;
	this->player->setMaterialName("Tlevel" + Utils::intToString(newLevel));
}

void Player::setResources(std::vector<int> newResources)
{
	this->resources[0] = newResources[0];
	this->resources[1] = newResources[1];
	this->resources[2] = newResources[2];
	this->resources[3] = newResources[3];
	this->resources[4] = newResources[4];
	this->resources[5] = newResources[5];
	this->resources[6] = newResources[6];
	this->resources[7] = this->id;
	this->resources[8] = this->level;
}

const std::string &Player::getTeam() const
{
	return (this->team);
}

const std::vector<int> &Player::getResources() const
{
	return (this->resources);
}

Ogre::SceneNode *Player::getNode() const
{
	return (this->node);
}

Player::~Player()
{
}
