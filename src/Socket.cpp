/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:59:15 by latahbah          #+#    #+#             */
/*   Updated: 2023/09/22 15:53:31 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket(const char *port)
{
    std::cout<<"  Setting up socket..."<<std::endl; 
	//Set up hints to find all addresses to add to socket
	struct addrinfo hints;
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_INET;    /* allow IPv4 only*/
    hints.ai_socktype = SOCK_STREAM;/* Stream socket (TCP) */
    hints.ai_flags = AI_PASSIVE;    /* for wildcard IP address */
	struct addrinfo *result;		/* starting rointer for getaddrinfo return structsv*/
	int s;
    std::cout<<"  Binding with port "<<port<<"\n";
	if ((s = getaddrinfo (NULL, port, &hints, &result)) != 0) {
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
    std::cout<<"  Socket is ready for connection."<<std::endl;
}

Socket::~Socket()
{
    if (close(listener) == -1) {
        perror("Close error\n");
        exit(EXIT_FAILURE);
	}
}

int Socket::get_listener()
{
	return listener;
}