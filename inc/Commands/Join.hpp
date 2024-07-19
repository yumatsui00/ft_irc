#ifndef JOIN_HPP
# define JOIN_HPP

#include "../all.hpp"
#include "Mode.hpp"

class Join : public Mode {
public:
	Join( Command &src, Server &server ) : Mode( src, server ) {};
	~Join() {};

	int		exec_join( Server &server );
	int		creatChannel( Server &server );
	void	JoinMessanger( void );
} ;



int	Join::exec_join( Server &server ) {
	if (!(this->_divCmd.size() == 2 || this->_divCmd.size() == 3))
		return (461); //command check
	if (_channel == NULL) //channel が存在しなかったら作成する
		return (creatChannel(server));
	//!kazくんから大きく変更してるけど心配だ
	if (_channel->getMode(modeI) && !_channel->isInInvitingList(_user->getNickName()))
		return (473); //招待モードだけど、招待されてない
	if (_channel->getMode(modeK) && (_divCmd.size() == 2 || _channel->getPass() != _divCmd[2]))
		return (475); //ぱすわーどありだけど、引数の数、またはパスワードが異なる
	if (_channel->getMode(modeL) && _channel->getMaxusers() <= _channel->getUsersNum())
		return (471); //人数制限ありだけど、すでにオーバーしてる　
	if (_channel->isExist(_user))
		return (0);//すでにいたら、エラーメッセージも出さずに終了
	_channel->addMember(_user);

	JoinMessanger();
	return 0;
}

int	Join::creatChannel( Server &server ) {
	if (_divCmd[1][0] != '#')
		return 403;
	if (_divCmd[1].size() == 1)
		return 403;
	Channel *ch = new Channel(_divCmd[1], this->_user);
	server.addChannel(ch);
	this->_channel = ch;
	if (_divCmd.size() == 3 && !_divCmd[2].empty())
		modePassword(true, _divCmd[2]);

	JoinMessanger();
	return (0);
}

void	Join::JoinMessanger( void ) {
	std::string msg;

	msg = ":" + _user->getPrefix() + " JOIN :" + _divCmd[1] + "\n";
	if (!_channel->getTopic().empty()) {
		msg += ":ft_irc 332 " + _user->getNickName() + " " + _divCmd[1] + " :" + _channel->getTopic() + "\n";
	}
	msg += ":ft_irc 353 " + _user->getNickName() + " = " + _divCmd[1] + " :" + _channel->getUsersList() + "\n";
	msg += ":ft_irc 366 " + _user->getNickName() + " " + _divCmd[1] + " :End of NAMES list\n";
	//!ft_send(fd ,msg)
	//fd = Channelの全員
}

# endif