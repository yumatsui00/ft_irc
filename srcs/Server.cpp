#include "all.hpp"

Channel*	Server::findChannel( std::string ch_name ) {
	for (std::vector<Channel*>::iterator it = this->_Channels.begin(); it != _Channels.end(); it++) {
		if ((*it)->getChannelName() == ch_name)
			return (*it);
	}
	return NULL;
}

std::string	Server::getPassword( void ) {
	return _password;
}

std::vector<Channel*>	Server::getChannels( void ) {
	return _Channels;
}

User*	Server::nick2User(std::string nick) {
	for (std::vector<User*>::iterator it = this->_Users.begin(); it != this->_Users.end(); it++) {
		if ((*it)->getNickName() == nick)
			return (*it);
	}
	return NULL;
} ;

User*	Server::fd2User(int fd) {
	for(std::vector<User*>::iterator it = this->_Users.begin(); it != this->_Users.end(); it++) {
		if ((*it)->getFd() == fd)
			return (*it);
	}
	//すべてのユーザーに必要なfdが割り当てられてるのでNULLにはならない
	return (NULL);
};


void	Server::addChannel( Channel *new_Ch ) {
	_Channels.push_back(new_Ch);
} ;