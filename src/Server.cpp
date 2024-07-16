#include "irc.hpp"
#include "Server.hpp"

Server::Server(): Socket(5000){}
Server::Server(int port, char *pass): Socket(port){_password = pass;}
