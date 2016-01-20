#pragma once

#ifndef APP_H_
#define APP_H_

#include <Ogre.h>
#include "Menu.h"
#include "NetworkManager.h"
#include "Game.h"

class App
{
public:
	App();
	virtual ~App();
	bool start();

private:
	Ogre::Root *mRoot;
	Ogre::RenderWindow* mWindow;
};

#endif