#include "App.h"


App::App() : mRoot(0)
{
}


App::~App()
{
	delete mRoot;
}

bool App::start()
{
	mRoot = new Ogre::Root("plugins_d.cfg", "ogre.cfg", "Ogre.log");
	Ogre::ConfigFile configFile;
	configFile.load("resources_d.cfg");
	Ogre::ConfigFile::SectionIterator seci = configFile.getSectionIterator();
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}
	if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
	{
		return false;
	}
	mWindow = mRoot->initialise(true, "ZappyGraph");
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	Game* game = new Game();
	NetworkManager *net = new NetworkManager(game);
	Menu *menuManager = new Menu(net);
	game->init(mRoot, mWindow, menuManager, net);
	game->createMenu();
	while (true)
	{
		net->update();
		Ogre::WindowEventUtilities::messagePump();
		if (mWindow->isClosed())
			return false;
		if (!mRoot->renderOneFrame())
			return false;
	}
	return true;
}