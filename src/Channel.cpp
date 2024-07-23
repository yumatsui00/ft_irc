#include "irc.hpp"
#include "Channel.hpp"

Channel::Channel( const std::string &ch_name, User *user )
: _ch_name(ch_name), _topic(""), _maxUsers(MAXMEMBERS), _pass("") {
	_modes[MODE_I] = false;
	_modes[MODE_T] = false;
	_modes[MODE_K] = false;
	_modes[MODE_O] = false;
	_modes[MODE_L] = false;
	addMember(user);
} ;




//!------------------------ GETTER---------------------------------------------------------------------

std::string	Channel::getChannelName( void ) const {
	return _ch_name;
} ;

std::string Channel::getUsersList( void ) {
	std::string list;

	for (std::map<User*, bool>::iterator it = _users.begin() ; it != _users.end(); it ++) {
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

bool	Channel::getMode( int mode ) {
	std::map<size_t, bool>::iterator it = _modes.find(mode);
	if (it != _modes.end())
		return (it->second);
	return false;
}

std::map<User*, bool>	Channel::getUsers( void ) const {
	return _users;
};

User*	Channel::nick2User( std::string nickname ) {
	for (std::map<User*, bool>::iterator it = _users.begin(); it != _users.end(); it ++) {
		if (it->first->getNickName() == nickname)
			return (it->first);
	}
	return NULL;
} ;






//!------------------------ Others---------------------------------------------------------------------
bool	Channel::isExist( User *user ) {
	std::map<User*, bool>::iterator it = _users.find(user);
	if (it != _users.end())
		return true;
	return false;
} ;

bool	Channel::isOperator( User *user ) {
	std::map<User*, bool>::iterator it = _users.find(user);
	if (it != _users.end())
		return (it->second);
	return false;
}

bool	Channel::isInInvitingList( std::string nickname ) {
	std::set<std::string>::iterator it = _invitingNameList.find(nickname);
	if (it != _invitingNameList.end())
		return true;
	return false;
}

bool	Channel::isMemberExist( void ) {
	if (_users.begin() == _users.end())
		return false;
	else
		return true;
}
void	Channel::setMode( int mode, bool on_off ) {
	std::map<size_t, bool>::iterator it = _modes.find(mode);
	if (it != _modes.end())
		it->second = on_off;
} ;

void	Channel::setTopic( std::string newTopic ) {
	_topic = newTopic;
	return ;
}

void	Channel::changePass( std::string newPass ) {
	if (_modes[MODE_K] == true)
		_pass = newPass;
	else
		_pass = "";
}

void	Channel::changeLimit( size_t num ) {
	if (_modes[MODE_L] == true)
		_maxUsers = num;
} ;

void	Channel::addInvitingList( std::string nickname ) {
	_invitingNameList.insert(nickname);
}

void	Channel::becomeOperator( User* user ) {
	std::map<User*, bool>::iterator it = _users.find(user);
	if (it != _users.end())
		it->second = true;
	return ;
} ;

void	Channel::ceaseOperator( User* user ) {
	std::map<User*, bool>::iterator it = _users.find(user);
	if (it != _users.end())
		it->second = false;
	return ;
}

void	Channel::delMember( User *user ) {
	std::map<User*, bool>::iterator it = _users.find(user);
	if (it != _users.end())
		_users.erase(it);
	return ;//!operatorが自分をキックしたらオペレーターがいなくなる
} ;

void	Channel::addMember( User* user ) {
	std::map<User*, bool>::iterator it = _users.find(user);
	if (it != _users.end())
		return ;
	if (this->_users.size() == 0)
		_users.insert(std::make_pair(user, true));
	else {
		_users.insert(std::make_pair(user, false));
		if (getMode(MODE_I)) { //もし招待モードだったらリストから消す
			for (std::set<std::string>::iterator it = _invitingNameList.begin(); it != _invitingNameList.end(); it++) {
				if ((*it) == user->getNickName()) {
					_invitingNameList.erase(it);
					return ;
				}
			}
		}
	}
	return ;
} ;

