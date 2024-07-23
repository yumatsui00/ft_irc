#include "Command.hpp"

int	Command::ping( Server &server ) {
	std::string msg;
	msg = ":ft_irc PONG ft_irc :127.0.0.1\r\n";
	//!いるのいらないの
	server.ft_send(_user->getFd(), msg);
	return (0);
}