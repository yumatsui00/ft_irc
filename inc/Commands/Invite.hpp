#ifndef INVITE_HPP
# define INVITE_HPP

#include "../all.hpp"

class Invite : public Command {
private:
	User*		_invitedUser;
	Channel*	_invitingCh;
public:
	Invite( Command &src ) : Command( src ) {};
	~Invite( void ) {};

	int		exec_invite( Server &server );
	void	inviteMessanger( void );
} ;

int	Invite::exec_invite( Server &server ) {
	if (this->_divCmd.size() != 3)
		return (461);// コマンドの数が違う
	_invitedUser = server.nick2User(_divCmd[1]);
	if (_invitedUser == NULL)
		return (401);//招待する日がサーバーに存在しない
	_invitingCh = server.findChannel(_divCmd[2]);
	if (_invitingCh == NULL)
		return (403);//!招待するチャンネルが存在しない。しかし、規約的には別に問題ない？要参照アンド相談
	if (!_invitingCh->isExist(_user))
		return (442);//招待者がそのチャンネルにいない
	if (_invitingCh->isExist(_invitedUser))
		return (443); //招待された人がすでにそのチャンネルにいる
	if (!_invitingCh->isOperator(_user))
		return (482); //招待者がオペレータじゃない
	_invitingCh->addInvitingList(_divCmd[1]);
	inviteMessanger();
	return (341);
}

void	Invite::inviteMessanger( void ) {
	std::string msg;
	msg = ":" + _user->getPrefix() + " INVITE " + _divCmd[1] + _divCmd[2] + '\n';
	//!ft_send(fd, msg)
	//fd = inviting group の人　＋　invitedUser
}



# endif