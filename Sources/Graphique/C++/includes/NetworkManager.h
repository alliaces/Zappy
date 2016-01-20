#pragma once

#ifndef NETWORKMANAGER_H_
#define NETWORKMANAGER_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <fcntl.h>
#include <algorithm>
#include <fcntl.h>
#include <sys/stat.h>
#include <Ogre.h>
#include "Utils.hpp"
#include "Sound.h"
#include "InfoBullePlayer.h"
#include "InfoBulleChat.h"

/*
** network
*/
#define DEF_PORT 5555

#ifdef WIN32



#elif defined (linux)

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#else

//#error not defined for this platform

#endif

using namespace boost;

class Game;

/*
** Event command
*/
# define NBCMD 25

# define EVENTWELCOME "BIENVENUE"
# define EVENTMSZ "msz"
# define EVENTBCT "bct"
# define EVENTTNA "tna"
# define EVENTPNW "pnw"
# define EVENTPPO "ppo"
# define EVENTPLV "plv"
# define EVENTPIN "pin"
# define EVENTPEX "pex"
# define EVENTPBC "pbc"
# define EVENTPIC "pic"
# define EVENTPIE "pie"
# define EVENTPFK "pfk"
# define EVENTPDR "pdr"
# define EVENTPGT "pgt"
# define EVENTPDI "pdi"
# define EVENTENW "enw"
# define EVENTEHT "eht"
# define EVENTEBO "ebo"
# define EVENTEDI "edi"
# define EVENTSGT "sgt"
# define EVENTSEG "seg"
# define EVENTSMG "smg"
# define EVENTSUC "suc"
# define EVENTSBP "sbp"

# include <sstream>

class NetworkManager
{
public:
	NetworkManager(Game *game);
	virtual ~NetworkManager();
	void initEvent();
	void initcmdList();
	std::string connecte(std::string addr);
	void fillBuffer(std::string bufferRead);
	bool runEngine(const std::string &command);
	static void update();
	bool SetSocketBlockingEnabled(int fd, bool blocking);
	void splitCmd(std::vector<std::string> &tokens,
		const std::string &text, char sep);
	int countArguments(const std::string &cmd) const;
	bool findCmd(const std::string &cmd, const std::string &cmdList) const;

	/*
	** Envents
	*/
	bool EventWelcome(const std::string &command);
	bool EventMsz(const std::string &command);
	bool EventBct(const std::string &command);
	bool EventTna(const std::string &command);
	bool EventPnw(const std::string &command);
	bool EventPpo(const std::string &command);
	bool EventPlv(const std::string &command);
	bool EventPin(const std::string &command);
	bool EventPex(const std::string &command);
	bool EventPbc(const std::string &command);
	bool EventPic(const std::string &command);
	bool EventPie(const std::string &command);
	bool EventPfk(const std::string &command);
	bool EventPdr(const std::string &command);
	bool EventPgt(const std::string &command);
	bool EventPdi(const std::string &command);
	bool EventEnw(const std::string &command);
	bool EventEht(const std::string &command);
	bool EventEbo(const std::string &command);
	bool EventEdi(const std::string &command);
	bool EventSgt(const std::string &command);
	bool EventSeg(const std::string &command);
	bool EventSmg(const std::string &command);
	bool EventSuc(const std::string &command);
	bool EventSbp(const std::string &command);
	//void setOnStart();
private:
	bool _isConnect;
	Game *_game;
	SOCKET _sock;
	std::string _bufferRead;
	int _pos;
	Sound _sound;
	InfoBulleChat *_chatCommand;

	/*
	** methodes pointer
	*/
	typedef bool (NetworkManager::*event_s)(const std::string &);
	std::map<std::string, event_s> _event;
	std::map<int, std::string> _cmdList;
	/*
	** instance
	*/
	static NetworkManager *_instance;
};

#endif