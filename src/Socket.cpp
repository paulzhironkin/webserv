/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:59:15 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/03 00:46:56 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket()
{
	//Set up hints to find all addresses to add to socket
	struct addrinfo hints;
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM;/* Stream socket (TCP) */
    hints.ai_flags = AI_PASSIVE;    /* for wildcard IP address */
	struct addrinfo *result;		/* starting rointer for getaddrinfo return structsv*/
	int s;
	if ((s = getaddrinfo (NULL, PORT, &hints, &result)) != 0) {
        perror("Getaddrinfo error\n");
        exit (EXIT_FAILURE);
    }
	//socklen_t length;
    struct addrinfo *rptr; //cycle iterator in addrinfo structs
	for (rptr = result; rptr != NULL; rptr = rptr -> ai_next) {
        listener = socket (rptr -> ai_family, rptr -> ai_socktype,
                       rptr -> ai_protocol);
        if (listener == -1)
            continue;

        if (bind(listener, rptr -> ai_addr, rptr -> ai_addrlen) == 0)  // Success
            break;

        if (close(listener) == -1) {
			perror("Close error\n");
			exit(EXIT_FAILURE);
		}
    }
	if (rptr == NULL) {               // Not successful with any address
        perror("Bind error\n");
        exit(EXIT_FAILURE);
    }
    freeaddrinfo (result);
	//Activate socket for listening
	if (listen (listener, BACKLOG) == -1) {
		perror("Listen error\n");
		exit(EXIT_FAILURE);
	}
	//test
	// int new_socket;
	// while(1)
    // {
    //     struct sockaddr_storage client_addr; // Address structure to store client information
    // 	socklen_t client_addr_len = sizeof(client_addr); // Initialize the size of the address structure

	// 	// Accept incoming connections
	// 	int new_socket = accept(listener, (struct sockaddr*)&client_addr, &client_addr_len);
	// 	if (new_socket < 0) {
	// 		perror("In accept");
	// 		exit(EXIT_FAILURE);
    // 	}
        
    //     char buffer[30000] = {0};
	// 	int valread;
    //     valread = read( new_socket , buffer, 30000);
    //     printf("%s\n",buffer );
    //     close(new_socket);
    // }
}

void Socket::create_pull()
{
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
	socklen_t addrlen;
    struct sockaddr_storage client_saddr;
    char str [INET6_ADDRSTRLEN];
    struct sockaddr_in  *ptr;
    struct sockaddr_in6  *ptr1;

	while (true)
	{
		//update nfds to poll all fds in pollfds
		nfds = numfds;
		if (poll (pollfds, nfds, 1000) == -1){
			perror("Poll error\n");
			exit(EXIT_FAILURE);
		}
		//in cycle check for ready fds
		for (int fd = 0; fd < (nfds + 1); fd++) {
			int cur_fd = (pollfds + fd)->fd;
			if ((pollfds + fd) -> fd <= 0) //if fd < 0 - it is inactive
				continue;
			//flag POLLIN means fd ready for reading
			if (((pollfds + fd) -> revents & POLLIN) == POLLIN)
			{
				if ((pollfds + fd) -> fd == listener) // request for new connection
				{
                    addrlen = sizeof(struct sockaddr_storage); //addrlen to pass to accept
					// fd_new to accept() to get client fd
                    int fd_new;
					//write address info about new client and its fd
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
					std::cout<<"Open new socket fd:"<<fd_new<<std::endl;
                    numfds++; //update counter of fds in pollfds
					//write info about fd in pollfds
		    		(pollfds + numfds - 1) -> fd = fd_new;
                    (pollfds + numfds - 1) -> events = POLLIN;
                    (pollfds + numfds - 1) -> revents = 0;
                }
				else //getting info from connection
				{
					char buf[BUF_SIZE];
					ssize_t nbytes = recv((pollfds + fd)->fd, buf, (size_t)BUF_SIZE, 0);
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
						
						int bytes_sent = send(cur_fd, response_message, message_len, 0);
						if (bytes_sent == -1) {
							perror("Send error");
						} else {
							printf("Sent %d bytes: %s\n", bytes_sent, response_message);
						}
					}
					else
					{
                        // connection closed by client
						printf("Socket %d closed by client\n\n", (pollfds + fd) -> fd);
						if (close ((pollfds + fd) -> fd) == -1)
                        {
							perror("Close error\n");
							exit(EXIT_FAILURE);
						}
						(pollfds + fd) -> fd *= -1; // make it negative so that it is ignored in future
                    }
				}
			}
		}
		// std::cout<<"\nNumber of fds in pollfds: "<<numfds<<std::endl;
	}
	
}

int Socket::get_listener()
{
	return listener;
}