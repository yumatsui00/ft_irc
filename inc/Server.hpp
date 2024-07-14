#ifndef SERVER_HPP
# define SERVER_HPP

#include "Webserv.hpp"
#include "Socket.hpp"

class	Socket;

class	Server:	public Socket
{
	private:
	public:
		Server(const char * config);

};

#endif