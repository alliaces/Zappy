/*
** InfoBulleChat.h for InfoBulleChat.h in /home/lelong_t/rendu/zappy_graphique/includes
** 
** Made by Théophile
** Login   <lelong_t@epitech.net>
** 
** Started on  Mon Jun 29 16:14:58 2015 Théophile
** Last update Mon Jun 29 16:15:27 2015 Théophile
*/

#ifndef		INFOBULLECHAT_H_
# define	INFOBULLECHAT_H_

#include <Ogre.h>
#include <vector>
#include "Text.h"

# define POSYDIFF 0.03

class InfoBulleChat
{
public:
	InfoBulleChat();
	~InfoBulleChat();
	void createMsg(const std::string &msgCommand, float r, float g, float b);
private:
	void initMsgCommand();
	void sortMsg();
	bool initInfoBulle_;
	std::vector<Text*> msgCommand_;
	int iteratorMsg_;
	float posXText_;
	float posYText_;
};

#endif
