#include "all.hpp"

User*	Server::fd2User(int fd) {
	for(std::vector<User*>::iterator it = this->_Users.begin(); it != this->_Users.end(); it++) {
		if ((*it)->getFd() == fd)
			return (*it);
	}
	//すべてのユーザーに必要なfdが割り当てられてるのでNULLにはならない
	return (NULL);
};