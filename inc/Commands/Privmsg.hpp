#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

#include "all.hpp"
#include "Mode.hpp"

class Privmsg : public Mode {
private:
	Privmsg() {};
public:
	Privmsg( Command &src, Server &server ) : Mode( src, server ) {};
	~Privmsg() {};
	int	exec_privmsg( Server &server );
} ;

int	Privmsg::exec_privmsg( Server &server ) {
	if (_divCmd.size() != 3)
		return (461);

	std::string msg;
	msg = ":" + _user->getPrefix() + " PRIVMSG " + _divCmd[1] + " :" + _divCmd[2] + "\n";
	if (_channel) {
		//!ft_send(fd, msg); //fd = channelの皆さん
	} else {
		User* target = server.nick2User(_divCmd[1]);
		if (target == NULL)
			return (401);
		//!ft_send(fd, msg); //fd = targetの方
	}
	return (0);
}

# endif