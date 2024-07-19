#ifndef ALL_HPP
# define ALL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>

#include <cerrno>
#include <cstdio>
#include <cstdlib>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <algorithm>
#include <vector>

#include "User.hpp"
#include "Channel.hpp"
#include "Command.hpp"
#include "Server.hpp"
#include "irc.hpp"
#include "Socket.hpp"

#include "Commands/Nick.hpp"
#include "Commands/CUser.hpp"
#include "Commands/Invite.hpp"
#include "Commands/Join.hpp"
#include "Commands/Kick.hpp"
#include "Commands/Mode.hpp"
//#include "Commands/Part.hpp"
#include "Commands/Pass.hpp"
#include "Commands/Ping.hpp"
#include "Commands/Privmsg.hpp"
#include "Commands/Quit.hpp"
#include "Commands/Topic.hpp"
//#include "Commands/Who.hpp"
//#include "Commands/Whois.hpp"

//std::vector<std::pair<std::string, int> > t;

#endif