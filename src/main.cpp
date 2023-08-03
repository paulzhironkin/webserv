/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:57:50 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/03 13:51:08 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Socket.hpp"
#include "Server.hpp"

int main()
{
	std::cout<<GREEN;
	std::cout<<"[WEBSERV] is starting..."<<std::endl;
	std::cout<<RESET;
	Server webserv;
	webserv.launch_server();
	return 0;
}