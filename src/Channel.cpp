#include "all.hpp"

Channel::Channel( const std::string ch_name, User *user ) :
_ch_name(ch_name), _topic(""), _maxUsers(MAXMEMBERS), _pass(""),\
_mode_i(false), _mode_t(false), _mode_k(false), _mode_o(false), _mode_l(false) {
	addMember(user);
}

bool	Channel::isExist( User *user ) {
	for (std::vector<std::pair<User*, bool> >::iterator it = _users.begin(); it != _users.end(); it ++) {
		if (it->first == user)
			return true;
	}
	return false;
} ;

bool	Channel::isOperator( User *user ) {
	for (std::vector<std::pair<User*, bool> >::iterator it = _users.begin(); it != _users.end(); it ++) {
		if (it->first == user) {
			return (it->second);
		}
	}
	return false;
}

bool	Channel::isInInvitingList( std::string nickname ) {
	for (std::vector<std::string>::iterator it = _invitingNameList.begin(); it != _invitingNameList.end(); it++) {
		if ((*it) == nickname)
			return true;
	}
	return false;
}

User*	Channel::nick2User( std::string nickname ) {
	for (std::vector<std::pair<User*, bool> >::iterator it = _users.begin(); it != _users.end(); it ++) {
		if (it->first->getNickName() == nickname)
			return (it->first);
	}
	return NULL;
} ;



void	Channel::addMember( User* user ) {
	for (std::vector<std::pair<User*, bool>>::iterator it = _users.begin(); it != _users.end(); it++) {
		if (it->first == user)
			return ;//おなじひとがいたら何もしない
	}
	if (this->_users.size() == 0)
		_users.push_back(std::make_pair(user, true));
	else {
		_users.push_back(std::make_pair(user, false));
		if (getMode(modeI)) { //もし招待モードだったらリストから消す
			for (std::vector<std::string>::iterator it = _invitingNameList.begin(); it != _invitingNameList.end(); it++) {
				if ((*it) == user->getNickName()) {
					_invitingNameList.erase(it);
					return ;
				}
			}
		}
	}
	return ;
} ;

void	Channel::addInvitingList( std::string nickname ) {
	_invitingNameList.push_back(nickname);
}


std::string Channel::getUsersList( void ) {
	std::string list;

	for (std::vector<std::pair<User*, bool> >::iterator it = _users.begin() ; it != _users.end(); it ++) {
		if (!list.empty())
			list += " ";
		if (it->second == true)
			list += "@";
		list += it->first->getNickName();
	}
	return (list);
} ;

std::string Channel::getPass( void ) const {
	return _pass;
} ;

size_t		Channel::getMaxusers( void ) const {
	return _maxUsers;
} ;

size_t		Channel::getUsersNum( void ) const {
	return _users.size();
} ;

std::string	Channel::getTopic( void ) const {
	return _topic;
} ;

void		Channel::setTopic( std::string newTopic ) {
	_topic = newTopic;
	return ;
}

bool	Channel::getMode( int mode ) {
	switch (mode)
	{
		case modeI:
			return (_mode_i);
		case modeT:
			return (_mode_t);
		case modeK:
			return (_mode_k);
		case modeO:
			return (_mode_o);
		case modeL:
			return (_mode_l);
		default:
			return (false);
	}
}

void	Channel::setMode( int mode, bool on_off ) {
	switch (mode)
	{
		case modeI:
			this->_mode_i = on_off;
			break ;
		case modeT:
			this->_mode_t = on_off;
			break ;
		case modeK:
			this->_mode_k = on_off;
			break ;
		case modeO:
			this->_mode_o = on_off;
			break ;
		case modeL:
			this->_mode_l = on_off;
			break ;
		default:
			std::cout << "error" << std::endl;
			break;
	}
} ;

void	Channel::changePass( std::string newPass ) {
	if (this->_mode_k == true)
		_pass = newPass;
	else
		_pass = "";
}