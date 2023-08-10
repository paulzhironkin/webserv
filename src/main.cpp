/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:57:50 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/10 09:09:49 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "WebServer.hpp"

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::cout<<argv[1];
		std::cout<<GREEN;
		std::cout<<"[WEBSERV] is starting..."<<std::endl;
		std::cout<<RESET;
		WebServer webserv;
		webserv.launch_server();
	}
	else
		std::cout<<"Error: invalid number of argument."<<std::endl;
	return 0;
}