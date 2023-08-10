/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:57:50 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/10 11:41:47 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include "WebServer.hpp"



int main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::ifstream config_file(argv[1]);
		if (config_file.is_open())
		{
			std::string config;
			while (std::getline(config_file, config)) {}
			config_file.close();
			std::cout<<GREEN;
			std::cout<<"[WEBSERV] is starting..."<<std::endl;
			std::cout<<RESET;
			WebServer webserv(config);
			webserv.launch_server();
    	}
		else 
		{
        	std::cout << "Error: Failed to open the file for reading." << std::endl;
			return 1;
    	}
	}
	else
		std::cout<<"Error: invalid number of argument."<<std::endl;
	return 0;
}