#ifndef INVITE_HPP
# define INVITE_HPP

#include "all.hpp"

class Invite : public Command {
private:
	Invite() {};
public:
	Invite( Command &src ) : Command( src ) {};
	~Invite() {};
	int	exec_invite( Server &server );
} ;

# endif