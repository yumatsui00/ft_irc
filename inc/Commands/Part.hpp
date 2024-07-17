#ifndef PART_HPP
# define PART_HPP

#include "all.hpp"

class Part : public Command {
private:
	Part() {};
public:
	Part( Command &src ) : Command( src ) {};
	~Part() {};
	int	exec_part( Server &server );
} ;

# endif