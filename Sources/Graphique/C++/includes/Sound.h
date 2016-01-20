/*
** Sound.h for Sound.h in /home/lelong_t/rendu/zappy_graphique/includes
** 
** Made by Théophile
** Login   <lelong_t@epitech.net>
** 
** Started on  Wed Jun 17 17:43:21 2015 Théophile
** Last update Wed Jun 17 17:43:51 2015 Théophile
*/

#ifndef		SOUND_H_
# define	SOUND_H_

#include "ISound.h"

class Sound : public ISound
{
public:
	Sound();
	~Sound();
	bool soundInit();
	bool loadSong(const std::string &);
  	bool playSound(std::string, bool);
	bool pauseSound(std::string);
	bool deleteSound(const std::string &song);
};

#endif
