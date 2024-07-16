#include "../includes/all.hpp"

std::vector<std::pair<std::string, int>>	exec_com(std::string com, int fd, Server server) {


}

int main(){
	std::string com = "JOIN #aa ~~~";
	int fd = 0;
	Server server;
	Command command;

	command.exec_cmd(com, server.fd2User(fd), server);
}