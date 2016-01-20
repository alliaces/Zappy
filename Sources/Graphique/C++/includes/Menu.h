#pragma once

#ifndef MENU_H_
#define MENU_H_

#include <Ogre.h>
#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayContainer.h>
#include <OgrePanelOverlayElement.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreFontManager.h>
#include "NetworkManager.h"

class Menu
{
public:
	Menu(NetworkManager* net);
	virtual ~Menu();
	void init();
	void create();
	void removeMenu();
	void click(int x, int y);
	void mouseMove(int x, int y);
	void key(char c);

private:
	std::string addr;
	bool isInit;
	Ogre::Overlay* overlay;
	NetworkManager* net;
	Ogre::OverlayManager* overlayManager;
	Ogre::OverlayContainer* buttonPan;
	Ogre::OverlayContainer* cursorPan;
	Ogre::OverlayContainer* panel;
	Ogre::TextAreaOverlayElement* textArea;
	Ogre::OverlayContainer* StatePan;
	Ogre::TextAreaOverlayElement* textState;
	int state;
};

#endif