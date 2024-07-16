#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "all.hpp"

class Channel {
private:
	std::string								_ch_name;
	std::string								_topic;
	std::vector <std::pair<User*, bool>>	_users;
	size_t									_maxUsers;
	std::string								_pass;
	int										_mode; //招待限定モード、パスワードありなしなど
	std::vector<std::string>				_invitingNameList;

	Channel( void ) {};
public:
	Channel(const std::string ch_name, User *user);
	~Channel( void );

};

#endif