#include "Command.hpp"

int		Command::nick( Server &server ) {
	std::string nonoChars = "@ #:!%&";
	if (!this->_user->getpassok()) {
		//! 先にパスワードが設定されていなければ消す
	}
	if (_divCmd.size() != 2)
		return (461);
	if (_divCmd[1].size() > 9 || _divCmd[1].empty() || !isalpha(_divCmd[1][0]))
		return (432);
	for (std::string::iterator it = _divCmd[1].begin(); it != _divCmd[1].end(); it++) {
		for (size_t i = 0; nonoChars.length(); i ++) {
			if (*it == nonoChars.at(i))
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