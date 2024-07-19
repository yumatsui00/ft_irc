
#include "../inc/all.hpp"
#include "../inc/irc.hpp"
#include "../inc/Server.hpp"

Server::Server(): Socket(5000){}
Server::Server(int port, char *pass): Socket(port){_password = pass;}
Server::~Server(){}


Channel*	Server::findChannel( std::string ch_name ) {
	for (std::set<Channel*>::iterator it = this->_Channels.begin(); it != _Channels.end(); it++) {
		if ((*it)->getChannelName() == ch_name)
			return (*it);
	}
	return NULL;
}

std::string	Server::getPassword( void ) {
	return _password;
}

std::set<Channel*>	Server::getChannels( void ) {
	return _Channels;
}

User*	Server::nick2User(std::string nick) {
	for (std::set<User*>::iterator it = this->_Users.begin(); it != this->_Users.end(); it++) {
		if ((*it)->getNickName() == nick)
			return (*it);
	}
	return NULL;
} ;

User*	Server::fd2User(int fd) {
	for(std::set<User*>::iterator it = this->_Users.begin(); it != this->_Users.end(); it++) {
		if ((*it)->getFd() == fd)
			return (*it);
	}
	//すべてのユーザーに必要なfdが割り当てられてるのでNULLにはならない
	return (NULL);
};


void	Server::addChannel( Channel *new_Ch ) {
	_Channels.insert(new_Ch);
} ;

void	Server::delChannel( Channel *channel ) {
	std::set<Channel*>::iterator it = _Channels.find(channel);
	if (it != _Channels.end()) {
		_Channels.erase(it);
		delete(channel);
	}

	//for (std::vector<Channel*>::iterator it = _Channels.begin(); it != _Channels.end(); it ++) {
	//	if (*it == channel) {
	//		_Channels.erase(it);
	//		delete(channel);
	//		break ;
	//	}
	//}
}