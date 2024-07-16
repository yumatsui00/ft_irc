#ifndef USER_HPP
# define USER_HPP

#include "all.hpp"

class User {
private:
	int			_fd;
	bool		_authenticate;
	std::string	_nickname;
	std::string _username;
	std::string _hostname;
	std::string _message;
	std::string _cmd_strage; //add
	User();
public:
	User(int fd);
	~User();

	int			getFd( void );
	std::string	getNickName( void );
	std::string	getUserName( void );
	std::string	getHostName( void );

	void		add_cmd_strage( std::string &cmd );
	std::string	get_cmd_strage( void );
	void		clear_cmd_strage( void );

} ;

#endif