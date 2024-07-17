#ifndef KICK_HPP
# define KICK_HPP

#include "all.hpp"

class Kick : public Command {
private:
	Kick() {};
public:
	Kick( Command &src ) : Command( src ) {};
	~Kick() {};
	int	exec_kick( Server &server );
} ;

# endif