/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:44:42 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/14 11:50:34 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"

WebServer::WebServer(string &config)
{
	//erase comms + split servers
	erase_comments(config);
	split_servers(config);
	//if some invalid servers didnt write - throw exc
	if (server_config.size() != server_num)
		throw runtime_error("Somthing with size"); //rewrite the sentence
	
	//we continue ONLY if we have atleast 1 server in servers vector
	// if (servers.empty())
	// 	std::cout<<"Error: no valid server configs"<<std::endl; // TODO: need to hanlde properly
	// else
	// 	cout<<"Server number is "<<servers.size()<<endl;
	

	
	// listener = websocket.get_listener();
	// if ((pollfds = (struct pollfd *)malloc(NUM_FDS * sizeof (struct pollfd))) == NULL){
	// 	perror("*Poolfds malloc error\n");
	// 	exit(EXIT_FAILURE);
	// }
	// pollfds -> fd = listener;
    // pollfds -> events = POLLIN;
    // pollfds -> revents = 0;
	// nfds = 1;
}

/**************************************************
 * 
 *	Erase_comments() delete lines 
 *	with # at start from config
 *
**************************************************/
void WebServer::erase_comments(string &config)
{
	size_t pos;

	pos = config.find('#');
	while (pos != std::string::npos)
	{
		size_t pos_end;
		pos_end = config.find('\n', pos);
		config.erase(pos, pos_end - pos);
		pos = config.find('#');
	}
}

/**************************************************
 * 
 *	Split_servers() split config by server {...}
 *	and push them into vector of string
 *
**************************************************/
void WebServer::split_servers(std::string &config)
{
	size_t start = 0;
	size_t end = 1;

	if (config.find("server", 0) == string::npos)
		throw runtime_error("Server did not find");
	while (start != end && start < config.length())
	{
		start = find_start_server(start, config);
		end = find_end_server(start, config);
		if (start == end && !isspace(config[start]))
			throw runtime_error("problem with scope");
		server_config.push_back(config.substr(start, end - start + 1));
		server_num++;
		start = end + 1;
	}
}

/**************************************************
 * 
 *	Find_start_server() search for "server " and
 *	return the index of { start of server
 *
**************************************************/
size_t WebServer::find_start_server(size_t start, string &config)
{
	size_t i;

	for (i = start; config[i]; i++)
	{
		if (config[i] == 's')
			break ;
		if (!isspace(config[i]))
			throw runtime_error("Wrong character out of server scope{}");
	}
	if (!config[i])
		return (start);
	if (config.compare(i, 6, "server") != 0)
		throw runtime_error("Wrong character out of server scope{}");
	i += 6;
	while (config[i] && isspace(config[i]))
		i++;
	if (config[i] == '{')
		return (i);
	else
		throw runtime_error("Wrong character out of server scope{}");
}

/**************************************************
 * 
 *	Find_end_server() search for server end and
 *	return the index of } end of server
 *
**************************************************/
size_t WebServer::find_end_server(size_t start, string &config)
{
	size_t	i;
	size_t	scope;
	
	scope = 0;
	for (i = start + 1; config[i]; i++)
	{
		if (config[i] == '{')
			scope++;
		if (config[i] == '}')
		{
			if (!scope)
				return (i);
			scope--;
		}
	}
	return (start);
}


/*
void WebServer::get_request(int client_fd)
{
	char buf[BUF_SIZE];
	ssize_t nbytes = recv(client_fd, buf, (size_t)BUF_SIZE, 0);
	if (nbytes < 0)
	{
		perror("recv error\n");
		exit(EXIT_FAILURE);
	}
	else if (nbytes > 0)
	{
		Request req(buf);
		if (!req.valid())
			return ;
		const char *response_message = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello, World";
		int message_len = strlen(response_message);
		
		int bytes_sent = send(client_fd, response_message, message_len, 0);
		if (bytes_sent == -1) {
			perror("Send error");
		} else {
			std::cout<<"\033[92m";
			std::cout<<"Sent "<<bytes_sent<<" bytes:"<<std::endl;
			std::cout<<response_message<<std::endl<<std::endl;
			std::cout<<RESET;
		}
	}
	else
	{
		// connection closed by client
		std::cout<<CYAN;
		std::cout<<"****************************************"<<std::endl;
		std::cout<<"*                                      *"<<std::endl;
		std::cout<<"*      Socket "<<client_fd<<" closed by client       *"<<std::endl;
		std::cout<<"*                                      *"<<std::endl;
		std::cout<<"****************************************"<<std::endl<<std::endl;
		std::cout<<RESET;
		if (close (client_fd) == -1)
		{
			perror("Close error\n");
			exit(EXIT_FAILURE);
		}
		client_fd *= -1; // make it negative so that it is ignored in future
	}
}

void WebServer::connect_client(int listener, struct pollfd *pollfds, int &numfds, int &maxfds)
{
	int fd_new;
	struct sockaddr_storage client_saddr;
	socklen_t addrlen;
	addrlen = sizeof (struct sockaddr_storage);
	//write address info about new client and its fd
	// if ((fd_new = accept (listener, (struct sockaddr *) &client_saddr, &addrlen)) == -1)
	if ((fd_new = accept(listener, (struct sockaddr *) &client_saddr, &addrlen)) == -1){
		perror("Accept error\n");
		exit(EXIT_FAILURE);
	}
	// add fd_new to pollfds
	if (numfds == maxfds) { // create space
		if ((pollfds = (struct pollfd *)realloc(pollfds, (maxfds + NUM_FDS) * sizeof (struct pollfd))) == NULL)
		{
			perror("Realloc error\n");
			exit(EXIT_FAILURE);
		}
		maxfds += NUM_FDS;
	}
	numfds++; //update counter of fds in pollfds
	//write info about fd in pollfds
	(pollfds + numfds - 1) -> fd = fd_new;
	(pollfds + numfds - 1) -> events = POLLIN;
	(pollfds + numfds - 1) -> revents = 0;
	connection_info(fd_new, client_saddr);
	
}

void WebServer::launch_server()
{
	std::cout<<"  Setting up server..."<<std::endl;
	//nfds_t nfds = 0; //number of pollfds structs passed in poll()
    int maxfds = NUM_FDS; //max fds is used to realloc pollfds array of structs
	int numfds = 1; //cur number of fds in pollfds (1 is because listener is already added in constructor

	std::cout<<GREEN;
	std::cout<<"[WEBSERV]Waiting for connections.."<<std::endl;
	std::cout<<RESET;
	while (true)
	{
		//update nfds to poll all fds in pollfds
		nfds = numfds;
		if (poll (pollfds, nfds, 1000) == -1){
			perror("Poll error\n");
			exit(EXIT_FAILURE);
		}
		//in cycle check for ready fds
		for (int fd = 0; fd < static_cast<int>(nfds + 1); fd++)
		{
			if ((pollfds + fd) -> fd <= 0) //if fd < 0 - it is inactive
				continue;
			//flag POLLIN means fd ready for reading
			if (((pollfds + fd) -> revents & POLLIN) == POLLIN)
			{
				if ((pollfds + fd) -> fd == listener) // request for new connection
				{
                    connect_client(listener, pollfds, numfds, maxfds);
                }
				else //getting info from connection
				{
					get_request((pollfds + fd)->fd); // TODO: split it to get_request->parse_reqiest->send response
				}
			}
		}
	}
}

void WebServer::connection_info(int client_fd, struct sockaddr_storage client_saddr)
{
	struct sockaddr_in  *ptr;
	char ip_address [INET_ADDRSTRLEN];
	ptr = (struct sockaddr_in *) &client_saddr;
	inet_ntop(AF_INET, &(ptr -> sin_addr), ip_address, sizeof (ip_address));
	std::cout<<GREEN;
	std::cout<<std::endl<<"****************************************"<<std::endl;
	std::cout<<"*                                      *"<<std::endl;
	std::cout<<"*        Open new socket fd: "<<client_fd<<"         *"<<std::endl;
	std::cout<<"*                                      *"<<std::endl;
	std::cout<<"*  Connection from client: "<<ip_address<<"   *"<<std::endl;
	std::cout<<"*                                      *"<<std::endl;
	std::cout<<"****************************************"<<std::endl<<std::endl;
	std::cout<<RESET;
}

WebServer::~WebServer()
{
	for (int fd = 0; fd < static_cast<int>(nfds + 1); fd++)
	{
		int cur_fd = (pollfds + fd)->fd;
		if (cur_fd > 0)
			close(fd);
	}
}

*/