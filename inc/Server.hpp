#ifndef SERVER_HPP
# define SERVER_HPP

#include "irc.hpp"
#include "Socket.hpp"
#include "User.hpp"
#include "Channel.hpp"

class User;
class Channel;
class Socket;

class Server : public Socket {
private:
	std::set<User*>		_Users;
	std::set<Channel*>	_Channels;
	std::string			_password;
	Server();
public:
	Server(int port, char *pass);
	~Server();

	std::string	getPassword( void );
	std::set<Channel*>	getChannels( void );
	User*		nick2User(std::string nick);
	Channel*	findChannel( std::string &ch_name );
	User*		fd2User(int fd);


	void		addChannel( Channel *new_Ch );
	void		delChannel( Channel *ch );

	//void		addUser(int fd);//kaz
	//void		delUser(int fd);//kaz

};

#endif