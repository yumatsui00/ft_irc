#include "Command.hpp"

int	Command::invite( Server &server ) {
	if (this->_divCmd.size() != 3)
		return (461);
	User* invitedUser = server.nick2User(_divCmd[1]);
	if (invitedUser == NULL)
		return (401); //招待する人がいない
	Channel *invitingCh = server.findChannel(_divCmd[2]);
	if (invitingCh == NULL)
		return (403); //!招待するチャンネルが存在しない、しかし規約的には問題ない？
	if (!invitingCh->isExist(_user))
		return (442); //招待者がそのチャンネルにいない
	if (!invitingCh->isOperator(_user))
		return (482);
	if (invitingCh->isExist(invitedUser))
		return (443);
	invitingCh->addInvitingList(_divCmd[1]);
	InviteMessanger(server, invitedUser->getFd());
	return (0);
}

void	Command::InviteMessanger( Server &server, int invitedFd ) {
	std::string	msg;

	msg = ":" + _user->getPrefix() + " INVITE " + _divCmd[1] + " " + _divCmd[2] + '\n';
	server.ft_send(invitedFd, msg);
	msg = ":ft_irc 341 " + _user->getNickName() + " " + _divCmd[2] + " :" + _divCmd[1] + "\n";
	server.ft_send(_user->getFd(), msg);
}
