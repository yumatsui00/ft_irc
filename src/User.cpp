#include "irc.hpp"
#include "User.hpp"
#include "Server.hpp"

//!----------GETTER---------
int			User::getFd( void ) const {
	return _fd;
} ;

Status		User::getStatus( void ) const {
	return _status;
};

std::string	User::getNickName( void ) const {
	return _nickname;
} ;

std::string	User::getUserName( void ) const {
	return _username;
} ;

std::string User::getPassword( void ) const {
	return _password;
}

std::string	User::getHostName( void ) const {
	return _hostname;
} ;

std::string	User::getPrefix( void ) const {
	std::string	prefix;

	if (_nickname.empty())
		prefix = "\?\?\?!";
	else
		prefix = _nickname + "!";
	if (_username.empty())
		prefix += "\?\?\?!";
	else
		prefix = _username + "!";
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

void	User::setPassword( std::string &Password ) {
	this->_password = Password;
} ;

void	User::setStatus( Status status ) {
	this->_status = status;
} ;



//!----------------------------others--------------------------------

bool	User::isRegistered( void ) {
	return (this->_status == REGISTERED ? true : false );
} ;

void	User::add_cmd_strage( std::string &add ) {
	this->_cmd_strage += add;
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