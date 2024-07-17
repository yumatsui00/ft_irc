#ifndef USER_HPP
# define USER_HPP

#include "all.hpp"

enum Status {
	LOGIN,
	LOGOUT,
	REGISTERED,
	HANDSHAKE,
} ;

class User {
private:
	int			_fd;
	bool		_authenticate;
	Status		_status;//最初はlogin
	std::string	_nickname;
	std::string _username;
	std::string	_password;
	std::string _hostname;
	std::string _message;
	std::string _cmd_strage; //add
	User();
public:
	User(int fd);
	~User();

	int			getFd( void ) const;
	std::string	getNickName( void ) const;
	std::string	getUserName( void ) const;
	std::string	getPassword( void ) const;
	std::string	getHostName( void ) const;

	void		setNickName( std::string &NickName );
	void		setUserName( std::string &UserName );
	void		setHostName( std::string &HostName );
	void		setPassword( std::string &Password );

	bool		isRegistered( void );
	bool		proceedRegisration( Server &server );


	void		add_cmd_strage( std::string &cmd );
	std::string	get_cmd_strage( void );
	void		clear_cmd_strage( void );

} ;

#endif