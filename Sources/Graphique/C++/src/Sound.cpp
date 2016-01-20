//
// Sound.cpp for Sound.cpp in /home/lelong_t/rendu/zappy_graphique/src
// 
// Made by Théophile
// Login   <lelong_t@epitech.net>
// 
// Started on  Wed Jun 17 17:42:55 2015 Théophile
// Last update Wed Jun 17 17:42:58 2015 Théophile
//

#include "Sound.h"

Sound::Sound()
{
}

Sound::~Sound()
{
	this->system_->release();
}

bool Sound::soundInit()
{
	if (FMOD::System_Create(&system_) != FMOD_OK)
	{
		return (false);
	}
	this->system_->init(100, FMOD_INIT_NORMAL, NULL);
	return (true);
}

bool Sound::loadSong(const std::string &file)
{
	this->system_->createSound(file.c_str(), FMOD_DEFAULT, 0, &(this->sounds_[file]));
	return (true);
}

bool Sound::playSound(std::string song, bool loop)
{
	if (loop == false)
		this->sounds_[song]->setMode(FMOD_LOOP_OFF);
	else
	{
		this->sounds_[song]->setMode(FMOD_LOOP_NORMAL);
		this->sounds_[song]->setLoopCount(-1);
	}
	this->system_->playSound(this->sounds_[song], NULL, false, &this->channel_[song]);
	return (true);
}

bool Sound::pauseSound(std::string song)
{
	this->system_->playSound(this->sounds_[song], NULL, true, &this->channel_[song]);
	return (true);
}

bool Sound::deleteSound(const std::string &song)
{
	this->sounds_[song]->release();
	return (true);
}
