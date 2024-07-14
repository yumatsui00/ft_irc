#include "Socket.hpp"

bool	g_active = true;

void	signal_handler(int signum)
{
	std::cout << "Signal " << signum << " recived";
	g_active = false;
}

int main ()
{
	Socket socket(5000);

	signal(SIGINT, signal_handler);

	while (g_active)
	{
		socket.run();
	}
	return (0);
}