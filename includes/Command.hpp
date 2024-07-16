#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "all.hpp"

class Command {
protected:
	User*						_user;
	std::string					_command;//一つのコマンド
	std::vector<std::string>	_divCmd; //一つのコマンドを分けたの
	std::vector<std::string>	_lst; //複数コマンド同時送信用のリスト
public:
	explicit	Command( void );
	virtual		~Command( void );
	void		exec_cmd( std::string &command, User *user, Server &server );
	bool		set_cmd( std::string &cmd);
	int			exec( Server &server );
} ;

void 		ft_send(int fd, std::string message);

class Join : public Command {
private:
	Join();
public:
	Join( Command &cmd );
	~Join(){};
} ;

#endif

//KICK #a aa \n KICK #a aaa \n →これが一行で対応 _lst