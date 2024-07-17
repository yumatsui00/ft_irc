#include "all.hpp"

Command::Command( Command &src ) \
	:_user(src.getUser()), _command(src.getCmd()),\
	_divCmd(src.getDivCmd()), _lst(src.getLst()) {};


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
	std::vector<std::string>::iterator it = _lst.begin();
	for (std::vector<std::string>::iterator it = _lst.begin(); it != _lst.end(); it ++) {
		set_cmd(*it);
		status = exec(serv);
		if (status == 999)
			break ;
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
		suffix = cmd.substr(semq_pos, cmd.size());
	} else
		suffix = cmd;

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
	else if (_divCmd[0] == "NICK")
		return select_nick(serv);
	else if (_divCmd[0] == "USER")
		return select_user(serv);
	else if (_divCmd[0] == "PASS")
		return select_pass(serv);
	else if (_divCmd[0] == "QUIT")
		return select_quit(serv);
	else if (_divCmd[0] == "WHO")
		return select_who(serv);
	else if (_divCmd[0] == "WHOIS")
		return select_whois(serv);
	else if (!_user->isRegistered())
		return (451);
	else if (_divCmd[0] == "JOIN")
		return select_join(serv);
	else if (_divCmd[0] == "PART")
		return select_part(serv);
	else if (_divCmd[0] == "PRIVMSG")
		return select_privmsg(serv);
	else if (_divCmd[0] == "KICK")
		return select_kick(serv);
	else if (_divCmd[0] == "INVITE")
		return select_invite(serv);
	else if (_divCmd[0] == "MODE")
		return select_mode(serv);
	else if (_divCmd[0] == "TOPIC")
		return select_topic(serv);
	else if (_divCmd[0] == "PING")
		return select_ping(serv);
	return (421);
} ;









//getters
User*		Command::getUser( void ) const {
	return this->_user;
} ;

std::string Command::getCmd( void ) const {
	return this->_command;
} ;

std::vector<std::string>	Command::getDivCmd( void ) const {
	return this->_divCmd;
} ;

std::vector<std::string>	Command::getLst( void ) const {
	return this->_lst;
} ;



//exec_select

int	Command::select_nick( Server &serv ) {
	Nick nick( *this );
	return nick.exec_nick( serv );
} ;

int	Command::select_user( Server &serv ) {
	CUser cuser( *this );
	return cuser.exec_user( serv );
} ;

int	Command::select_pass( Server &serv ) {
	Pass pass( *this );
	return pass.exec_pass( serv );
} ;


int	Command::select_invite( Server &serv ) {
	Invite	invite( *this );
	return  invite.exec_invite( serv );
} ;

int	Command::select_join( Server &serv ) {
	Join join( *this, serv );
	return join.exec_join(serv);
}

//int	Command::select_kick( Server &serv ) {

//	return 
//}

//int	Command::select_mode( Server &serv ) {

//	return 
//}

//int	Command::select_part( Server &serv ) {

//	return 
//}

//int	Command::select_ping( Server &serv ) {

//	return 
//}

//int	Command::select_privmsg( Server &serv ) {

//	return 
//}

//int	Command::select_quit( Server &serv ) {

//	return 
//}

//int	Command::select_topic( Server &serv ) {

//	return 
//}

//int	Command::select_who( Server &server ) {

//}

//int	Command::select_whois( Server &server ) {

//}


//!このmsgは自由？
void	Command::regisration_message( void ) {
	std::string msg;
	msg = "001 " + _user->getNickName() + " :Welcome to the Internet Relay Network "\
									+ _user->getprefix()? + "\n" ;
	msg += "002 " + _user->getNickName() + " :Your host is ft_irc, running version 1.0\r\n"
	_user->ft_send(_user->getFd(), msg)
}

