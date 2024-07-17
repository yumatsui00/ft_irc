#ifndef JOIN_HPP
# define JOIN_HPP

#include "all.hpp"
#include "Mode.hpp"



class Join : public Mode {
private:

public:
	Join( Command &src, Server &server ) : Mode( src, server ) {};
	~Join() {};
	int	exec_join( Server &server );
	int	creatChannel( Server &server );
} ;

int	Join::exec_join( Server &server ) {
	Channel *ch;

	if (!(this->_divCmd.size() == 2 || this->_divCmd.size() == 3))
		return (461); //command check
	if (_channel == NULL) //channel が存在しなかったら作成する
		return (creatChannel(server));
	
	return 0;
}



int	Join::creatChannel( Server &server ) {
	if (_divCmd[1][0] != '#')
		return 403;
	if (_divCmd[1].size() == 1)
		return 403;
	Channel *ch = new Channel(_divCmd[1], this->_user);
	server.addChannel(ch);
	this->_channel = ch;
	if (_divCmd.size() == 3 && !_divCmd[2].empty())
		modePassword(true, _divCmd[2]);



	return 0;
}

# endif