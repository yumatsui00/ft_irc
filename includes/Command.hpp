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
	Command( Command &src );
	virtual		~Command( void );

	User*						getUser( void ) const;
	std::string					getCmd( void ) const ;
	std::vector<std::string>	getDivCmd( void ) const ;
	std::vector<std::string>	getLst( void ) const ;

	void		exec_cmd( std::string &command, User *user, Server &server );
	void		set_cmd( std::string &cmd);
	int			exec( Server &server );

	int			select_nick( Server &server );
	int			select_user( Server &server );
	int			select_pass( Server &server );
	int			select_invite( Server &server );
	int			select_join( Server &server );
	int			select_kick( Server &server );
	int			select_mode( Server &server );
	int			select_part( Server &server );
	int			select_ping( Server &server );
	int			select_privmsg( Server &server );
	int			select_quit( Server &server );
	int			select_topic( Server &server );
	int			select_who( Server &server );
	int			select_whois( Server &sever );

	void		regisration_message( void );
} ;

void 		ft_send(int fd, std::string message);

#endif

//KICK #a aa \n KICK #a aaa \n →これが一行で対応 _lst