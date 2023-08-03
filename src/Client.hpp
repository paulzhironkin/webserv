/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:14:17 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/03 12:13:03 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct client_data {
	char request_text[10000]; //need to make it dynamical and strings type
};

class Client
{
private:
	int client_fd;
	struct sockaddr_storage client_saddr;
	socklen_t addrlen;
	struct client_data data;
public:
	Client();
	int get_fd();
	void set_fd(int new_fd);
	struct client_data get_client_data();
	struct sockaddr_storage get_saddr();
	socklen_t get_addrlen();
};

#endif