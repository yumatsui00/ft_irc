#include "Command.hpp"

int	Command::user( Server &server ) {
	if (!this->_user->getpassok()) {
		close(_user->getFd());
		return (0);
	}
	std::cout << _user->isRegistered() << std::endl;
	if (_user->isRegistered())//ここバグってるよ
		return (0); //すでにloginしてある
	if (_divCmd.size() != 5)
		return (461);
	if (!_user->getUserName().empty())
		return (462);
	_user->setUserName(_divCmd[1]);
	if (this->proceedRegisration(server))
		regisration_message(server);
	return (0);
}
