#pragma once

#ifndef INPUT_H_
#define INPUT_H_

#include <Ogre.h>
#include <OIS/OIS.h>
#include "Menu.h"

class Game;

class Input : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener
{
public:
	Input(Ogre::RenderWindow* mWindow, Ogre::Camera* mCamera, Ogre::SceneManager* mSceneMgr, Menu* menuManager, Game *game);
	virtual ~Input();
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	void windowResized(Ogre::RenderWindow* wnd);
	void windowClosed(Ogre::RenderWindow* wnd);
	bool mouseMoved(const OIS::MouseEvent &e);
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool keyPressed(const OIS::KeyEvent &e);
	bool keyReleased(const OIS::KeyEvent &e);
	OIS::Mouse* get_mouse();

private:
	Game *game;
	Ogre::RenderWindow* mWindow;
	Ogre::Camera*       mCamera;
	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneNode* select;
	bool montinue;
	OIS::InputManager*  mInputManager;
	OIS::Mouse*         mMouse;
	OIS::Keyboard*      mKeyboard;
	Menu *menuManager;
	bool LmouseState;
	bool RmouseState;
	int camx;
	int camy;
	int lcamx;
	int lcamy;
	int mousex;
	int mousey;
};

#endif
