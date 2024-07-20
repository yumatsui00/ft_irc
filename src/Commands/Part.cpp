#include "Command.hpp"

int Command::part( Server &server ) {
	if (!(_divCmd.size() == 2 || _divCmd.size() == 3))
		return (461);
	Channel *channel = server.findChannel(_divCmd[1]);
	if (!channel)
		return (403);
	if (!channel->isExist(_user))
		return (442);

	std::string msg;
	msg = ": " + _user->getPrefix() + " PART " + _divCmd[1];
	if (_divCmd.size() == 2)
		msg += " :\n";
	else
		msg += " :" + _divCmd[2] + "\n";
	//ft_send()
	if (!channel->isMemberExist())
		server.delChannel(channel);
	return (0);
}