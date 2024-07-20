#include "Command.hpp"

int	Command::privmsg( Server &server ) {
	if (_divCmd.size() != 3)
		return 461;

	std::string msg;
	msg = ":" + _user->getPrefix() + " PRIVMSG " + _divCmd[1] + " :" + _divCmd[2] + "\n";
	Channel *channel = server.findChannel(_divCmd[1]);
	if (channel) {
		//!ft_send(fs, msg);//fd = channel のみなさん
	} else {
		User* target = server.nick2User(_divCmd[1]);
		if (target == NULL)
			return (401);
		//!ft_send fd = target
	}
	return (0);
}