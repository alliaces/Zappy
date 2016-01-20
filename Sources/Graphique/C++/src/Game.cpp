#include "Game.h"
#include "OgreOverlaySystem.h"
#include "NetworkManager.h"


Game::Game()
{
	this->initInfoPlayer = false;
	this->colorLevelPlayer[WHITE] = Ogre::ColourValue(1.0, 1.0, 1.0);
	this->colorLevelPlayer[GREEN] = Ogre::ColourValue(0, 1.0, 0);
	this->colorLevelPlayer[PINK] = Ogre::ColourValue(1.0, 0.2, 1.0);
	this->colorLevelPlayer[RED] = Ogre::ColourValue(1.0, 0, 0);
	this->colorLevelPlayer[PURPLE] = Ogre::ColourValue(0.4, 0, 1.0);
	this->colorLevelPlayer[BROWN] = Ogre::ColourValue(0.6, 0.2, 0);
	this->colorLevelPlayer[BLUE] = Ogre::ColourValue(0, 0, 1.0);
	this->colorLevelPlayer[GOLD] = Ogre::ColourValue(1.0, 0.85, 0);
	this->speedAnim = SPEED_ANIM;
	this->sizeMapX = 0;
	this->sizeMapY = 0;
}

void Game::setSpeedAnim(float newSpeedAnim)
{
	this->speedAnim = newSpeedAnim * SPEED_ANIM;
}

void Game::movePlayer(int id, int x, int y, int o)
{
	int i = 0;
	while (i < players.size())
	{
		if (players[i].getId() == id)
		{
			players[i].move(x, y, o);
			break;
		}
		i++;
	}
}

void Game::fillMap(int x, int y, std::vector<int> data)
{
	map->fillMap(x, y, data);
	if (this->initInfoPlayer == false)
	{
		this->infoPlayer = new InfoBullePlayer;
		this->infosPlayer.push_back(0);
		this->infosPlayer.push_back(0);
		this->infosPlayer.push_back(0);
		this->infosPlayer.push_back(0);
		this->infosPlayer.push_back(0);
		this->infosPlayer.push_back(0);
		this->infosPlayer.push_back(0);
		this->infosPlayer.push_back(0);
		this->infosPlayer.push_back(1);
		infoPlayer->update(this->infosPlayer, "empty");
		this->initInfoPlayer = true;
	}
}

void Game::createTeam(std::string name)
{
	teams.push_back(Team(name));
}

void Game::createPlayer(int id, int x, int y, char orient, char level, std::string teamName)
{
	int i = 0;
	Ogre::ColourValue color;
	while (i < teams.size())
	{
		if (teams[i].name == teamName)
		{
			color = teams[i].color;
			break;
		}
		i++;
	}
	players.push_back(Player(id, x, y, orient, level, teamName, this->speedAnim,
		this->sizeMapX,
		this->sizeMapY,
		this->colorLevelPlayer[level], mSceneMgr));
}

void Game::createEgg(int id)
{
	int i = 0;
	while (i < players.size())
	{
		if (players[i].getId() == id)
		{
			eggs.push_back(Egg(id, players[i].x, players[i].y, "eggFork", mSceneMgr));
			break;
		}
		i++;
	}
}

void Game::eggEndFork(int id, int idPlayer, int x, int y)
{
	int i(0);

	while (i < this->eggs.size() && this->eggs[i].getId() != idPlayer)
		i++;
	if (i == this->eggs.size())
		return;
	this->eggs[i].setId(id);
	this->eggs[i].endFork("egg");
}

void Game::createIncantation(int x, int y, int level, int id)
{
	this->incantation.push_back(Incantation(id, x, y, level, this->colorLevelPlayer[level], mSceneMgr));
}

void Game::createMap(int sizeX, int sizeY)
{
	map = new Map(mSceneMgr, sizeX, sizeY);
	this->sizeMapX = sizeX;
	this->sizeMapY = sizeY;
}

void Game::deleteEgg(int id)
{
	int	i(0);

	while (i < this->eggs.size() && eggs[i].getId() != id)
		i++;
	if (i == this->eggs.size())
		return;
	this->eggs[i].deathEgg();
}

void Game::deleteIncantation(int x, int y, bool success)
{
	int i(0);

	while (i < incantation.size() && (incantation[i].getPosX() != x && incantation[i].getPosY() != y))
		i++;
	if (i == incantation.size())
		return;
	this->incantation[i].endIncantation();
}

void Game::dead(int id)
{
	int i = 0;
	while (i < players.size())
	{
		if (players[i].getId() == id)
		{
			players[i].doDead();
			break;
		}
		i++;
	}
}

void Game::selectPlayer(Ogre::SceneNode *player)
{
	int i = 0;
	Ogre::LogManager::getSingletonPtr()->logMessage("selectPlayer");
	while (i < players.size())
	{
		if (players[i].getNode() == player)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("player found");
			infoPlayer->update(players[i].getResources(), this->players[i].getTeam());
			break;
		}
		i++;
	}
}

void Game::take(int id)
{
	int i = 0;
	while (i < players.size())
	{
		if (players[i].getId() == id)
		{
			players[i].takeRes();
			break;
		}
		i++;
	}
}

void Game::drop(int id)
{
	int i = 0;
	while (i < players.size())
	{
		if (players[i].getId() == id)
		{
			players[i].dropRes();
			break;
		}
		i++;
	}
}

void Game::levelUp(int id, int level)
{
	int i = 0;
	while (i < players.size())
	{
		if (players[i].getId() == id)
		{
			players[i].setLevel(level, this->colorLevelPlayer[level]);
			break;
		}
		i++;
	}
}

void Game::updateInventoryPlayer(int id, int x, int y, std::vector<int> resources)
{
	if (this->initInfoPlayer == true)
	{
		int i(0);

		while (i < players.size() && players[i].getId() != id)
			i++;
		if (i == players.size())
			return;
		this->players[i].setResources(resources);
		this->infosPlayer[0] = resources[0];
		this->infosPlayer[1] = resources[1];
		this->infosPlayer[2] = resources[2];
		this->infosPlayer[3] = resources[3];
		this->infosPlayer[4] = resources[4];
		this->infosPlayer[5] = resources[5];
		this->infosPlayer[6] = resources[6];
		this->infosPlayer[7] = id;
		this->infosPlayer[8] = this->players[i].getLevel();
	}
}

void Game::update(Ogre::Real time)
{
/*	if (map != NULL)
		map->updateMap(time);*/
	int i = 0;
	while (i < players.size())
	{
		if (players[i].update(time) == false)
			players.erase(players.begin() + i);
		i++;
	}
}

void Game::init(Ogre::Root *mRoot, Ogre::RenderWindow* mWindow, Menu *menuManager, NetworkManager* net)
{
	this->menuManager = menuManager;
	this->mWindow = mWindow;
	map = NULL;
	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager", "SceneManager");
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.6, 0.6, 0.6));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	mCamera = mSceneMgr->createCamera("GameCam");
	mCamera->setPosition(Ogre::Vector3(0, 10, 0));
	mCamera->lookAt(Ogre::Vector3(20, 0, 20));
	mCamera->setNearClipDistance(0.1);
	mCamera->setFarClipDistance(0.1);
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0.45, 0.7, 0.8));
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	Ogre::OverlaySystem* pOverlaySystem = new Ogre::OverlaySystem();
	mSceneMgr->addRenderQueueListener(pOverlaySystem);

	input = new Input(mWindow, mCamera, mSceneMgr, menuManager, this);	

	mRoot->addFrameListener(input);
	menuManager->init();
}

void Game::createMenu()
{
	menuManager->create();
}

Game::~Game()
{
}

void Game::OnError(std::string error)
{

}
