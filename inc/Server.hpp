#ifndef SERVER_HPP
# define SERVER_HPP

#include "irc.hpp"
#include "Socket.hpp"

class User;
class Channel;
class Socket;

class Server : public Socket {
private:
	// std::set<User*>		_Users;
	//std::set<Channel*>	_Channels;
	std::string			_password;
	Server();
public:
	Server(int port, char *pass);
	~Server();

	std::string	getPassword( void );
	std::set<Channel*>	getChannels( void );
	std::string	user2nick( User* user );
	User*		nick2User(std::string nick);
	Channel*	findChannel( std::string &ch_name );

	void		addChannel( Channel *new_Ch );
	void		delChannel( Channel *ch );

	void	ft_send(int fd, std::string mes);
};

#endif