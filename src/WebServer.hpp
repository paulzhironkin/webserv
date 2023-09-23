/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:45:03 by latahbah          #+#    #+#             */
/*   Updated: 2023/09/22 20:36:49 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP


#include "Client.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Socket.hpp"
#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <utility>
#include <sstream>
#include <dirent.h>
#include "Server.hpp"
#include "ConfigParser.hpp"
#include "ServerConfig.hpp"
#include "Location.hpp"
#include "ConfigFile.hpp"
#include <vector>
#include <cstdio>
// #include <cstdint>

// ANSI escape code for text colors
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

using namespace std;


class WebServer
{
private:
	std::vector<ServerConfig> servers;
	struct pollfd *pollfds;
	int		maxfds;
	std::vector<Socket *> websockets;
	nfds_t nfds;
	void connect_client(int listener, struct pollfd *pollfds, nfds_t &numfds);
	void get_request(int client_fd);
	void connection_info(int client_fd, struct sockaddr_storage client_saddr);
	ServerConfig getServerConfigByPort(int port) const;
	std::string loadIndexContent(const ServerConfig& serverConfig) const;
	
public:
	WebServer(std::vector<ServerConfig> configs);
	void launch_server();

// 	void erase_comments(string &config);
// 	void split_servers(string &config);
// 	size_t find_start_server(size_t start, string &config);
// 	size_t find_end_server (size_t start, string &config);
	~WebServer(); //free struct pollfds
};


#endif