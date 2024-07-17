#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "all.hpp"

#define NAMELENGTH 200
#define MAXMEMBERS 200

#define modeI 1
#define modeT 2
#define modeK 3
#define modeO 4
#define modeL 5

class Channel {
private:
	std::string								_ch_name;
	std::string								_topic;
	std::vector <std::pair<User*, bool>>	_users;//a user who is an operator is true
	size_t									_maxUsers;
	std::string								_pass;
	std::vector<std::string>				_invitingNameList;
	bool									_mode_i;
	bool									_mode_t;
	bool									_mode_k;
	bool									_mode_o;
	bool									_mode_l;


	Channel( void ) {};
public:

	Channel( const std::string ch_name, User *user );
	~Channel( void ) {};



	std::string	getChannelName( void );

	void	addMember( User *user );
	void	setMode( int mode, bool on_off );
};



#endif