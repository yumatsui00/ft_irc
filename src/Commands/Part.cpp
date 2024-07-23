#include "Command.hpp"
//done
int Command::part( Server &server ) {
	if (!(_divCmd.size() == 2 || _divCmd.size() == 3))
		return (461);
	Channel *channel = server.findChannel(_divCmd[1]);
	if (!channel)
		return (403);
	if (!channel->isExist(_user))
		return (442);

	std::string msg;
	msg = ":" + _user->getPrefix() + " PART " + _divCmd[1];
	if (_divCmd.size() == 2)
		msg += " :\n";
	else
		msg += " :" + _divCmd[2] + "\n";

	std::map<User*, bool> users = channel->getUsers();
	for (std::map<User*, bool>::iterator it = users.begin(); it != users.end(); it++) {
		server.ft_send(it->first->getFd(), msg);
	}

	channel->delMember(_user);
	if (!channel->isMemberExist())
		server.delChannel(channel);
	return (0);
}