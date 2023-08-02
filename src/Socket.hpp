/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:31:45 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/03 00:04:15 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <errno.h>
#include <syslog.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>
#include <time.h>
#include <iostream>

#define PORT		"4242"	//port to connect. It's extracted from serv config
#define BUF_SIZE	10000
#define BACKLOG		10 		// Max num of connections on socket
#define NUM_FDS		5		//Number of checking fds

class Socket
{
private:
	int listener;		//fd for socket
public:
	Socket();
	void create_pull();
	int get_listener();
};

#endif