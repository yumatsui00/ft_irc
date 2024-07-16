#include "all.hpp"

void	Command::exec_cmd(std::string &cmds, User *user , Server &serv) {
	int	*fds; //送信先のfds

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

	//一度に複数のコマンド（改行）が送られてきたときのため_lstで分割して保存
	int	status;
	std::string buf;
	std::istringstream stream(cmds.c_str());
	while (std::getline(stream, buf))
		_lst.push_back(buf);
	std::vector<std::string>::iterator it = _lst.begin();
	for (std::vector<std::string>::iterator it = _lst.begin(); it != _lst.end(); it ++) {
		//lstに改行がsaigo含まれていなかったらの処理？
		if (!set_cmd(*it))
			return ;
		status = exec(serv);
	}

	//ft_send(fd[0 ~ n], messeage);
} ;

bool	Command::set_cmd(std::string &cmd) {
	this->_command = cmd;
	this->_divCmd.clear();

	if (!cmd.empty() && cmd[cmd.size() - 1] == '\n')
		cmd.erase(cmd.size() - 1);

	std::string first, elses;
	size_t semq_pos = cmd.find(":");
	if (semq_pos != std::string::npos) {
		first = cmd.substr(0, semq_pos);
		elses = cmd.substr(semq_pos, cmd.size());
	} else
		first = cmd;

	size_t found;
	while ((found = first.find("	")) != std::string::npos)
		first.erase(found, 1);
	std::istringstream	stream(first.c_str());
	std::string			buf;
	while(std::getline(stream, buf, ' '))
		this->_divCmd.push_back(buf);
	if (elses.size() != 0)
		this->_divCmd.push_back(elses);
	return true;
} ;

int	Command::exec( Server &serv ) {
	if (_divCmd.empty())
		return 0;
	if (_divCmd[0] == "NICK")
		return nick(serv);
	else if (_divCmd[0] == "USER")
		return user(serv);
	else if ()
		return oin
} ;
