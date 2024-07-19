#ifndef PING_HPP
# define PING_HPP

#include "../all.hpp"

class Ping : public Command {
private:
	Ping(){};
public:
	Ping( Command &src ) : Command( src ) {};
	~Ping(){};
	int	exec_ping( void );
} ;

int		Ping::exec_ping( void ) {
	std::string msg;
	msg = ":ft_irc PONG ft_irc :127.0.0.1\r\n";
	//!ft_send();
	return (0);
}

# endif