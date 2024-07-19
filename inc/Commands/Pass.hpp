#ifndef PASS_HPP
# define PASS_HPP

# include "../all.hpp"

class Pass : public Command {
private:
	Pass() {};
public:
	Pass( Command &src ) : Command( src ) {};
	~Pass() {};
	int	exec_pass( Server &server );
} ;

int	Pass::exec_pass( Server &serv ){
	if (_lst.size() != 2)
		return (461);
	if (!_user->getPassword().empty())
		return (462);
	_user->setPassword(_lst[1]);
	if (_user->proceedRegisration(serv))
		regisration_message();
	//if ()//!今設定したパスワードと、サーバーのパスワードが違ったら
	//	//!消す
	return (0);
};

#endif