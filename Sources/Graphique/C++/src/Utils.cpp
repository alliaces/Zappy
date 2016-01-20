//
// Utils.cpp for Utils.cpp in /home/lelong_t/rendu/zappy_graphique/src
// 
// Made by Théophile
// Login   <lelong_t@epitech.net>
// 
// Started on  Wed May  6 14:12:18 2015 Théophile
// Last update Wed May  6 14:12:19 2015 Théophile
//

#include "Utils.hpp"

Utils::Utils()
{
}

Utils::~Utils()
{
}

int Utils::stringToInt(const std::string &str)
{
	int nb;

	std::istringstream(str) >> nb;
	return (nb);
}

std::string Utils::intToString(int nb)
{
	std::stringstream ss;
	std::string str("");

	ss << nb;
	str = ss.str();
	return (str);
}