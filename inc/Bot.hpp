#ifndef BOT_HPP
# define BOT_HPP

# include "irc.hpp"

class Bot {
public:
	std::string	nickname = "ぼっと君";
	std::string	prefix = "ボット君";
	std::string	_msg;
}

#endif