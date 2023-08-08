/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:42:47 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/08 21:27:30 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request(std::string text)
{
	std::cout<<"==============================\n";
	std::size_t index;
	index = text.find("\r\n");
	if (index == std::string::npos)
		perror("Ivalid request - no first line\n"); //TODO: handle invalid 
	request_line = text.substr(0,index); //TODO: check on invalid first line
	type = request_line.substr(0, request_line.find(" "));
	request_line.erase(0, request_line.find(" ") + 1);
	resource = request_line.substr(0, request_line.find(" "));
	request_line.erase(0, request_line.find(" ") + 1);
	protocol = request_line.substr();
	text.erase(0,index + 2);
	std::string head_break = "\r\n\r\n";
	index = text.find(head_break);
	if (index == std::string::npos)
		perror("Ivalid request - no empty line after header\n"); //TODO: handle invalid
	std::string text_headers; //tmp string to parse into map
	// std::cout<<"index - "<<index<<std::endl;
	text_headers = text.substr(0, index);
	text.erase(0,index + 4);
	body = text.substr();
	print_info();
	exit(EXIT_SUCCESS);
}

std::string Request::get_request_line()
{
	return request_line;
}

std::map<std::string, std::string> Request::get_headers()
{
	return headers;
}

std::string Request::get_header_value(std::string key)
{
	std::map<std::string, std::string>::iterator it = headers.find(key);
	if (it != headers.end())
		return it->second;
	else
		return NULL;
}

std::string Request::get_body()
{
	return body;
}

void Request::print_info()
{
	std::cout<<RED;
	std::cout<<"Type: ["<<type<<"]"<<std::endl;
	std::cout<<"Resource: ["<<resource<<"]"<<std::endl;
	std::cout<<"Protocol: ["<<protocol<<"]"<<std::endl<<std::endl;
	// std::cout<<YELLOW;
	// std::cout<<"Headers: ["<<text_headers<<"]"<<std::endl<<std::endl;
	// std::cout<<CYAN;
	// std::cout<<"Body: ["<<text<<"]"<<std::endl;
	std::cout<<RESET;
}