/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:45:03 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/10 11:41:34 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "Client.hpp"
#include "Request.hpp"
#include "Server.hpp"
#include <vector>

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
	vector<Server> servers; //if size == 0 there is no servers and return
	struct pollfd *pollfds;
	nfds_t nfds;
	void connect_client(int listener, struct pollfd *pollfds, int &numfds, int &maxfds);
	void get_request(int client_fd);
	void connection_info(int client_fd, struct sockaddr_storage client_saddr);
public:
	WebServer(string config);
	void launch_server();
	~WebServer(); //free struct pollfds
};

#endif