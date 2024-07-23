#include "Command.hpp"

int	Command::user( Server &server ) {
	//passwordをセット
	//if (_user->getpassok()) {
	//	//!消す
	//	return (999);
	//}
	if (_user->isRegistered())
		return (0); //すでにloginしてある
	if (_divCmd.size() != 5)
		return (461);
	if (!_user->getUserName().empty())
		return (462);
	_user->setUserName(_divCmd[1]);
	_user->setNickName(_divCmd[2]);
	if (this->proceedRegisration(server))
		regisration_message(server);
	return (0);
}
