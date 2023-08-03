/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:57:50 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/03 09:52:38 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Socket.hpp"
#include "Server.hpp"

int main()
{
	Server webserv;
	webserv.launch_server();
	return 0;
}