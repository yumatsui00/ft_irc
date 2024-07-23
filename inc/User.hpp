#ifndef USER_HPP
# define USER_HPP

#include "irc.hpp"

class User {
private:
	int			_fd;
	bool		_passok; //falseで初期化
	bool		_registered;//最初はlogin
	std::string	_nickname;
	std::string _username;
	std::string _hostname;
	std::string _message; //
	std::string _cmd_strage; //add
	User() {};
public:
	User(int fd) : _fd(fd) {};
	~User() {};
	//!---------------------GETTER-----------------------------
	int			getFd( void ) const;
	bool		getpassok( void ) const;
	bool		getStatus( void ) const;
	std::string	getNickName( void ) const;
	std::string	getUserName( void ) const;
	std::string	getHostName( void ) const;
	std::string	getPrefix( void ) const;
	std::string	get_cmd_strage( void );
	std::string getMessage( void ) const;

	//!---------------------SETTER---------------------------------
	void		setNickName( std::string &NickName );
	void		setUserName( std::string &UserName );
	void		setHostName( std::string &HostName );
	void		setPassok( bool passok );
	void		setIsRegistered( bool status );
	void		setMessage( std::string &mes);

	void		clearMessage();

	//!---------------------others--------------------------------

	bool		isRegistered( void );
	void		add_cmd_strage( std::string &cmd );
	void		clear_cmd_strage( void );

	bool		operator==( User &rhs );
} ;

#endif