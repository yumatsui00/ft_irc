#include "Socket.hpp"

Socket::Socket(int port_server){   
    _addr_server.sin_addr.s_addr = INADDR_ANY;
    _addr_server.sin_port = htons(port_server);
    _addr_server.sin_family = AF_INET;
	_socket = socket(AF_INET, SOCK_STREAM, 0);//error
	_set_non_blocking(_socket);
	_get_send_buffer_size();
	bind(_socket, (sockaddr*)&_addr_server, sizeof(_addr_server));//error
	memset(&_ev, 0, sizeof(struct epoll_event));
	_ev.events = EPOLLIN;
	_ev.data.fd = _socket;
	_set_epfd();
	epoll_ctl(_epfd, EPOLL_CTL_ADD, _socket, &_ev);
	listen(_socket, SOMAXCONN);
}

// void	Socket::Connect(){
// 	std::cout << "Waiting" << std::endl;
// 	listen(_socket, SOMAXCONN);
// 	socklen_t addr_len = sizeof(_addr_client);
// 	_new_fd = accept(_socket, (sockaddr*)&_addr_client, &addr_len);
// 	std::cout << "Success" << std::endl;
// }

void	Socket::_set_non_blocking(int fd){
	int	flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1){
		std::cerr << "fcntl F_GETFL" << std::endl;
		exit(EXIT_FAILURE);
	}
	flags |= O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) == -1){
		std::cerr << "fcntl F_SETFL" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void	Socket::_get_send_buffer_size(){
	socklen_t	len = sizeof(_send_buffer_size);

	if (getsockopt(_socket, SOL_SOCKET, SO_SNDBUF, &_send_buffer_size,  &len) == -1){
		std::cerr << "setsockopt" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "send buffer size = " << _send_buffer_size << std::endl;
}

void	Socket::_set_epfd(){
	if ((_epfd = epoll_create(MAX_FD)) < 0){
		std::cerr << "epoll_create" << std::endl;
	}
}

void	Socket::run(){
	_n_events = epoll_wait(_epfd, _events, MAX_FD, -1);
	if (_n_events <= 0){
		if (g_active == false)
			return ;
		std::cerr << "epoll_wait" << std::endl;
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < _n_events; i ++){
		if (_events[i].data.fd < 0)
			continue;
		else if (_events[i].data.fd == _socket){
			socklen_t addr_len = sizeof(_addr_client);
			_fd = accept(_socket, (sockaddr*)&_addr_client, &addr_len);//error
			_set_non_blocking(_fd);
			memset(&_ev, 0, sizeof(struct epoll_event));
			_ev.events = EPOLLIN;
			_ev.data.fd = _fd;
			epoll_ctl(_epfd, EPOLL_CTL_ADD, _fd, &_ev);//error
			std::cout << "new connection on fd " << _fd << std::endl;
		}
		else
		{
			_fd = _events[i].data.fd;
			char	buf[BUF_SIZE];
			ssize_t	byte;
			byte = read(_fd, buf, BUF_SIZE);
			if (byte == -1){
				std::cerr << "read error on fd " << _fd << std::endl;
				close(_fd);
				epoll_ctl(_epfd, EPOLL_CTL_DEL, _fd, &_events[i]);
				continue ;
			}
			else if (byte == 0)
			{
				std::cerr << "connection closed on fd " << _fd << std::endl;
				close(_fd);
				epoll_ctl(_epfd, EPOLL_CTL_DEL, _fd, &_events[i]);
				continue ;
			}
			std::cout << "Reciver\n" <<  buf;
			buf[byte] = '\0';
			byte = write(_fd, buf, byte + 1);
			if (byte == -1){
				std::cerr << "write error on fd " << _fd << std::endl;
				close(_fd);
				epoll_ctl(_epfd, EPOLL_CTL_DEL, _fd, &_events[i]);
			}
		}
	}
}

// void	Socket::RecvText()
// {
// 	char text[1024];
// 	int recv_size = recv(_new_fd, text, 1023, 0);
// 	if (recv_size <= 0)
// 		exit(0);
//     text[recv_size] = '\0';
// 	std::cout << "Recived" << text;
// }

// void	Socket::SendText(const char *text)
// {
// 	send(_new_fd, text, 1024, 0);
// 	std::cout << " and return same text" << std::endl;
// }