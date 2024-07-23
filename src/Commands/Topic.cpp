#include "Command.hpp"

int	Command::topic( Server &server ) {
	if (!(_divCmd.size() == 2 || _divCmd.size() == 3))
		return (461);
	Channel *channel = server.findChannel(_divCmd[1]);
	if (channel == NULL)
		return (403);
	if (!channel->isExist(_user))
		return (442);//そのチャンネルにいなかったら☓
	if (_divCmd.size() == 2)
		return (TopicMessanger(channel, server, false));
	if (channel->getMode(MODE_T))
		return (482); //topic 変更が制限されてたらだめ
	if (!channel->isOperator(_user))
		return (482); //operatorじゃなかったら //! 諸説
	channel->setTopic(_divCmd[2]);
	return (TopicMessanger(channel, server, true));
}

int	Command::TopicMessanger( Channel *channel, Server &server, bool set ) {
	std::string msg;

	if (set == false) {
		if (channel->getTopic().empty())
			msg = ":ft_irc 331 " + _user->getNickName() + " " + _divCmd[1] + " :No topic is set\n";
		else
			msg = ":ft_irc 332 " + _user->getNickName() + " " + _divCmd[1] + " :" + channel->getTopic() + "\n";
		server.ft_send(_user->getFd(), msg);
	} else {
		msg = ":" + _user->getPrefix() + " TOPIC " + _divCmd[1] + " :" + _divCmd[2] + "\n";
		std::map<User*, bool> users = channel->getUsers();
		for (std::map<User*, bool>::iterator it = users.begin(); it != users.end(); it++) {
			server.ft_send(it->first->getFd(), msg);
		}
	}
	return (0);
}

//!諸説の部分。４８２のエラー分についても諸説あり。