/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:57:50 by latahbah          #+#    #+#             */
/*   Updated: 2023/09/22 15:12:13 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include "WebServer.hpp"
#include "ConfigParser.hpp"


int main(int argc, char **argv)
{
	if (argc == 2)
	{
		try {
			std::string		config;
			ConfigParser cluster;
			config = (argc == 1 ? "config			ConfigParser	cluster;s/default.conf" : argv[1]);
			cluster.createCluster(config);
			cluster.print();
			WebServer webserv(cluster.getServers());
			webserv.launch_server();
    	}
		catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
			return (1);
		}
		
	}
	else
		std::cout<<"Error: invalid number of argument."<<std::endl;
	return 0;
}