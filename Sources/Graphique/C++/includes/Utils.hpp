//
// Utils.hpp for Utils.hpp in /home/lelong_t/rendu/zappy_graphique/includes
// 
// Made by Théophile
// Login   <lelong_t@epitech.net>
// 
// Started on  Wed May  6 14:13:19 2015 Théophile
// Last update Wed May  6 14:13:39 2015 Théophile
//

#ifndef		UTILS_HPP_
# define	UTILS_HPP_

# include <string>
# include <sstream>

class Utils
{
public:
	Utils();
	~Utils();
	static int stringToInt(const std::string &);
	static std::string intToString(int);
};

#endif
