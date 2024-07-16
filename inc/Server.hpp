#ifndef SERVER_HPP
# define SERVER_HPP

#include "irc.hpp"
#include "Socket.hpp"

class	Socket;

class	Server:	public Socket
{
	private:
		std::string	_password;
		Server();
	public:
		Server(int port, char *pass);
		~Server();
};

#endif