#include "all.hpp"

Channel::Channel( const std::string ch_name, User *user ) :
_ch_name(ch_name), _topic(""), _maxUsers(MAXMEMBERS), _pass(""),\
_mode_i(false), _mode_t(false), _mode_k(false), _mode_o(false), _mode_l(false) {
	addMember(user);
}


void	Channel::addMember(User* user) {
	for (std::vector<std::pair<User*, bool>>::iterator it = _users.begin(); it != _users.end(); it++) {
		if (it->first == user)
			return ;
	}
	if (this->_users.size() == 0)
		_users.push_back(std::make_pair(user, true));
	else
		_users.push_back(std::make_pair(user, false));
	return ;
} ;


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