#ifndef WHOIS_HPP
# define WHOIS_HPP

#include "all.hpp"

class Whois : public Command {
private:
	Whois() {};
public:
	Whois( Command &src ) : Command( src ) {};
	~Whois() {};
	int	exec_whois( Server &server );
} ;

# endif