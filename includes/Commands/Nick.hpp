#ifndef NICK_HPP
# define NICK_HP

#include "all.hpp"

class Nick : public Command {
private:
	std::string	_nonoChars = " @#:!%&";
	Nick() {};
public:
	Nick( Command &src ) : Command( src ) {};
	~Nick() {};
	int	exec_nick( Server &server );
} ;

int	Nick::exec_nick( Server &serv ) {
	if (this->_user->getPassword().empty()) {
		//! 先にパスワードが設定されていなければ消す
	}
	if (_lst.size() != 2)
		return (461);
	if (_lst[1].size() > 9 || _lst[1].empty() || !isalpha(_lst[1][0]))
		return (432);
	for (std::string::iterator it = _lst[1].begin(); it != _lst[1].end(); it++) {
		for (size_t i = 0; _nonoChars.length(); i ++) {
			if (*it == _nonoChars.at(i))
				return (432);
		}
	}
	//nickname がついてなかったらつける（変更はなし？）
	if (serv.nick2User(this->_lst[1]))
		return (433);
	this->_user->setNickName(this->_lst[1]);
	if (this->_user->proceedRegisration(serv) == true)
		this->regisration_message();//!regisration accomplished
	return (0);
} ;

# endif