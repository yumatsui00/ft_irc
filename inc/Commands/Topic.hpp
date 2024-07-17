#ifndef TOPIC_HPP
# define TOPIC_HPP

#include "all.hpp"
#include "Mode.hpp"

class Topic : public Mode {
public:
	Topic( Command &src, Server &server ) : Mode( src, server ) {};
	~Topic( void ) {};

	int		exec_topic( Server &server );
	int		TopicMessanger( void );
} ;

int		Topic::exec_topic( Server &server ) {
	if (!(_divCmd.size() == 2 || _divCmd.size() == 3))
		return (461);
	if (_channel == NULL)
		return (403);
	if (!_channel->isExist(_user))
		return (442);//そのチャンネルにいなかったら☓
	if (_divCmd.size() == 2)
		return (TopicMessanger());
	if (_channel->getMode(modeT))
		return (482); //topic 変更が制限されてたらだめ
	if (!_channel->isOperator(_user))
		return (482); //operatorじゃなかったら //! 諸説
	_channel->setTopic(_divCmd[2]);

}

int	Topic::TopicMessanger( void ) {
	std::string msg;

	if (!_channel->getTopic().empty())
		msg = ":ft_irc 331 " + _user->getNickName() + " " + _divCmd[1] + " :No topic is set\n";
	else
		msg = ":ft_irc 332 " + _user->getNickName() + " " + _divCmd[1] + " :" + _channel->getTopic() + "\n";
	//!ft_send(fd, msg)
	//fd, _userのみ？hatenahatena
	return (0);
}

# endif