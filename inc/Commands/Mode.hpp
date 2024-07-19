#ifndef MODE_HPP
# define MODE_HPP

#include "../all.hpp"

class Mode : public Command {
private:
	int		displayCurrentMode( void );
	int		modeChanger( Server &server, size_t size );
	int		checkNum( std::string num );
protected:
	Channel *_channel;
	Mode() {};
public:
	Mode( Command &src ) : Command( src ) {};
	Mode( Command &src, Server &server );
	virtual ~Mode() {};


	int		exec_mode( Server &server );
	void	setChannel( Channel *channel );

	void	modePassword( bool mode, std::string newPass );
	bool	modeLimit( bool mode, int num );

} ;

Mode::Mode( Command &src, Server &server ) : Command( src ) {
	//Channelを使用するコマンドは、２つ目の引数にchannel名が来ることが多い、存在したらそれを設定、なかったらNULL
	if (this->_divCmd[1].empty()) {
		this->_channel = NULL;
		return ;
	}
	else {
		for (std::set<Channel*>::iterator it = server.getChannels().begin(); it != server.getChannels().end(); it++) {
			if ((*it)->getChannelName() == _divCmd[1]) {
				this->_channel = *it;
				return ;
			}
		}
	};
	this->_channel = NULL;
}




int		Mode::exec_mode( Server &server ) {
	if (!(2 <= _divCmd.size() && _divCmd.size() <= 4))
		return (461);
	if (_channel == NULL)
		return (403);
	if (!_channel->isExist(_user))
		return (442);
	if (_divCmd.size() == 2)
		return (displayCurrentMode());
	if (!_channel->isOperator(_user))
		return (482);
	return (modeChanger( server, _divCmd.size() ));
} ;

int		Mode::displayCurrentMode( void ) {
	std::string msg;

	msg = ":ft_irc 324" + _user->getNickName() + _divCmd[1] + " +";
	if ((_channel->getMode(modeK)))
		msg += "k";
	if ((_channel->getMode(modeL)))
		msg += "l";
	if ((_channel->getMode(modeI)))
		msg += "i";
	if ((_channel->getMode(modeT)))
		msg += "t";
	if ((_channel->getMode(modeO)))
		msg += "o";
	if ((_channel->getMode(modeK)))
		msg += " " + _channel->getPass();
	if ((_channel->getMode(modeL))) {
		size_t	tmp = _channel->getMaxusers();
		std::ostringstream oss;
		oss << tmp;
		msg += " " + oss.str();
	}
	msg += "\n";
	//ft_semd(fd, msg) fd = だれ
	return (0);
}

int		Mode::modeChanger( Server &server, size_t size ) {
	bool		msg_permission = true;
	std::string mod = _divCmd[1], arg1 = _divCmd[2], arg2;
	std::string msg = ":" + _user->getPrefix() + " MODE" + mod + " " + arg1;

	if (size == 3)
		msg += "\n";
	else if (size == 4) {
		arg2 = _divCmd[3];
		msg += " " + arg2 + "\n";
	}

	if (mod == "+i" && size == 3)
		_channel->setMode(modeI, true);
	else if (mod == "-i" && size == 3)
		_channel->setMode(modeI, false);
	else if (mod == "+t" && size == 3)
		_channel->setMode(modeT, true);
	else if (mod == "-t" && size == 3)
		_channel->setMode(modeT, false);
	else if (mod == "+k" && size == 4)
		modePassword(true, arg2);
	else if (mod == "-k" && size == 4)
		modePassword(false, "");
	else if (mod == "+l" && size == 4) {
		if (!modeLimit(true, checkNum(arg2)))
			return (401); //err番号怪しい
	}
	else if (mod == "-l" && size == 3)
		modeLimit(false, MAXMEMBERS);
	else if ((mod == "+o" || mod == "-o") && size == 4) {
		User* target = _channel->nick2User(arg2);
		if (target == NULL)
			return (441);
		if (mod == "+o")
			_channel->becomeOperator(target);
		else
			_channel->ceaseOperator(target);
	}
	else
		msg_permission = false;
	if (msg_permission == true)
		//ft_send(fd, aef); fd = すべてのひと
	return (0);
}

void	Mode::modePassword( bool mode, std::string newPass ) {
	if (mode == true) {
		this->_channel->setMode(modeK, mode);
		this->_channel->changePass( newPass );
	} else {
		this->_channel->setMode(modeK, mode);
		this->_channel->changePass( "" );
	}
} ;

int		Mode::checkNum( std::string num ) {
	int		number;

	std::istringstream iss(num);
	iss >> num;
	if (iss.eof() && !iss.fail())
		return (-1);
	return number;
}

bool	Mode::modeLimit( bool mode, int num ) {
	if (num <= 0)
		return false;
	if (mode == true) {
		_channel->setMode(modeL, true);
		_channel->changeLimit(num);
	} else {
		_channel->setMode(modeT, false);
	}
	return true;
} ;

# endif