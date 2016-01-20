/*
** ISound.h for ISound.h in /home/lelong_t/rendu/zappy_graphique/includes
** 
** Made by Théophile
** Login   <lelong_t@epitech.net>
** 
** Started on  Wed Jun 17 18:03:33 2015 Théophile
** Last update Wed Jun 17 18:04:03 2015 Théophile
*/

#ifndef		ISOUND_H_
# define	ISOUND_H_

# define MAIN_SOUND "./04 - The Legend of Zelda - Twilight Princess - Menu Select.mp3"
# define CLICK_SOUND "./click.WAV"
# define WALK_SOUND "./footsteps_on_soft_foam_play_mat.mp3"
# define BATTLE_SOUND "./Zelda- Twilight Princess Music - Hyrule Field Main Theme.mp3"
//# define BATTLE_SOUND "./Medieval 2 _ Total War Soundtrack - Duke of Death.mp3"
# define DEATH_PLAYER_SOUND "./wilhelm_scream.mp3"
# define EXPULSE_SOUND "./300 - This is Sparta.mp3"

# include <vector>
# include <iostream>
# include <string>
# include <cstdlib>
# include <map>
# include "fmod.hpp"

class ISound
{
 public:
  virtual ~ISound() {}
  virtual bool soundInit() = 0;
  virtual bool loadSong(const std::string &) = 0;
  virtual bool playSound(std::string, bool) = 0;
  virtual bool pauseSound(std::string) = 0;

 protected:
  FMOD::System *system_;
  std::map<std::string, FMOD::Sound *> sounds_;
  std::map<std::string, FMOD::Channel *> channel_;
};

#endif
