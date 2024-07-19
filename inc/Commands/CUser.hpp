#ifndef CUSER_HPP
# define CUSER_HPP

#include "../all.hpp"

class CUser : public Command {
private:
	CUser( void ){};
public:
	CUser( Command &src ) : Command( src ) {};
	int	exec_user( Server &server );
} ;

int	CUser::exec_user( Server &serv ) {
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
	if (_user->proceedRegisration(serv))
		regisration_message();
	return (0);
} ;

#endif