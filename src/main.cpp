#include "Socket.hpp"
#include "Server.hpp"

#include <stdlib.h>
#include <errno.h>
#include <limits.h>

bool	g_active = true;

int	ft_strtol(char *str)
{

	char	*endptr;
	errno = 0;
	long	num = strtol(str, &endptr, 10);
	if (errno != 0 || *endptr != '\0' || str[1] == *endptr){
		std::cerr << "Input invalid port number" << std::endl;
		std::exit(1);
	}
	if (num < 1024 || 65535 < num){
		std::cerr << "Port number is out of range (1024 ~ 65535)" << std::endl;
		std::exit(1);
	}
	return ((int)num);
}

void	signal_handler(int signum)
{
	std::cout << "Signal " << signum << " recived" << std::endl;
	g_active = false;
}

int main (int ac, char **av)
{
	if (ac != 3){
		std::cerr << "./ircserv <port> <password>" << std::endl;
		return (1);
	}
	int	port = ft_strtol(av[1]);
	Server server(port, av[2]);
	signal(SIGINT, signal_handler);

	while (g_active){
		server.run();
	}
	return (0);
}
