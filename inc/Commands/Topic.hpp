#ifndef TOPIC_HPP
# define TOPIC_HPP

#include "all.hpp"

class Topic : public Command {
private:
	Topic() {};
public:
	Topic( Command &src ) : Command( src ) {};
	~Topic() {};
	int	exec_topic( Server &server );
} ;

# endif