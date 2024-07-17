#ifndef PING_HPP
# define PING_HPP

#include "all.hpp"

class Ping : public Command {
private:
	Ping(){};
public:
	Ping( Command &src ) : Command( src ) {};
	~Ping(){};
	int	exec_ping( Server &server );
} ;

# endif