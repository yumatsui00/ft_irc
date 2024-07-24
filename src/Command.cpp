#include "irc.hpp"
#include "Command.hpp"

class Server;

void	c( int status, std::vector<std::string> cmd ) {
	// std::cout << "\n -----check-----" << std::endl;
	// std::cout << "status = " << status << std::endl;
	// for (std::vector<std::string>::iterator it = cmd.begin(); it != cmd.end(); it ++) {
	// 	std::cout << (*it) << std::endl;
	// }
	// std::cout << "-------------" << std::endl;
	(void)status, (void)cmd;
}

Command::Command( Command &src )
:_user(src._user), _command(src._command), _divCmd(src._divCmd), _lst(src._lst){};


void	Command::exec_cmd(std::string &cmds, User *user , Server &serv) {
	this->_user = user;
	this->_lst.clear();

	//なぜか\rが入っているので消去
	std::size_t find;
	while ((find = cmds.find("\r")) != std::string::npos)
		cmds.erase(find, 1);

	//cmds改行があったらコマンド完成、なかったら未完成のため保存。改行があるかつ最後が改行じゃないのは仕様上同時に送られないらしい、、、ので対応不要
	find = cmds.find("\n");
	if (find == std::string::npos) {
		this->_user->add_cmd_strage(cmds);
		return ;
	} else {
		cmds.insert(0, this->_user->get_cmd_strage());
		this->_user->clear_cmd_strage();
	}

	//irssi は改行を復数同時に送れるが、最後が必ず改行になっている仕様
	//一度に複数のコマンド（改行）が送られてきたときのため_lstで分割して保存
	int	status;
	std::string buf;
	std::istringstream stream(cmds.c_str());
	while (std::getline(stream, buf))
		_lst.push_back(buf);
	for (std::vector<std::string>::iterator it = _lst.begin(); it != _lst.end(); it ++) {
		set_cmd(*it);
		status = exec(serv);
		if (status == 999)
			break ;
		printError(status, serv);
		c(status, _divCmd);
	}

	//ft_send(fd[0 ~ n], messeage);
} ;

void	Command::set_cmd(std::string &cmd) {
	this->_command = cmd;
	this->_divCmd.clear();

	if (!cmd.empty() && cmd[cmd.size() - 1] == '\n')
		cmd.erase(cmd.size() - 1);

	// : のあとは一単語として認識する
	std::string prefix, suffix;
	size_t semq_pos = cmd.find(":");
	if (semq_pos != std::string::npos) {
		prefix = cmd.substr(0, semq_pos);
		suffix = cmd.substr(semq_pos + 1, cmd.size());
	} else
		prefix = cmd;

	size_t found;
	while ((found = prefix.find("  ")) != std::string::npos)
		prefix.erase(found, 1);
	std::istringstream	stream(prefix.c_str());
	std::string			buf;
	while(std::getline(stream, buf, ' '))
		this->_divCmd.push_back(buf);
	if (suffix.size() != 0)
		this->_divCmd.push_back(suffix);
} ;


int	Command::exec( Server &serv ) {
	if (_divCmd.empty())
		return 0;
	else if (_divCmd[0] == "CAP")
		return 0;
	else if (_divCmd[0] == "WHO")
		return 0;
	else if (_divCmd[0] == "WHOIS")
		return 0;
	else if (_divCmd[0] == "NICK")
		return nick(serv);
	else if (_divCmd[0] == "USER")
		return user(serv);
	else if (_divCmd[0] == "PASS")
		return pass(serv);
	else if (_divCmd[0] == "QUIT")
		return quit(serv);
	else if (!_user->isRegistered())
		return (451);
	else if (_divCmd[0] == "INVITE")
		return invite(serv);
	else if (_divCmd[0] == "JOIN")
		return join(serv);
	else if (_divCmd[0] == "KICK")
		return kick(serv);
	else if (_divCmd[0] == "MODE")
		return mode(serv);
	else if (_divCmd[0] == "PART")
		return part(serv);
	else if (_divCmd[0] == "PING")
		return ping(serv);
	else if (_divCmd[0] == "PRIVMSG")
		return privmsg(serv);
	else if (_divCmd[0] == "TOPIC")
		return topic(serv);
	return (421);
} ;



bool	Command::proceedRegisration( Server &server ) {
	if (_user->isRegistered() == true)
		return false;
	if (!_user->getNickName().empty() && !_user->getUserName().empty() && _user->getpassok()) {
		_user->setIsRegistered(true);
		return true;
	}
	return false;
	(void)server;
}



void	Command::regisration_message( Server &server ) {
	std::string msg;
	msg = "001 " + _user->getNickName() + " :Welcome to the Internet Relay Network " + _user->getPrefix() + "\n" ;
	msg += "002 " + _user->getNickName() + " :Your host is ft_irc, running version 1.0\r\n";
	server.ft_send(_user->getFd(), msg);
}

void	Command::printError( int status, Server& server ) {
	if (status == 0)
		return ;

	std::ostringstream oss;
    oss << status;
	std::string msg = ":ft_irc " + oss.str() + " ";
	std::string nick = _user->getNickName();

	if (status == 401)
		msg += nick + " " + _divCmd[1] + " :No such nick/channel\n";
	else if (status == 403)
		msg += nick + " " + _divCmd[1] + " :No such channel\n";
	else if (status == 404)
		msg += _divCmd[1] + " :Cannot send to channel\n";
	else if (status == 421)
		msg += nick + " " + _divCmd[0] + " :Unknown command\n";
	else if (status == 432)
		msg += "* " + _divCmd[1] + " :Erroneous Nickname\n";
	else if (status == 433)
		msg += "* " + _divCmd[1] + " :Nickname is already in use\n";
	else if (status == 441)
		msg += nick + " " + _divCmd[1] + " :You're not on that channel\n";
	else if (status == 442)
		msg += nick + " " + _divCmd[1] + " :You're not on that channel\n";
	else if (status == 443)
		msg += nick + " " + _divCmd[1] + " :is already on channel\n";
	else if (status == 451)
		msg += ":Not registered\n";
	else if (status == 461)
		msg += nick + " " + _divCmd[0] + " :Syntax error\n";
	else if (status == 462)
		msg += " :You may not reregister\n";
	else if (status == 464)
	{
		if (nick.size() == 0)
			msg += "* :Password incorrect\n";
		else
			msg += nick + " :Password incorrect\n";
	}
	else if (status == 471)
		msg += nick + " " + _divCmd[1] + " :Cannot join channel (+l)\n";
	else if (status == 473)
		msg += nick + " " + _divCmd[1] + " :Cannot join channel (+i)\n";
	else if (status == 475)
		msg += nick + " " + _divCmd[1] + " :Cannot join channel (+k)\n";
	else if (status == 476)
		msg += _divCmd[1] + " :Bad Channel Mask\n";
	else if (status == 482)
		msg += nick + " " + _divCmd[1] + " :You're not channel operator\n";
	server.ft_send(_user->getFd(), msg);
}
