/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:30:07 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/08 21:26:08 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <map>
#include <string>
#include <iostream>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

class Request
{
private:
	std::string request_line;
	std::string type;
	std::string resource;
	std::string protocol;
	std::map<std::string, std::string> headers;
	std::string body;
public:
	Request(std::string text);
	std::string get_request_line();
	std::map<std::string, std::string> get_headers();
	std::string get_header_value(std::string key);
	std::string get_body();
	void print_info();
};

#endif