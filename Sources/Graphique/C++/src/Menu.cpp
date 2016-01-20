#include "Menu.h"

Menu::Menu(NetworkManager *net)
{
	this->net = net;
	isInit = false;
	state = 0;
}


Menu::~Menu()
{
}


void Menu::init()
{
	overlayManager = Ogre::OverlayManager::getSingletonPtr();
}

void Menu::create()
{
	state = 1;
	Ogre::FontManager *fontMgr = Ogre::FontManager::getSingletonPtr();
	Ogre::ResourcePtr font = fontMgr->create("MyFont", "General");
	font->setParameter("type", "truetype");
	font->setParameter("source", "vipond_octic.ttf");
	font->setParameter("size", "26");
	font->setParameter("resolution", "96");
	font->load();

	overlay = overlayManager->create("Overlay");

	//BACK


	Ogre::OverlayContainer* backPan = static_cast<Ogre::OverlayContainer*>(
		overlayManager->createOverlayElement("Panel", "PanelBack"));
	backPan->setPosition(0.0, 0.0);
	backPan->setDimensions(1.0, 1.0);
	backPan->setMaterialName("accueil");

	//CURSOR


	cursorPan = static_cast<Ogre::OverlayContainer*>(
		overlayManager->createOverlayElement("Panel", "PanelCursor"));
	cursorPan->setMetricsMode(Ogre::GMM_PIXELS);
	cursorPan->setPosition(0, 0);
	cursorPan->setDimensions(25, 25);
	cursorPan->setMaterialName("cursorMat");

	//STATE
	StatePan = static_cast<Ogre::OverlayContainer*>(
		overlayManager->createOverlayElement("Panel", "PanelState"));
	StatePan->setPosition(0.0, 0.0);
	StatePan->setDimensions(1.0, 0.2);

	textState = static_cast<Ogre::TextAreaOverlayElement*>(
		overlayManager->createOverlayElement("TextArea", "TextAreaState"));
	textState->setPosition(0.31, 0.53);
	textState->setDimensions(0.25, 0.01);
	textState->setCaption("Loading...");
	textState->setFontName(font->getName());
	textState->setColourBottom(Ogre::ColourValue(0.7, 0.7, 0.7));
	textState->setColourTop(Ogre::ColourValue(0.1, 0.1, 0.1));
	textState->setCharHeight(0.0);

	//TITRE
	Ogre::OverlayContainer* titrePan = static_cast<Ogre::OverlayContainer*>(
		overlayManager->createOverlayElement("Panel", "PanelTitre"));
	titrePan->setPosition(0.0, 0.0);
	titrePan->setDimensions(1.0, 0.2);

	Ogre::TextAreaOverlayElement* textTitre = static_cast<Ogre::TextAreaOverlayElement*>(
		overlayManager->createOverlayElement("TextArea", "TextAreaTitre"));
	textTitre->setPosition(0.365, 0.1);
	textTitre->setDimensions(0.25, 0.01);
	textTitre->setCaption("Zappy");
	textTitre->setCharHeight(0.2);
	textTitre->setFontName(font->getName());
	textTitre->setColourBottom(Ogre::ColourValue(0.8, 0.8, 0.8));
	textTitre->setColourTop(Ogre::ColourValue(0.1, 0.1, 0.1));

	//BUTTON

	buttonPan = static_cast<Ogre::OverlayContainer*>(
		overlayManager->createOverlayElement("Panel", "PanelButton"));
	buttonPan->setPosition(0.57, 0.475);
	buttonPan->setDimensions(0.1, 0.05);
	buttonPan->setMaterialName("buttonMat");

	Ogre::TextAreaOverlayElement* textButton = static_cast<Ogre::TextAreaOverlayElement*>(
		overlayManager->createOverlayElement("TextArea", "TextAreaButton"));
	textButton->setPosition(0.01, 0.01);
	textButton->setDimensions(0.1, 0.05);
	textButton->setCaption("Connect");
	textButton->setCharHeight(0.05);
	textButton->setFontName(font->getName());
	textButton->setColourBottom(Ogre::ColourValue(0.9, 0.9, 0.9));
	textButton->setColourTop(Ogre::ColourValue(0.6, 0.6, 0.6));

	//ADDRESSE
	panel = static_cast<Ogre::OverlayContainer*>(
		overlayManager->createOverlayElement("Panel", "PanelAddr"));
	panel->setPosition(0.31, 0.475);
	panel->setDimensions(0.25, 0.05);
	panel->setMaterialName("darkInput");

	textArea = static_cast<Ogre::TextAreaOverlayElement*>(
		overlayManager->createOverlayElement("TextArea", "TextAreaAddr"));
	textArea->setPosition(0.01, 0.015);
	textArea->setDimensions(0.25, 0.01);
	textArea->setCaption(addr);
	textArea->setCharHeight(0.03);
	textArea->setFontName(font->getName());
	textArea->setColourBottom(Ogre::ColourValue(0.8, 0.8, 0.8));
	textArea->setColourTop(Ogre::ColourValue(0.6, 0.6, 0.6));

	overlay->add2D(backPan);
	overlay->add2D(panel);
	overlay->add2D(titrePan);
	overlay->add2D(StatePan);
	overlay->add2D(buttonPan);
	overlay->add2D(cursorPan);
	buttonPan->addChild(textButton);
	panel->addChild(textArea);
	titrePan->addChild(textTitre);
	StatePan->addChild(textState);
	
	overlay->show();
}

void Menu::removeMenu()
{
	overlayManager->destroyAll();
}

void Menu::click(int x, int y)
{
	int buttonx;
	int buttony;
	int buttonx1;
	int buttony1;

	if (state == 1)
	{
		y += 25;
		buttonx = 1920 * buttonPan->getLeft();
		buttony = 1080 * buttonPan->getTop();
		buttonx1 = buttonx + 1920 * buttonPan->getWidth();
		buttony1 = buttony + 1080 * buttonPan->getHeight();
		if (x > buttonx && y > buttony && x < buttonx1 && y < buttony1)
		{
			textState->setCharHeight(0.05);
			std::string result = net->connecte(addr);
			if (result == "")
			{
				state = 2;
				removeMenu();
			}
			else
				textState->setCaption(result);
		}
	}
}

void Menu::mouseMove(int x, int y)
{
	if (state == 1)
		cursorPan->setPosition(x, y);
}

void Menu::key(char c)
{
	if (state == 1)
	{
		if (c == 8 && addr.length() > 0)
			addr.erase(addr.end() - 1);
		else if (c >= '0' && c <= '9' || c == ':' || c == '.')
			addr.push_back(c);
		textArea->setCaption(addr);
	}
}