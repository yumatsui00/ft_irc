#include "irc.hpp"
#include "User.hpp"
#include "Server.hpp"

//!----------GETTER---------
int			User::getFd( void ) const {
	return _fd;
} ;



std::string	User::getNickName( void ) const {
	return _nickname;
} ;

std::string	User::getUserName( void ) const {
	return _username;
} ;

bool		 User::getpassok( void ) const {
	return _passok;
}

std::string	User::getHostName( void ) const {
	return _hostname;
} ;

std::string User::getMessage ( void ) const {
	return _message;
}

std::string	User::getPrefix( void ) const {
	std::string	prefix;

	if (_nickname.empty())
		prefix = "\?\?\?!";
	else
		prefix = _nickname + "!";
	if (_username.empty())
		prefix += "\?\?\?!";
	else
		prefix += _username + "!";
	prefix += "@";
	prefix += _hostname;
	return (prefix);
}

std::string	User::get_cmd_strage( void ) {
	return _cmd_strage;
} ;

//!---------------------------SETTER-------------------------------

void	User::setNickName( std::string &NickName ) {
	this->_nickname = NickName;
} ;

void	User::setUserName( std::string &UserName ) {
	this->_username = UserName;
} ;

void	User::setHostName( std::string &HostName ) {
	this->_hostname = HostName;
} ;

void	User::setPassok( bool passok ) {
	this->_passok = passok;
} ;


void	User::setMessage( std::string &mes ){
	this->_message += mes;
}

void	User::clearMessage( void ){
	this->_message.clear();
}

//!----------------------------others--------------------------------

bool	User::isRegistered( void ) {
	return (_registered);
} ;

void	User::setIsRegistered( bool status ) {
	_registered = status;
} ;

void	User::add_cmd_strage( std::string &add ) {
	this->_cmd_strage += add;
	std::cout << _cmd_strage << std::endl;
} ;


void	User::clear_cmd_strage( void ) {
	_cmd_strage.clear();
	return ;
}

bool	User::operator==( User& rhs ) {
	if (this == &rhs)
		return true;
	return false;
} ;