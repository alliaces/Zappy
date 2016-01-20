#include <math.h> 
#include "Input.h"
#include "Game.h"

Input::Input(Ogre::RenderWindow* mWindow, Ogre::Camera* mCamera, Ogre::SceneManager* mSceneMgr, Menu *menuManager, Game *game)
{
	this->mWindow = mWindow;
	this->mCamera = mCamera;
	this->mSceneMgr = mSceneMgr;
	this->menuManager = menuManager;
	this->game = game;
	this->select = NULL;
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");

	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

#if defined OIS_WIN32_PLATFORM
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
	pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
	pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif

	mInputManager = OIS::InputManager::createInputSystem(pl);
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));

	mKeyboard->setTextTranslation(OIS::Keyboard::Ascii);

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	windowResized(mWindow);
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	montinue = true;
	LmouseState = false;
	RmouseState = false;
}

OIS::Mouse* Input::get_mouse()
{
	return (mMouse);
}


Input::~Input()
{
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
}

bool Input::frameRenderingQueued(const Ogre::FrameEvent& evt)
{

	mKeyboard->capture();
	mMouse->capture();
	game->update(evt.timeSinceLastFrame);
	return montinue;
}

void Input::windowResized(Ogre::RenderWindow* wnd)
{
	unsigned int width, height, depth;
	int left, top;
	wnd->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void Input::windowClosed(Ogre::RenderWindow* wnd)
{
	if (wnd == mWindow)
	{
		if (mInputManager)
		{
			mInputManager->destroyInputObject(mMouse);
			mInputManager->destroyInputObject(mKeyboard);

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}
}

bool Input::mouseMoved(const OIS::MouseEvent &e)
{
	menuManager->mouseMove(e.state.X.abs, e.state.Y.abs);
	if (LmouseState == true)
	{
		int x = e.state.X.abs - mousex;
		int y = e.state.Y.abs - mousey;
		float a = mCamera->getOrientation().getYaw().valueRadians();
		mCamera->move(mCamera->getRealRight() * -x * 0.01f);

		Ogre::Vector3 v = mCamera->getRealRight();
		float ax = v.x;
		v.x = v.z;
		v.z = -ax;
		mCamera->move(v * y * 0.01f);
	}
	if (RmouseState == true)
	{
		float x = e.state.X.abs - mousex;
		float y = e.state.Y.abs - mousey;
		mCamera->yaw(Ogre::Degree(-x / 10.0f));
		mCamera->pitch(Ogre::Degree(-y / 10.0f));
	}
	mousex = e.state.X.abs;
	mousey = e.state.Y.abs;
	return true;
}

bool Input::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	menuManager->click(e.state.X.abs, e.state.Y.abs);
	if (id == OIS::MB_Left)
	  {
	    if (select)
	      select->showBoundingBox(false);
	    Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(e.state.X.abs/(float)(e.state.width), e.state.Y.abs/(float)(e.state.height));
	    Ogre::RaySceneQuery* RayQuery;
	    RayQuery = mSceneMgr->createRayQuery(mouseRay);
	    RayQuery->setSortByDistance(true, 1);
	    Ogre::RaySceneQueryResult& result = RayQuery->execute();
	    Ogre::RaySceneQueryResult::iterator it;
	    it = result.begin();
	    if (it != result.end())
	      if (it->movable)
	      {
			select = it->movable->getParentSceneNode();
			game->selectPlayer(select);
	      }
	    if (select)
	      select->showBoundingBox(true);
	  }
	if (id == OIS::MB_Right)
		LmouseState = true;
	if (id == OIS::MB_Middle)
		RmouseState = true;
	return true;
}

bool Input::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	if (id == OIS::MB_Right)
		LmouseState = false;
	if (id == OIS::MB_Middle)
		RmouseState = false;
	return true;
}

bool Input::keyPressed(const OIS::KeyEvent &e)
{
	if (e.key == OIS::KC_NUMPAD0)
		menuManager->key('0');
	else if (e.key == OIS::KC_NUMPAD1)
		menuManager->key('1');
	else if (e.key == OIS::KC_NUMPAD2)
		menuManager->key('2');
	else if (e.key == OIS::KC_NUMPAD3)
		menuManager->key('3');
	else if (e.key == OIS::KC_NUMPAD4)
		menuManager->key('4');
	else if (e.key == OIS::KC_NUMPAD5)
		menuManager->key('5');
	else if (e.key == OIS::KC_NUMPAD6)
		menuManager->key('6');
	else if (e.key == OIS::KC_NUMPAD7)
		menuManager->key('7');
	else if (e.key == OIS::KC_NUMPAD8)
		menuManager->key('8');
	else if (e.key == OIS::KC_NUMPAD9)
		menuManager->key('9');
	else if (e.key == OIS::KC_NUMPADCOMMA)
		menuManager->key('.');
	else
		menuManager->key(e.text);
	switch (e.key)
	{
		case OIS::KC_ESCAPE:
			montinue = false;
			break;
	}
	return montinue;
}

bool Input::keyReleased(const OIS::KeyEvent &e)
{
	return true;
}
