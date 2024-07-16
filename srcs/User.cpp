#include "all.hpp"






int	User::getFd( void ) {
	return _fd;
} ;

std::string	User::getNickName( void ) {
	return _nickname;
} ;

std::string	User::getUserName( void ) {
	return _username;
} ;

std::string	User::getHostName( void ) {
	return _hostname;
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
