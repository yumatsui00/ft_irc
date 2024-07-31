#include "Command.hpp"

int	Command::quit( Server &server ) {
	// server.close_connection(_user->getFd());
	// close (_user->getFd());
	return QUIT_NUM;
	(void)server;
} ;