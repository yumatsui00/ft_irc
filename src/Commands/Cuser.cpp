#include "Command.hpp"

int	Command::user( Server &server ) {
	if (!this->_user->getpassok()) {
		server.close_connection(_user->getFd());
		return (0);
	}
	if (_user->isRegistered())
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
