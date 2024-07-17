#ifndef WHO_HPP
# define WHO_HPP

#include "all.hpp"

class Who : public Command {
private:
	Who() {};
public:
	Who( Command &src ) : Command( src ) {};
	~Who() {};
	int	exec_who( Server &server );
} ;

# endif