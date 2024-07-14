#ifndef SOCKET_HPP
# define SOCKET_HPP

#include "Webserv.hpp"

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 8080
#define BUF_SIZE 1024
#define	MAX_FD	200

extern bool	g_active;

class	Socket
{
	private:
		int		_socket;
		int		_fd;
		int		_send_buffer_size;
		int		_epfd;
		int		_n_events;
		struct sockaddr_in	_addr_server;
		struct sockaddr_in	_addr_client;
		struct epoll_event	_events[MAX_FD];
		struct epoll_event	_ev;
	
		void	_set_non_blocking(int fd);
		void	_get_send_buffer_size();
		void	_set_epfd();
	public:
		Socket(int port_server);
		void	run();
		
		void Connect();

		void SendText(const char* text);
		void RecvText();
};


#endif