//
// Text.cpp for Text.cpp in /home/lelong_t/rendu/zappy_graphique/src
// 
// Made by Théophile
// Login   <lelong_t@epitech.net>
// 
// Started on  Thu Jun 25 14:12:20 2015 Théophile
// Last update Thu Jun 25 14:12:22 2015 Théophile
//

#include "Text.h"

int Text::init = 0;

Text::Text()
{
	this->_overlayManage = Ogre::OverlayManager::getSingletonPtr();
	if (init == 1)
	{
		this->_panel = static_cast<Ogre::OverlayContainer*>(this->_overlayManage->createOverlayElement("Panel", "GUI"));
		this->_panel->setMetricsMode(Ogre::GMM_PIXELS);
		this->_panel->setPosition(0, 0);
		this->_panel->setDimensions(1.0f, 1.0f);
		this->_overlay = this->_overlayManage->create("GUI_OVERLAY");
		this->_overlay->add2D(this->_panel);
	}
	++(this->init);
	szElement = "element_" + Ogre::StringConverter::toString(init);
	this->_overlay = this->_overlayManage->getByName("GUI_OVERLAY");
	this->_panel = static_cast<Ogre::OverlayContainer*>(this->_overlayManage->getOverlayElement("GUI"));
	textArea = static_cast<Ogre::TextAreaOverlayElement*>(this->_overlayManage->createOverlayElement("TextArea", szElement));
	this->_panel->addChild(textArea);
	this->_overlay->show();
}

Text::~Text()
{
	this->_overlayManage->destroyOverlayElement(szElement);
	--(this->init);
	if (init == 0)
	{
		this->_overlayManage->destroyOverlayElement("GUI");
		this->_overlayManage->destroy("GUI_OVERLAY");
	}
}

void Text::showText()
{
	this->_overlay->show();
}

void Text::hideText()
{
	this->_overlay->hide();
}

void Text::setText(Ogre::String szString, float caracSize)
{
	textArea->setCaption(szString);
	textArea->setDimensions(0.25f, 0.05f);
	textArea->setMetricsMode(Ogre::GMM_RELATIVE);
	textArea->setFontName("MyFont");
	textArea->setCharHeight(caracSize);
}

void Text::setPos(float x, float y)
{
	textArea->setPosition(x, y);
}

void Text::setCol(float R, float G, float B, float I)
{
	textArea->setColour(Ogre::ColourValue(R, G, B, I));
}

Ogre::String Text::getText() const
{
	return (textArea->getCaption());
}

/*void Text::createPanel()
{
	panel = static_cast<Ogre::OverlayContainer*>(
		overlayManager->createOverlayElement("Panel", "PanelAddr"));
	panel->setPosition(0.31, 0.475);
	panel->setDimensions(0.25, 0.05);
	panel->setMaterialName("darkInput");
	this->_overlay->add2D(this->panel);
}*/
