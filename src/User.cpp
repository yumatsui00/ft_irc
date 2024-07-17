#include "all.hpp"






int	User::getFd( void ) const {
	return _fd;
} ;

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




bool	User::isRegistered( void ) {
	return (this->_status == REGISTERED ? true : false );
} ;

bool	User::proceedRegisration( Server &server ) {
	if (_status == REGISTERED)
		return false;
	if (!_nickname.empty() && !_username.empty() && (_password == server.getPassword())) {
		this->_status = REGISTERED;
		return true;
	}
	return false;
} ;


void		User::add_cmd_strage( std::string &add ) {
	this->_cmd_strage += add;
} ;

std::string	User::get_cmd_strage( void ) {
	return _cmd_strage;
} ;

void		User::clear_cmd_strage( void ) {
	_cmd_strage.clear();
	return ;
}


bool	User::operator==( User& rhs ) {
	if (this == &rhs)
		return true;
	return false;
} ;