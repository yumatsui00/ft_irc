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
	std::map <User*, bool>					_users;//a user who is an operator is true
	size_t									_maxUsers;
	std::string								_pass;
	std::set<std::string>				_invitingNameList;
	bool									_mode_i; //招待モード
	bool									_mode_t; //topic
	bool									_mode_k; //password有無
	bool									_mode_o; //operator付与等
	bool									_mode_l;//制限


	Channel( void ) {};
public:

	Channel( const std::string ch_name, User *user );
	~Channel( void ) {};

	bool	isExist( User *user );
	bool	isOperator( User *user );
	bool	isInInvitingList( std::string nickname );
	bool	isMemberExist();

	std::string	getChannelName( void ) const;
	std::string	getUsersList( void ); //なぜかconst使えない？
	std::string	getPass( void ) const;
	std::string	getTopic( void ) const;
	void		setTopic( std::string newTopic ) ;

	size_t		getMaxusers( void ) const;
	size_t		getUsersNum( void ) const;
	User*		nick2User( std::string nickname ) ;

	void		addMember( User *user );
	void		delMember( User *user );
	void		addInvitingList( std::string nickname );

	void	setMode( int mode, bool on_off );
	bool	getMode( int mode );

	void	changePass( std::string newPass );
	void	changeLimit( size_t num );
	void	becomeOperator( User* user );
	void	ceaseOperator( User* user );
};



#endif