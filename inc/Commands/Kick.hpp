#ifndef KICK_HPP
# define KICK_HPP

#include "all.hpp"
#include "Mode.hpp"

class Kick : public Mode {
public:
	Kick( Command &src, Server &server ) : Mode( src, server ) {};
	Kick() {};

	int		exec_kick( Server &server );
	void	KickMessanger( void );
} ;

int	Kick::exec_kick( Server &server ) {
	if (!(this->_divCmd.size() == 3 || this->_divCmd.size() == 4))
		return (461);
	if (!this->_channel)
		return (403);//channelが存在するか
	if (!_channel->isOperator(_user))
		return (482);//オペレータかつ存在するか
	User* kickedUser = _channel->nick2User(_divCmd[2]);
	if (!kickedUser)
		return (401);//キックされる人が存在するか
	KickMessanger();
	_channel->delMember(kickedUser);
	if (!_channel->isMemberExist()) {
		server.delChannel(_channel);
		_channel == NULL;
	} // 誰もいなくなったら消す
}

void	Kick::KickMessanger( void ) {
	std::string msg;

	msg = ":" + _user->getPrefix() + " KICK " + _divCmd[1] + " " + _divCmd[2] + " :";
	if (msg.size() == 3)
		msg += _user->getNickName() + "\n";
	else
		msg += _divCmd[3] + "\n";
	//ft_send(fd, msg);
	//fd グループの人全員
}

# endif