/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:59:15 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/03 09:52:15 by latahbah         ###   ########.fr       */
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
}

int Socket::get_listener()
{
	return listener;
}