//
// InfobulleChat.cpp for InfobulleChat.cpp in /home/lelong_t/rendu/zappy_graphique/src
// 
// Made by Théophile
// Login   <lelong_t@epitech.net>
// 
// Started on  Mon Jun 29 16:21:41 2015 Théophile
// Last update Mon Jun 29 16:22:01 2015 Théophile
//

#include "InfoBulleChat.h"

InfoBulleChat::InfoBulleChat()
{
	this->iteratorMsg_ = 0;
	this->posXText_ = 0.01f;
	this->posYText_ = 0.6f;
	this->initInfoBulle_ = false;
}

InfoBulleChat::~InfoBulleChat()
{	
}

void InfoBulleChat::initMsgCommand()
{
	size_t i(0);

	while (i < 10)
	{
		this->msgCommand_.push_back(new Text);
		this->msgCommand_[i]->setText("Empty", 0.03f);
		this->msgCommand_[i]->setCol(1.0f, 1.0f, 1.0f, 0);
		this->msgCommand_[i]->setPos(this->posXText_,
			this->posYText_ + (i * POSYDIFF));
		i++;
	}
}

void InfoBulleChat::createMsg(const std::string &msgCommand, float r, float g, float b)
{
	if (initInfoBulle_ == false)
	{
		initMsgCommand();
		initInfoBulle_ = true;
	}
	if (this->iteratorMsg_ < 10)
	{
		this->msgCommand_[this->iteratorMsg_]->setText(msgCommand, 0.03f);
		this->msgCommand_[this->iteratorMsg_]->setCol(r, g, b, 0.8f);
		this->msgCommand_[this->iteratorMsg_]->setPos(this->posXText_,
			this->posYText_ + (this->iteratorMsg_ * POSYDIFF));
		this->msgCommand_[this->iteratorMsg_]->showText();
		this->iteratorMsg_++;
	}
	else
	{
		this->sortMsg();
		this->iteratorMsg_--;
		this->msgCommand_[this->iteratorMsg_]->setText(msgCommand, 0.03f);
		this->msgCommand_[this->iteratorMsg_]->setCol(r, g, b, 0.8f);
		this->msgCommand_[this->iteratorMsg_]->setPos(this->posXText_,
			this->posYText_ + (this->iteratorMsg_ * POSYDIFF));
		this->msgCommand_[this->iteratorMsg_]->showText();
	}
}

void InfoBulleChat::sortMsg()
{
	size_t pos(0);
	size_t posMax(this->msgCommand_.size() - 1);
	Ogre::String tmp;

	while (pos < this->msgCommand_.size())
	{
		if (pos != posMax)
		{
			this->msgCommand_[pos]->setText(this->msgCommand_[pos + 1]->getText(), 0.03f);
			tmp = this->msgCommand_[pos + 1]->getText();
		}
		pos++;
	}
}