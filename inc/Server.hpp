#ifndef SERVER_HPP
# define SERVER_HPP

#include "irc.hpp"
#include "Socket.hpp"

class	Socket;

class	Server:	public Socket
{
	protected:
		std::string	_password;
	public:
		Server();
		Server(int port, char *pass);
		std::string	getpassword();
};

#endif