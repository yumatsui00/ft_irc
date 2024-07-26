#include "irc.hpp"
#include "Server.hpp"

Server::Server(): Socket(5000){}
Server::Server(int port, char *pass): Socket(port){_password = pass;}
Server::~Server(){
	User *del;
	std::set<User*>::iterator it = _Users.begin();
	while (it != _Users.end()){
		del = *it;
		it ++;
		delete del;
	}
	Channel *tmp;
	std::set<Channel*>::iterator itc = _Channels.begin();
	while (itc != _Channels.end()){
		tmp = *itc;
		itc ++;
		delete tmp;
	}
}


std::string	Server::getPassword( void ) {
	return _password;
}

std::set<Channel*>	Server::getChannels( void ) {
	return _Channels;
}

Channel*	Server::findChannel( std::string &ch_name ) {
	for (std::set<Channel*>::iterator it = this->_Channels.begin(); it != _Channels.end(); it++) {
		if ((*it)->getChannelName() == ch_name)
			return (*it);
	}
	return NULL;
}

User*	Server::nick2User(std::string nick) {
	for (std::set<User*>::iterator it = this->_Users.begin(); it != this->_Users.end(); it++) {
		if ((*it)->getNickName() == nick)
			return (*it);
	}
	return NULL;
} ;

// User*	Server::fd2User(int fd) {
// 	for(std::set<User*>::iterator it = this->_Users.begin(); it != this->_Users.end(); it++) {
// 		if ((*it)->getFd() == fd)
// 			return (*it);
// 	}
// 	//すべてのユーザーに必要なfdが割り当てられてるのでNULLにはならない
// 	return (NULL);
// };


void	Server::addChannel( Channel *new_Ch ) {
	_Channels.insert(new_Ch);
} ;

void	Server::delChannel( Channel *channel ) {
	std::set<Channel*>::iterator it = _Channels.find(channel);
	if (it != _Channels.end()) {
		_Channels.erase(it);
		delete(channel);
	}
}

void	Server::ft_send(int fd, std::string mes){
	User* user = Socket::fd2User(fd);
	user->setMessage(mes);
	Socket::event_epollout(fd);
}

void	Server::del_user_all(int fd) {
	User* 		user = fd2User(fd);
	std::string	nick = user->getNickName();

	if (user == NULL)
		return ;
	for (std::set<Channel*>::iterator ch = _Channels.begin(); ch != _Channels.end(); ch++) {
		std::map<User*, bool> usrs = (*ch)->getUsers();
		for (std::map<User*, bool>::iterator usr = usrs.begin(); usr != usrs.end(); usr++) {
			if (user == usr->first)
				(*ch)->delMember(user);
		}
		std::set<std::string> invitelist = (*ch)->getInviteList();
		for (std::set<std::string>::iterator invite = invitelist.begin(); invite != invitelist.end(); invite++) {
			if (*invite == nick)
				(*ch)->delInvitingList(nick);
		}
	}
}
