#include "Command.hpp"
//!
int		Command::join( Server &server ) {
	if (!(this->_divCmd.size() == 2 || this->_divCmd.size() == 3))
		return (461); //command check
	Channel	*target = server.findChannel(_divCmd[1]);
	if (target == NULL) //channel が存在しなかったら作成する
		return (creatChannel(server));
	return (joinChannel(server, target));
}

int		Command::creatChannel( Server &server ) {
	if (_divCmd[1][0] != '#')
		return 403;
	if (_divCmd[1].size() == 1)
		return 403;
	Channel *target = new Channel(_divCmd[1], this->_user);
	server.addChannel(target);
	if (_divCmd.size() == 3 && !_divCmd[2].empty()) {
		target->setMode(MODE_K, true);
		target->changePass(_divCmd[2]);
	}
	JoinMessanger(target, server);
	return (0);
}

int		Command::joinChannel( Server &server, Channel* channel ) {
	if ((channel->getMode(MODE_I)) && !channel->isInInvitingList(_user->getNickName()))
		return (473); //招待モードだけど、招待されてない
	if (channel->getMode(MODE_K) && (_divCmd.size() == 2 || channel->getPass() != _divCmd[2]))
		return (475); //ぱすわーどありだけど、引数の数、またはパスワードが異なる
	if (channel->getMode(MODE_L) && channel->getMaxusers() <= channel->getUsersNum())
		return (471); //人数制限ありだけど、すでにオーバーしてる　
	if (channel->isExist(_user))
		return (0);//すでにいたら、エラーメッセージも出さずに終了
	channel->addMember(_user);
	JoinMessanger(channel, server);
	return 0;
}

void	Command::JoinMessanger( Channel* channel, Server &server ) {
	std::string msg;

	msg = ":" + _user->getPrefix() + " JOIN :" + _divCmd[1] + "\n";
	if (!channel->getTopic().empty()) {
		msg += ":ft_irc 332 " + _user->getNickName() + " " + _divCmd[1] + " :" + channel->getTopic() + "\n";
	}
	msg += ":ft_irc 353 " + _user->getNickName() + " = " + _divCmd[1] + " :" + channel->getUsersList() + "\n";
	msg += ":ft_irc 366 " + _user->getNickName() + " " + _divCmd[1] + " :End of NAMES list\n";
	server.ft_send(_user->getFd(), msg);
	//msg = channel->bothello(); private msg 風に、　ボットクンカラコンニチハ
}
