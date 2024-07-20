#include "Command.hpp"

int	Command::pass( Server &server ) {
	if (_lst.size() != 2)
		return (461);
	if (!_user->getPassword().empty())
		return (462);
	_user->setPassword(_lst[1]);
	if (proceedRegisration(server))
		regisration_message();
	//if ()//!今設定したパスワードと、サーバーのパスワードが違ったら
	//	//!消す
	return (0);
}