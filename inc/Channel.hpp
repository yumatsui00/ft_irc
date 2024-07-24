#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "irc.hpp"
#include "User.hpp"
#define NAMELENGTH 200
#define MAXMEMBERS 200

#define MODE_I 1
#define MODE_T 2
#define MODE_K 3
#define MODE_O 4
#define MODE_L 5

class User;

class Channel {
private:
	std::string								_ch_name;
	std::string								_topic;
	std::map <User*, bool>					_users;//a user who is an operator is true
	size_t									_maxUsers;
	std::string								_pass;
	std::set<std::string>				_invitingNameList;
	std::map<size_t, bool>					_modes;

	Channel( void ) {};
public:

	Channel( const std::string &ch_name, User *user );
	~Channel( void ) {};

//!------------------------GETTER---------------------------
	std::string	getChannelName( void ) const;
	std::string	getUsersList( void ); //なぜかconst使えない？
	std::string	getPass( void ) const;
	std::string	getTopic( void ) const;
	size_t		getMaxusers( void ) const;
	size_t		getUsersNum( void ) const;
	bool		getMode( int mode );
	std::map<User*, bool>	getUsers( void ) const ;
	User*		nick2User( std::string nickname ) ;

//!------------------------Others---------------------------
	bool		isExist( User *user );
	bool		isOperator( User *user );
	bool		isInInvitingList( std::string nickname );
	bool		isMemberExist();

	void		setTopic( std::string newTopic ) ;
	void		setMode( int mode, bool on_off );
	void		changePass( std::string newPass );
	void		changeLimit( size_t num );

	void		addMember( User *user );
	void		delMember( User *user );
	void		addInvitingList( std::string nickname );

	void		becomeOperator( User* user );
	void		ceaseOperator( User* user );

};



#endif