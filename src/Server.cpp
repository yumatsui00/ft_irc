#include "Webserv.hpp"
#include "Server.hpp"

Server::Server(const char * config): Socket(5000){
	(void)config;
}