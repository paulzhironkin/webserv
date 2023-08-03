/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:44:42 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/03 13:26:58 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() : websocket()//, clients()
{
}

void Server::get_request(int client_fd)
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
		std::cout<<buf<<std::endl;
		const char *response_message = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello, World";
		int message_len = strlen(response_message);
		
		int bytes_sent = send(client_fd, response_message, message_len, 0);
		if (bytes_sent == -1) {
			perror("Send error");
		} else {
			printf("Sent %d bytes: %s\n", bytes_sent, response_message);
		}
	}
	else
	{
		// connection closed by client
		printf("Socket %d closed by client\n\n", client_fd);
		if (close (client_fd) == -1)
		{
			perror("Close error\n");
			exit(EXIT_FAILURE);
		}
		client_fd *= -1; // make it negative so that it is ignored in future
	}
}

void Server::connect_client(int listener, struct pollfd *pollfds, int &numfds, int &maxfds)
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

void Server::launch_server()
{
	int listener = websocket.get_listener();
	nfds_t nfds = 0; //number of pollfds structs passed in poll()
    struct pollfd *pollfds; //structs with fd and events to check for ready to work
    int maxfds = 0; //max fds is used to realloc pollfds array of structs
	int numfds = 0; //cur number of fds in pollfds
	
	if ((pollfds = (struct pollfd *)malloc(NUM_FDS * sizeof (struct pollfd))) == NULL){
		perror("*Poolfds malloc error\n");
		exit(EXIT_FAILURE);
	}
    maxfds = NUM_FDS; //update maxfds to check later whether *pollfds is full or not 
	//Add listener to poll
	pollfds -> fd = listener;
    pollfds -> events = POLLIN;
    pollfds -> revents = 0;
    numfds = 1; // update number of fds in pollfds
	
	//Vars for client address info
	// socklen_t addrlen;
    // struct sockaddr_storage client_saddr;
    // char str [INET6_ADDRSTRLEN];
    // struct sockaddr_in  *ptr;
    // struct sockaddr_in6  *ptr1;

	while (true)
	{
		//update nfds to poll all fds in pollfds
		nfds = numfds;
		if (poll (pollfds, nfds, 1000) == -1){
			perror("Poll error\n");
			exit(EXIT_FAILURE);
		}
		//in cycle check for ready fds
		for (int fd = 0; fd < (nfds + 1); fd++)
		{
			int cur_fd = (pollfds + fd)->fd;
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
					get_request((pollfds + fd)->fd); /* TODO: split it to get_request->parse_reqiest->send response  */
				}
			}
		}
	}
}

void Server::connection_info(int client_fd, struct sockaddr_storage client_saddr)
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