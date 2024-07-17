#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

#include "all.hpp"

class Privmsg : public Command {
private:
	Privmsg() {};
public:
	Privmsg( Command &src ) : Command( src ) {};
	~Privmsg() {};
	int	exec_privmsg( Server &server );
} ;

# endif