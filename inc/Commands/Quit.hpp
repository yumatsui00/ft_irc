#ifndef QUIT_HPP
# define QUIT_HPP

#include "../all.hpp"

class Quit : public Command {
private:
	Quit() {};
public:
	Quit( Command &src ) : Command( src ) {};
	~Quit() {};
	int	exec_quit( Server &server );
} ;

int	Quit::exec_quit( Server &server ) {
	//byebye
	return (999);
}

#endif