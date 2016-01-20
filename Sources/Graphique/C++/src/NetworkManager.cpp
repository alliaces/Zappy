#include "NetworkManager.h"
#include "Game.h"

#ifdef WIN32
#include <io.h>

#endif

NetworkManager *NetworkManager::_instance;

NetworkManager::NetworkManager(Game *game)
{
	this->_isConnect = false;
#ifdef WIN32
	WSADATA wsa;
	int err = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (err < 0)
	{
		puts("WSAStartup failed !");
		exit(EXIT_FAILURE);
	}
#endif
	this->_game = game;
	this->_sock = socket(AF_INET, SOCK_STREAM, 0);
	SetSocketBlockingEnabled(this->_sock, false);
	this->_pos = 0;
	struct timeval timeout;
	timeout.tv_sec = 3;
	timeout.tv_usec = 0;
	setsockopt(_sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
	setsockopt(_sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));
	initEvent();
	initcmdList();
	this->_chatCommand = new InfoBulleChat;
	this->_sound.soundInit();
	this->_sound.loadSong(MAIN_SOUND);
	this->_sound.loadSong(BATTLE_SOUND);
	this->_sound.loadSong(CLICK_SOUND);
	this->_sound.loadSong(WALK_SOUND);
	this->_sound.loadSong(DEATH_PLAYER_SOUND);
	this->_sound.loadSong(EXPULSE_SOUND);
	this->_sound.playSound(MAIN_SOUND, true);
	NetworkManager::_instance = this;
}

void NetworkManager::initcmdList()
{
	this->_cmdList[0] = EVENTWELCOME;
	this->_cmdList[1] = EVENTMSZ;
	this->_cmdList[2] = EVENTBCT;
	this->_cmdList[3] = EVENTTNA;
	this->_cmdList[4] = EVENTPNW;
	this->_cmdList[5] = EVENTPPO;
	this->_cmdList[6] = EVENTPLV;
	this->_cmdList[7] = EVENTPIN;
	this->_cmdList[8] = EVENTPEX;
	this->_cmdList[9] = EVENTPBC;
	this->_cmdList[10] = EVENTPIC;
	this->_cmdList[11] = EVENTPIE;
	this->_cmdList[12] = EVENTPFK;
	this->_cmdList[13] = EVENTPDR;
	this->_cmdList[14] = EVENTPGT;
	this->_cmdList[15] = EVENTPDI;
	this->_cmdList[16] = EVENTENW;
	this->_cmdList[17] = EVENTEHT;
	this->_cmdList[18] = EVENTEBO;
	this->_cmdList[19] = EVENTEDI;
	this->_cmdList[20] = EVENTSGT;
	this->_cmdList[21] = EVENTSEG;
	this->_cmdList[22] = EVENTSMG;
	this->_cmdList[23] = EVENTSUC;
	this->_cmdList[24] = EVENTSBP;
}

void NetworkManager::initEvent()
{
	this->_event[EVENTWELCOME] = &NetworkManager::EventWelcome;
	this->_event[EVENTMSZ] = &NetworkManager::EventMsz;
	this->_event[EVENTBCT] = &NetworkManager::EventBct;
	this->_event[EVENTTNA] = &NetworkManager::EventTna;
	this->_event[EVENTPNW] = &NetworkManager::EventPnw;
	this->_event[EVENTPPO] = &NetworkManager::EventPpo;
	this->_event[EVENTPLV] = &NetworkManager::EventPlv;
	this->_event[EVENTPIN] = &NetworkManager::EventPin;
	this->_event[EVENTPEX] = &NetworkManager::EventPex;
	this->_event[EVENTPBC] = &NetworkManager::EventPbc;
	this->_event[EVENTPIC] = &NetworkManager::EventPic;
	this->_event[EVENTPIE] = &NetworkManager::EventPie;
	this->_event[EVENTPFK] = &NetworkManager::EventPfk;
	this->_event[EVENTPDR] = &NetworkManager::EventPdr;
	this->_event[EVENTPGT] = &NetworkManager::EventPgt;
	this->_event[EVENTPDI] = &NetworkManager::EventPdi;
	this->_event[EVENTENW] = &NetworkManager::EventEnw;
	this->_event[EVENTEHT] = &NetworkManager::EventEht;
	this->_event[EVENTEBO] = &NetworkManager::EventEbo;
	this->_event[EVENTEDI] = &NetworkManager::EventEdi;
	this->_event[EVENTSGT] = &NetworkManager::EventSgt;
	this->_event[EVENTSEG] = &NetworkManager::EventSeg;
	this->_event[EVENTSMG] = &NetworkManager::EventSmg;
	this->_event[EVENTSUC] = &NetworkManager::EventSuc;
	this->_event[EVENTSBP] = &NetworkManager::EventSbp;
}

bool NetworkManager::SetSocketBlockingEnabled(int fd, bool blocking)
{
	if (fd < 0) return false;

#ifdef WIN32
	unsigned long mode = blocking ? 0 : 1;
	return (ioctlsocket(fd, FIONBIO, &mode) == 0) ? true : false;
#else
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags < 0) return false;
	flags = blocking ? (flags&~O_NONBLOCK) : (flags | O_NONBLOCK);
	return (fcntl(fd, F_SETFL, flags) == 0) ? true : false;
#endif
}

NetworkManager::~NetworkManager()
{
#ifdef WIN32
	WSACleanup();
#endif
	delete this->_chatCommand;
	this->_sound.deleteSound(CLICK_SOUND);
	this->_sound.deleteSound(WALK_SOUND);
	this->_sound.deleteSound(BATTLE_SOUND);
	this->_sound.deleteSound(DEATH_PLAYER_SOUND);
	this->_sound.deleteSound(EXPULSE_SOUND);
}

std::string NetworkManager::connecte(std::string addr)
{
	struct hostent	*host;
	SOCKADDR_IN		sin;

    try
    {
		if (NetworkManager::_instance->_sock == -1)
			return ("Fatal Error.");
		if (strstr(addr.c_str(), ":") != NULL)
		{
			host = gethostbyname(strtok((char *)addr.c_str(), ":"));
			sin.sin_port = htons(atoi(strtok(NULL, ":")));
		}
		else
		{
			host = gethostbyname((char *)addr.c_str());
			sin.sin_port = htons(DEF_PORT);
		}
		if (host == NULL)
			return ("Unknow host.");
		sin.sin_addr = *(IN_ADDR *)(host)->h_addr;
		sin.sin_family = AF_INET;
		if (connect(NetworkManager::_instance->_sock, (SOCKADDR *)&sin, sizeof(SOCKADDR)) == -1)
			return ("Connexion impossible.");
		NetworkManager::_instance->_isConnect = true;
		NetworkManager::_instance->_sound.pauseSound(MAIN_SOUND);
		NetworkManager::_instance->_sound.deleteSound(MAIN_SOUND);
		NetworkManager::_instance->_sound.playSound(CLICK_SOUND, false);
		NetworkManager::_instance->_sound.pauseSound(CLICK_SOUND);
		NetworkManager::_instance->_sound.playSound(BATTLE_SOUND, true);
    }
    catch (std::exception& e)
    {
    	return (e.what());
	}
	return("");
}

void NetworkManager::fillBuffer(std::string buffRead)
{
	int y(0);

	while (buffRead[y] != '\0')
	{
		this->_bufferRead.push_back(buffRead[y]);
		this->_pos++;
		y++;
	}
}

void NetworkManager::update()
{
	int len(0);
	size_t n(0);
	char buffRead[512];

		try
   	 {
			if (NetworkManager::_instance->_isConnect)
			{
				len = read(NetworkManager::_instance->_sock, buffRead, 511);
				if (len == -1)
					buffRead[0] = '\0';
				else
					buffRead[len] = '\0';
				NetworkManager::_instance->fillBuffer(buffRead);
				if ((n = NetworkManager::_instance->_bufferRead.find("\n")) != std::string::npos)
				{
					std::string str(NetworkManager::_instance->_bufferRead);
					str.erase(n + 1, str.length());
					NetworkManager::_instance->runEngine(str);
					NetworkManager::_instance->_bufferRead.erase(0, n + 1);
				}
			}
		}
		catch (std::exception& e)
		{
			NetworkManager::_instance->_game->OnError(e.what());
		}
}

bool NetworkManager::runEngine(const std::string &command)
{
	int i(0);

	while (i < NBCMD)
	{
		if (findCmd(command, this->_cmdList[i]) == true && this->_cmdList[i] != "msz")
		{
			(this->*_event[this->_cmdList[i]])(command);
			return (true);
		}
		if (findCmd(command, this->_cmdList[i]) == true && this->_cmdList[i] == "msz")
		{
			int x(0);
			int y(0);
			std::vector<std::string> argCmd;

			if (countArguments(command) != 2)
			{
				Ogre::LogManager::getSingletonPtr()->logMessage("[MSZ] Bad nb args");
				return (false);
			}
			splitCmd(argCmd, command, ' ');
			x = Utils::stringToInt(argCmd[1]);
			y = Utils::stringToInt(argCmd[2]);
			this->_game->createMap(x, y);
//			Ogre::LogManager::getSingletonPtr()->logMessage("[EventMsz] done");
			return (true);
		}
		i++;
	}
	return (true);
}

/*
** split
*/
void NetworkManager::splitCmd(std::vector<std::string> &cmdArg,
	const std::string &cmd, char sep)
{
  int start(0);
  int end(0);

  while (( end = cmd.find(sep, start)) != std::string::npos)
  {
    cmdArg.push_back(cmd.substr(start, end - start));
    start = end + 1;
  }
  cmdArg.push_back(cmd.substr(start));
}

/*
** find command
*/
bool NetworkManager::findCmd(const std::string &cmd,
	const std::string &cmdList) const
{
	size_t i(0);

	while (cmd[i] == cmdList[i] &&
		i < cmdList.size() &&
		cmdList[i] != ' ' &&
		cmdList[i] != '\n')
		i++;
	if (cmd[i] == ' ' || cmd[i] == '\n')
		return (true);
	return (false);
}

/*
** count arguments
*/
int NetworkManager::countArguments(const std::string &cmd) const
{
	int size(0);
	int i(0);

	while ((size_t) i < cmd.size())
	{
		if (cmd[i] == ' ')
			size++;
		i++;
	}
	return (size);
}

/*
** Event
*/

bool NetworkManager::EventWelcome(const std::string &command)
{
	(void) command;
	write(_sock, "GRAPHIC\n", strlen("GRAPHIC\n"));
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventWelcome] GRAPHIC send");
	return (true);
}

bool NetworkManager::EventMsz(const std::string &command)
{
	int x(0);
	int y(0);
	std::vector<std::string> argCmd;

	if (countArguments(command) != 2)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[MSZ] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	x = Utils::stringToInt(argCmd[1]);
	y = Utils::stringToInt(argCmd[2]);
//	this->_game->createMap(x, y);
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventMsz] done");
	return (true);
}

bool NetworkManager::EventBct(const std::string &command)
{
	std::vector<std::string> argCmd;
	std::vector<int> listArgInt;
	int x(0);
	int y(0);
	int i(3);

	if (countArguments(command) != 9)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[BCT] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	x = Utils::stringToInt(argCmd[1]);
	y = Utils::stringToInt(argCmd[2]);
	while ((size_t) i < argCmd.size())
	{
		listArgInt.push_back(Utils::stringToInt(argCmd[i]));
		i++;
	}
	this->_game->fillMap(x, y, listArgInt);
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventBct] done");
	return (true);
}

bool NetworkManager::EventTna(const std::string &command)
{
	std::vector<std::string> argCmd;

	if (countArguments(command) != 1)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[TNA] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	this->_game->createTeam(argCmd[1]);
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventTna] done");
	return (true);
}

bool NetworkManager::EventPnw(const std::string &command)
{
	std::vector<std::string> argCmd;
	int i(1);

	if (countArguments(command) != 6)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[PNW] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	this->_game->createPlayer(Utils::stringToInt(argCmd[1]),
		Utils::stringToInt(argCmd[2]),
		Utils::stringToInt(argCmd[3]),
		Utils::stringToInt(argCmd[4]),
		Utils::stringToInt(argCmd[5]),
		argCmd[6]);
	return (true);
}

bool NetworkManager::EventPpo(const std::string &command)
{
	std::vector<std::string> argCmd;
	int i(1);

	if (countArguments(command) != 4)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[PPO] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
//	this->_sound.playSound(WALK_SOUND, false);
	this->_game->movePlayer(Utils::stringToInt(argCmd[1]),
		Utils::stringToInt(argCmd[2]),
		Utils::stringToInt(argCmd[3]),
		Utils::stringToInt(argCmd[4]));
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventPpo] done");
	return (true);
}

bool NetworkManager::EventPlv(const std::string &command)
{
	std::vector<std::string> argCmd;

	if (countArguments(command) != 2)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[PLV] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	this->_game->levelUp(Utils::stringToInt(argCmd[1]),
		Utils::stringToInt(argCmd[2]));
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventPlv] done");
	return (true);
}

bool NetworkManager::EventPin(const std::string &command)
{
	std::vector<std::string> argCmd;
	std::vector<int> listArgInt;
	int id(0);
	int x(0);
	int y(0);
	int i(4);

	if (countArguments(command) != 10)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[PIN] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	id = Utils::stringToInt(argCmd[1]);
	x = Utils::stringToInt(argCmd[2]);
	y = Utils::stringToInt(argCmd[3]);
	while ((size_t) i < argCmd.size())
	{
		listArgInt.push_back(Utils::stringToInt(argCmd[i]));
		i++;
	}
	this->_game->updateInventoryPlayer(id, x, y, listArgInt);
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventPin] done");
	return (true);
}

bool NetworkManager::EventPex(const std::string &command)
{
	std::vector<std::string> argCmd;

	if (countArguments(command) != 1)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[PEX] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	this->_sound.playSound(EXPULSE_SOUND, false);
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventPex] done");
	return (true);
}

bool NetworkManager::EventPbc(const std::string &command)
{
	std::vector<std::string> argCmd;

	if (countArguments(command) < 1)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[PBC] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	this->_chatCommand->createMsg((std::string) "[Broadcast] From player " + argCmd[1], 0, 0, 1.0f);
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventPbc] done");
	return (true);
}

bool NetworkManager::EventPic(const std::string &command)
{
	std::vector<std::string> argCmd;
	int i(1);

	if (countArguments(command) < 4)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[PIC] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	this->_game->createIncantation(Utils::stringToInt(argCmd[1]),
		Utils::stringToInt(argCmd[2]),
		Utils::stringToInt(argCmd[3]),
		Utils::stringToInt(argCmd[4]));
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventPic] done");
	return (true);
}

bool NetworkManager::EventPie(const std::string &command)
{
	std::vector<std::string> argCmd;
	int i(1);

	if (countArguments(command) != 3)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[PIE] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	this->_game->deleteIncantation(Utils::stringToInt(argCmd[1]),
		Utils::stringToInt(argCmd[2]),
		Utils::stringToInt(argCmd[3]));
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventPie] done");
	return (true);
}

bool NetworkManager::EventPfk(const std::string &command)
{
	std::vector<std::string> argCmd;

	if (countArguments(command) != 1)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[PFK] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	this->_game->createEgg(Utils::stringToInt(argCmd[1]));
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventPfk] done");
	return (true);
}

bool NetworkManager::EventPdr(const std::string &command)
{
	std::vector<std::string> argCmd;

	if (countArguments(command) != 2)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[PDR] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	this->_game->drop(Utils::stringToInt(argCmd[1]));
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventPdr] done");
	return (true);
}

bool NetworkManager::EventPgt(const std::string &command)
{
	std::vector<std::string> argCmd;

	if (countArguments(command) != 2)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[PGT] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	this->_game->take(Utils::stringToInt(argCmd[1]));
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventPgt] done");
	return (true);
}

bool NetworkManager::EventPdi(const std::string &command)
{
	std::vector<std::string> argCmd;

	if (countArguments(command) != 1)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[PDI] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	this->_sound.playSound(DEATH_PLAYER_SOUND, false);
	this->_game->dead(Utils::stringToInt(argCmd[1]));
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventPdi] done");
	return (true);
}

bool NetworkManager::EventEnw(const std::string &command)
{
	std::vector<std::string> argCmd;

	if (countArguments(command) != 4)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[ENW] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	this->_game->eggEndFork(Utils::stringToInt(argCmd[1]),
		Utils::stringToInt(argCmd[2]),
		Utils::stringToInt(argCmd[3]),
		Utils::stringToInt(argCmd[4]));
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventEnw] done");
	return (true);
}

bool NetworkManager::EventEht(const std::string &command)
{
	std::vector<std::string> argCmd;

	if (countArguments(command) != 1)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[EHT] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	this->_game->deleteEgg(Utils::stringToInt(argCmd[1]));
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventEht] done");
	return (true);
}

bool NetworkManager::EventEbo(const std::string &command)
{
	std::vector<std::string> argCmd;

	if (countArguments(command) != 1)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[EBO] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventEbo] done");
	return (true);
}

bool NetworkManager::EventEdi(const std::string &command)
{
	std::vector<std::string> argCmd;

	if (countArguments(command) != 1)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[EDI] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventEdi] done");
	return (true);
}

bool NetworkManager::EventSgt(const std::string &command)
{
	std::vector<std::string> argCmd;

	if (countArguments(command) != 1)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[SGT] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	this->_game->setSpeedAnim(Utils::stringToInt(argCmd[1]));
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventSgt] done");
	return (true);
}

bool NetworkManager::EventSeg(const std::string &command)
{
	std::vector<std::string> argCmd;

	if (countArguments(command) != 1)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[SEG] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');

	Text *textWin = new Text;

	textWin->setText((std::string) "Winner : " + argCmd[1], 0.1f);
	textWin->setPos(0.2f, 0.2f);
	textWin->setCol(1.0f, 0.84f, 0, 1.0f);
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventSeg] done");
	return (true);
}

bool NetworkManager::EventSmg(const std::string &command)
{
	std::vector<std::string> argCmd;

	if (countArguments(command) != 1)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[SMG] Bad nb args");
		return (false);
	}
	splitCmd(argCmd, command, ' ');
	this->_chatCommand->createMsg((std::string) "[Server msg] : " + argCmd[1], 1.0f, 0, 0);
//	Ogre::LogManager::getSingletonPtr()->logMessage("[EventSmg] done");
	return (true);
}

bool NetworkManager::EventSuc(const std::string &command)
{
	(void) command;
	return (true);
}

bool NetworkManager::EventSbp(const std::string &command)
{
	(void) command;
	return (true);
}
