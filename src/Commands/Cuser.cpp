#include "Command.hpp"

int	Command::user( Server &server ) {
	if (_user->getPassword().empty()) {
		//!消す
		return (999);
	}
	if (_lst.size() != 5)
		return (461);
	if (!_user->getUserName().empty())
		return (462);
	_user->setUserName(_lst[1]);
	_user->setNickName(_lst[2]);
	if (this->proceedRegisration(server))
		regisration_message();
	return (0);
}
