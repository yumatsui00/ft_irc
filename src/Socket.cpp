#include "Socket.hpp"

Socket::Socket(){}

Socket::~Socket(){
	close(_socket);
}


Socket::Socket(int port_server){   
    _addr_server.sin_addr.s_addr = INADDR_ANY;
    _addr_server.sin_port = htons(port_server);
    _addr_server.sin_family = AF_INET;
	if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		_exit_mes("socket");
	_set_non_blocking(_socket);
	_get_send_buffer_size();
	if ((bind(_socket, (sockaddr*)&_addr_server, sizeof(_addr_server))) < 0)
		_exit_mes("bind");
	std::memset(&_ev, 0, sizeof(struct epoll_event));
	_ev.events = EPOLLIN;
	_ev.data.fd = _socket;
	_set_epfd();
	if (epoll_ctl(_epfd, EPOLL_CTL_ADD, _socket, &_ev) == -1)
		_exit_mes("epoll_ctl Socket");
	if ((listen(_socket, SOMAXCONN)) == -1)
		_exit_mes("lesten");
	std::cout << "Server is active Port " << port_server << std::endl;
}

void	Socket::_set_non_blocking(int fd){
	int	flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1){
		_exit_mes("fcntl F_GETFL");
	}
	flags |= O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) == -1){
		_exit_mes("fcntl F_SETFL" );
	}
}

void	Socket::_get_send_buffer_size(){
	socklen_t	len = sizeof(_send_buffer_size);

	if (getsockopt(_socket, SOL_SOCKET, SO_SNDBUF, &_send_buffer_size,  &len) == -1){
		_exit_mes("setsockopt");
	}
	// std::cout << "Send buffer size = " << _send_buffer_size << std::endl;
}

void	Socket::_set_epfd(){
	if ((_epfd = epoll_create(MAX_FD)) < 0){
		_exit_mes("epoll_create");
	}
}

void	Socket::run(){
	_n_events = epoll_wait(_epfd, _events, MAX_FD, -1);
	if (_n_events <= 0){
		if (g_active == false)
			return ;
		_exit_mes("epoll_wait");
	}
	for(int i = 0; i < _n_events; i ++){
		if (_events[i].data.fd < 0)
			continue;
		else if (_events[i].data.fd == _socket)
			new_connection();
		else if (_events[i].events  & EPOLLIN)
			recv_fd(i);
		else if (_events[i].events & EPOLLOUT)
			send_fd(i);
	}
}

void	Socket::_exit_mes(const char *mes){
	std::cerr << mes << std::endl;
	std::exit(EXIT_FAILURE);
}

void	Socket::event_epollout(int fd){
	_ev.events = EPOLLIN | EPOLLOUT;
	_ev.data.fd = fd;
	if (epoll_ctl(_epfd, EPOLL_CTL_MOD, fd, &_ev) == -1)
		_exit_mes("epoll_ctl event_epollout");
}

void	Socket::event_epollin(int fd){
	_ev.events = EPOLLIN;
	_ev.data.fd = fd;
	if (epoll_ctl(_epfd, EPOLL_CTL_MOD, fd, &_ev) == -1)
		_exit_mes("epoll_ctl event_epollin");
}

void	Socket::new_connection(){
	socklen_t addr_len = sizeof(_addr_client);
	if ((_fd = accept(_socket, (sockaddr*)&_addr_client, &addr_len)) < 0)
		_exit_mes("accept");
	_set_non_blocking(_fd);
	std::memset(&_ev, 0, sizeof(struct epoll_event));
	_ev.events = EPOLLIN;
	_ev.data.fd = _fd;
	if (epoll_ctl(_epfd, EPOLL_CTL_ADD, _fd, &_ev) == -1)
		_exit_mes("epoll_ctl new_client");
	std::cout << "New connection on fd " << _fd << std::endl;
}

void	Socket::recv_fd(int i){
	_fd = _events[i].data.fd;
	std::string buf(BUF_SIZE, '\0');
	ssize_t	byte;
	byte = recv(_fd, &buf[0], BUF_SIZE, 0);
	if (byte == -1){
		if (errno == EAGAIN) // errno == EWOULDBLOCK 同じらしい
			std::cerr << "Read would block on fd " << _fd << std::endl;
		else{
			std::cerr << "Read error on fd " << _fd << std::endl;
			close(_fd);
			epoll_ctl(_epfd, EPOLL_CTL_DEL, _fd, &_events[i]);
			return ;
		}
	}
	else if (byte == 0){
		std::cerr << "Connection closed on fd " << _fd << std::endl;
		close(_fd);
		epoll_ctl(_epfd, EPOLL_CTL_DEL, _fd, &_events[i]);
		return ;
	}
	std::cout << "Reciver from " << _fd << std::endl << buf;
	// if (_i % 2 == 0)
	// 	event_epollout(_fd);
	// _i ++;
}

void	Socket::send_fd(int i){
	ssize_t	byte;
	_fd = _events[i].data.fd;
	std::string  buf = "BAKA\n";
	byte = send(_fd, buf.c_str(), buf.size(), 0);
	if (byte == -1){
		if (errno == EAGAIN)
			std::cerr << "Send Would block on fd " << _fd << std::endl;
		else{
		std::cerr << "Send error on fd " << _fd << std::endl;
			close(_fd);
			epoll_ctl(_epfd, EPOLL_CTL_DEL, _fd, &_events[i]);
			return ;
		}
	}
	else if (byte > 0)
		event_epollin(_fd);
}
