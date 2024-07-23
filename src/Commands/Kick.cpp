#include "Command.hpp"
//done
int	Command::kick( Server &server ) {
	if (!(_divCmd.size() == 3 || _divCmd.size() == 4))
		return (461);
	Channel *channel = server.findChannel(_divCmd[1]);
	if (channel == NULL)
		return (403);
	if (!channel->isOperator(_user))
		return (482);
	User *kickedUser = channel->nick2User(_divCmd[2]);
	if (!kickedUser)
		return (401);
	KickMessanger(server, channel);
	channel->delMember(kickedUser);
	if (!channel->isMemberExist()) {
		server.delChannel(channel);
	}
	return (0);
}

void	Command::KickMessanger( Server &server, Channel *channel ) {
	std::string msg;

	msg = ":" + _user->getPrefix() + " KICK " + _divCmd[1] + " " + _divCmd[2] + " :";
	if (msg.size() == 3)
		msg += _user->getNickName() + "\n";
	else
		msg += _divCmd[3] + "\n";

	std::map<User*, bool> users = channel->getUsers();
	for (std::map<User*, bool>::iterator it = users.begin(); it != users.end(); it++) {
		server.ft_send(it->first->getFd(), msg);
	}
}