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
			if (it->first != _user)
				server.ft_send(it->first->getFd(), msg);
		}
		janken( server, users );
	} else {
		User* target = server.nick2User(_divCmd[1]);
		if (target == NULL)
			return (401);
		server.ft_send(target->getFd(), msg);
	}
	return (0);
}

void	Command::janken( Server &server, std::map<User*, bool> users ) {
	std::string msg;
	if (_divCmd[2].find("じゃんけん") != std::string::npos) {
		if (_divCmd[2].find("グ") != std::string::npos || _divCmd[2].find("ぐ") != std::string::npos) {
			msg = ":じゃんけんbot君 PRIVMSG " + _divCmd[1] + " :じゃんけんパー！✋" + "\n";
		} else if (_divCmd[2].find("チ") != std::string::npos || _divCmd[2].find("ち") != std::string::npos) {
			msg = ":じゃんけんbot君 PRIVMSG " + _divCmd[1] + " :じゃんけんグー！👊" + "\n";
		} else if (_divCmd[2].find("パ") != std::string::npos || _divCmd[2].find("ぱ") != std::string::npos) {
			msg = ":じゃんけんbot君 PRIVMSG " + _divCmd[1] + " :じゃんけんチョキ！✌️" + "\n";
		} else {
			std::srand(std::time(0));
  	 	 	int result = std::rand() % 3;
			if (result == 0){
				msg = ":じゃんけんbot君 PRIVMSG " + _divCmd[1] + " :じゃんけんチョキ！✌️" + "\n";
			} else if (result == 1) {
				msg = ":じゃんけんbot君 PRIVMSG " + _divCmd[1] + " :じゃんけんグー！👊" + "\n";
			} else {
				msg = ":じゃんけんbot君 PRIVMSG " + _divCmd[1] + " :じゃんけんパー！✋" + "\n";
			}
		}
		for (std::map<User*, bool>::iterator it = users.begin(); it != users.end(); it++) {
			server.ft_send(it->first->getFd(), msg);
		}
	}
}