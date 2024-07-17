#ifndef MODE_HPP
# define MODE_HPP

#include "all.hpp"

class Mode : public Command {
protected:
	Channel *_channel;
	Mode() {};
public:
	Mode( Command &src ) : Command( src ) {};
	Mode( Command &src, Server &server ) : Command( src ) {}
	virtual ~Mode() {};


	int		exec_mode( Server &server );
	void	setChannel( Channel *channel );
	void	modePassword( bool mode, std::string newPass );
} ;

Mode::Mode( Command &src, Server &server ) : Command( src ) {
	//Channelを使用するコマンドは、２つ目の引数に必ずchannel名が来るので、存在したらそれを設定、なかったらNULL
	if (this->_divCmd[1].empty()) {
		this->_channel = NULL;
		return ;
	}
	else {
		for (std::vector<Channel*>::iterator it = server.getChannels().begin(); it != server.getChannels().end(); it++) {
			if ((*it)->getChannelName() == _divCmd[1]) {
				this->_channel = *it;
				return ;
			}
		}
	};
	this->_channel = NULL;
}

void	Mode::modePassword( bool mode, std::string newPass ) {
	if (mode == true) {
		this->_channel->setMode(modeK, mode);
		//途中
	}
}

# endif