#ifndef SERVER_HPP
# define SERVER_HPP

#include "all.hpp"

class Server {
private:
	std::vector<User*>		_Users;
	std::vector<Channel*>	_Channels;
	std::string				_pass;
public:
	Server();
	~Server();
	User*	fd2User(int fd);
	void	addUser(int fd);//kaz
	void	delUser(int fd);//kaz

};

#endif