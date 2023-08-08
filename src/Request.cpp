/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:42:47 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/08 22:25:14 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request(std::string text)
{
	isValid = true;
	std::size_t index;
	//parsing first line
	index = text.find("\r\n");
	check_index(index);
	std::string request_line = text.substr(0, index + 2);
	parse_request_line(request_line);
	text.erase(0, index + 2);
	//parsing headers
	std::string head_break = "\r\n\r\n";
	index = text.find(head_break);
	check_index(index);
	std::string text_headers;
	text_headers = text.substr(0, index + 2);
	parse_headers(text_headers);
	text.erase(0,index + 4);
	//parsing body
	body = text.substr();
	print_info();
}

void Request::parse_request_line(std::string request_line)
{
	std::size_t index;
	index = request_line.find(" ");
	check_index(index);
	type = request_line.substr(0, index);
	request_line.erase(0, index + 1);
	index = request_line.find(" ");
	check_index(index);
	resource = request_line.substr(0, index);
	request_line.erase(0, index + 1);
	index = request_line.find("\r\n");
	check_index(index);
	protocol = request_line.substr(0, index);
}

void Request::parse_headers(std::string str)
{
	std::size_t index;
	std::size_t colon_index;
	std::string header;
	std::string key;
	std::string value;
	while (str.size())
	{
		index = str.find("\r\n");
		check_index(index);
		header = str.substr(0, index);
		colon_index = header.find(":");
		check_index(colon_index);
		key = header.substr(0, colon_index);
		value = header.substr(colon_index + 2, index);
		headers[key] = value;
		str.erase(0, index + 2);
	}
}

void Request::check_index(std::size_t index)
{
	if (index == std::string::npos)
		isValid = false;
}

//================ GETTERS =====================//
 
std::string Request::get_type()
{
	return type;
}
std::string Request::get_resource()
{
	return resource;
}
std::string Request::get_protocol()
{
	return protocol;
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

bool Request::valid()
{
	return isValid;
}

//================ Print info about request =====================//

void Request::print_info()
{
	std::cout<<"Client request:"<<std::endl<<std::endl;
	std::cout<<RED;
	std::cout<<"Request line: "<<std::endl;
	std::cout<<"Type: ["<<type<<"]"<<std::endl;
	std::cout<<"Resource: ["<<resource<<"]"<<std::endl;
	std::cout<<"Protocol: ["<<protocol<<"]"<<std::endl<<std::endl;
	std::cout<<YELLOW;
	std::cout<<"Headers:"<<std::endl;
	std::map<std::string, std::string>::iterator it;
    for (it = headers.begin(); it != headers.end(); ++it) {
        std::cout<<it->first << ": [" << it->second << "]"<< std::endl;
    }
	std::cout<<std::endl<<std::endl;
	std::cout<<CYAN;
	std::cout<<"Body:"<<std::endl<<"["<<body<<"]"<<std::endl;
	std::cout<<RESET;
}