/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:21:08 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/03 12:13:10 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client()
{
	client_fd = 0;
	struct sockaddr_storage new_saddr;
	client_saddr = new_saddr;
	addrlen = sizeof(struct sockaddr_storage);
	struct client_data new_data;
	data = new_data;
}

int Client::get_fd()
{
	return client_fd;
}

struct client_data Client::get_client_data()
{
	return data;
}

struct sockaddr_storage Client::get_saddr()
{
	return client_saddr;
}

void Client::set_fd(int new_fd)
{
	client_fd = new_fd;
}

socklen_t Client::get_addrlen()
{
	return addrlen;
}