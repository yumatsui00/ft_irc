#include "Command.hpp"

int		Command::nick( Server &server ) {
	char nonoChars[8] = "@ #:!%&";
	if (!this->_user->getpassok()) {
		close(_user->getFd());
		return (0);
	}
	if (_divCmd.size() != 2)
		return (461);
	if (_user->isRegistered())
		return (0);
	if (_divCmd[1].size() > 9 || _divCmd[1].empty() || !isalpha(_divCmd[1][0]))
		return (432);
	for (int i = 0; i < 7; i++) {
		char c = nonoChars[i];
		for (size_t j = 0; j < _divCmd[1].length(); j++) {
			if (_divCmd[1].at(j) == c)
				return (432);
		}
	}
	//nickname がついてなかったらつける（変更はなし？）
	if (server.nick2User(this->_divCmd[1]))
		return (433);
	this->_user->setNickName(this->_divCmd[1]);
	if (this->proceedRegisration(server) == true)
		this->regisration_message(server);//!regisration accomplished
	return (0);
} ;