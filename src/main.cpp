#include "Socket.hpp"
#include "Server.hpp"

bool	g_active = true;

void	signal_handler(int signum)
{
	std::cout << "Signal " << signum << " recived";
	g_active = false;
}

int main (int ac, char **argv)
{
	if (ac != 3){
		std::cerr << "./ircserv <port> <password>" << std::endl;
	}
	Server server;
	signal(SIGINT, signal_handler);

	while (g_active)
	{
		server.run();
	}
	return (0);
}