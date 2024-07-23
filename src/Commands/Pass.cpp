#include "Command.hpp"

int	Command::pass( Server &server ) {
	if (_user->isRegistered())
		return (0);
	if (_divCmd.size() != 2)
		return (461);
	if (_divCmd[1].empty())
		return (462);
	if (_divCmd[1] == server.getPassword())
		_user->setPassok( true );
	else
		//!userを消す
	if (proceedRegisration(server))
		regisration_message(server);
	return (0);
}