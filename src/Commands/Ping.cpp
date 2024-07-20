#include "Command.hpp"

int	Command::ping( Server &server ) {
	std::string msg;
	msg = ":ft_irc PONG ft_irc :127.0.0.1\r\n";
	//!ft_send();
	(void)server;
	return (0);
}