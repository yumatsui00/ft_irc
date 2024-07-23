#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "irc.hpp"
#include "Server.hpp"
#include "User.hpp"


class Command {
protected:
	User*						_user;
	std::string					_command;//一つのコマンド
	std::vector<std::string>	_divCmd; //一つのコマンドを分けたの
	std::vector<std::string>	_lst; //複数コマンド同時送信用のリスト
public:
	explicit	Command( void ){};
	Command( Command &src );
	~Command( void ) {};

	void		exec_cmd( std::string &command, User *user, Server &server );
	void		set_cmd( std::string &cmd);
	int			exec( Server &server );

//!-----------------------Commands---------------------------
	int			nick( Server &server );
	int			user( Server &server );
	int			pass( Server &server );
		bool		proceedRegisration( Server &server );
	int			invite( Server &server );
	int			join( Server &server );
		int			creatChannel( Server &server );
		int			joinChannel( Server &server, Channel* channel );
	int			kick( Server &server );
	int			mode( Server &server );
		int			displayCurrentMode( Channel* channel, Server &server );
		int			modeChanger( Server &server, Channel *channel, size_t size );
		int			checkNum( std::string num );
	int			quit( Server &server );
	int			part( Server &server );
	int			ping( Server &server );
	int			privmsg( Server &server );
	int			topic( Server &server );

//?--------------------messanger----------------------------
	void		InviteMessanger( Server &server, int invitedFd );
	void		JoinMessanger( Channel* channel, Server &server );
	void		KickMessanger( Server &server, Channel* channel );
	int			TopicMessanger( Channel* channel, Server &server, bool set );
	void		regisration_message( Server &server );
	void		printError( int status, Server &server );



} ;

void 		ft_send(int fd, std::string message);

#endif

//KICK #a aa \n KICK #a aaa \n →これが一行で対応 _lst