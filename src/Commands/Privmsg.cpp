#include "Command.hpp"

int	Command::privmsg( Server &server ) {
	if (_divCmd.size() != 3)
		return 461;

	std::string msg;
	msg = ":" + _user->getPrefix() + " PRIVMSG " + _divCmd[1] + " :" + _divCmd[2] + "\n";
	Channel *channel = server.findChannel(_divCmd[1]);
	if (channel) {
		std::map<User*, bool> users = channel->getUsers();
		for (std::map<User*, bool>::iterator it = users.begin(); it != users.end(); it++) {
			server.ft_send(it->first->getFd(), msg);
		}
		if (_divCmd[2] == "じゃんけんグー") {
			msg = ":じゃんけんbot君 PRIVMSG " + _divCmd[1] + " :じゃんけんパー！✋" + "\n";
			for (std::map<User*, bool>::iterator it = users.begin(); it != users.end(); it++) {
				server.ft_send(it->first->getFd(), msg);
			}
		} else if (_divCmd[2] == "じゃんけんチョキ") {
			msg = ":じゃんけんbot君 PRIVMSG " + _divCmd[1] + " :じゃんけんグー！👊" + "\n";
			for (std::map<User*, bool>::iterator it = users.begin(); it != users.end(); it++) {
				server.ft_send(it->first->getFd(), msg);
			}
		} else if (_divCmd[2] == "じゃんけんパー") {
			msg = ":じゃんけんbot君 PRIVMSG " + _divCmd[1] + " :じゃんけんチョキ！✌️✋" + "\n";
			for (std::map<User*, bool>::iterator it = users.begin(); it != users.end(); it++) {
				server.ft_send(it->first->getFd(), msg);
			}
		} 
	} else {
		User* target = server.nick2User(_divCmd[1]);
		if (target == NULL)
			return (401);
		server.ft_send(target->getFd(), msg);
	}
	return (0);
}