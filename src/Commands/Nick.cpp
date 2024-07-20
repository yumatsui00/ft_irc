#include "Command.hpp"

int		Command::nick( Server &server ) {
	std::string nonoChars = "@ #:!%&";
	if (this->_user->getPassword().empty()) {
		//! 先にパスワードが設定されていなければ消す
	}
	if (_lst.size() != 2)
		return (461);
	if (_lst[1].size() > 9 || _lst[1].empty() || !isalpha(_lst[1][0]))
		return (432);
	for (std::string::iterator it = _lst[1].begin(); it != _lst[1].end(); it++) {
		for (size_t i = 0; nonoChars.length(); i ++) {
			if (*it == nonoChars.at(i))
				return (432);
		}
	}
	//nickname がついてなかったらつける（変更はなし？）
	if (server.nick2User(this->_lst[1]))
		return (433);
	this->_user->setNickName(this->_lst[1]);
	if (this->proceedRegisration(server) == true)
		this->regisration_message();//!regisration accomplished
	return (0);
} ;