/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:45:03 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/03 10:41:55 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Socket.hpp"

class Server
{
private:
	Socket websocket;
	void get_request(int client_fd);
	void connect_client(int listener, struct pollfd *pollfds, int &numfds, int &maxfds);
public:
	Server();
	void launch_server();
};

#endif