#ifndef SOCKET_HPP
# define SOCKET_HPP

#include "irc.hpp"
#include "User.hpp"
#include "Channel.hpp"

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 8080
#define BUF_SIZE 16384
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
		std::vector<std::pair<int, std::string> >	_lst;
		struct sockaddr_in	_addr_server;
		struct sockaddr_in	_addr_client;
		struct epoll_event	_events[MAX_FD];
		struct epoll_event	_ev;

		void	_set_non_blocking(int fd);
		void	_get_send_buffer_size();
		void	_set_epfd();
		void	_exit_mes(const char *mes);
		void	recv_fd(int i);
		void	send_fd(int i);
		void	new_connection();
		void	close_connection(int fd);
	protected:
		std::set<User*>		_Users;
		std::set<Channel*>	_Channels;
	public:
		Socket();
		Socket(int port_server);
		~Socket();
		std::vector<std::pair<int, std::string> >	get_command();
		void	run();
		void	event_epollout(int fd);
		void	event_epollin(int fd);
		User*		fd2User(int fd);
		void	del_user_all(int fd);

};

#endif