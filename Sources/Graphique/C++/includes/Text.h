/*
** Text.h for Text.h in /home/lelong_t/rendu/zappy_graphique/includes
** 
** Made by Théophile
** Login   <lelong_t@epitech.net>
** 
** Started on  Thu Jun 25 14:13:37 2015 Théophile
** Last update Thu Jun 25 14:14:01 2015 Théophile
*/

#pragma once

#ifndef		TEXT_H_
# define	TEXT_H_

#include <iostream>
#include <Ogre.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreStringConverter.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>

class Text
{
public:
	Text();
	~Text();
	void setText(Ogre::String szString, float caracSize);
	void setPos(float x, float y);
	void setCol(float R, float G, float B, float I);
	Ogre::String getText() const;
	void showText();
	void hideText();
private:
	Ogre::Overlay *_overlay;
	Ogre::OverlayContainer *_panel;
	Ogre::OverlayManager *_overlayManage;
	Ogre::TextAreaOverlayElement *textArea;
	static int init;
	Ogre::String szElement;
};

#endif
