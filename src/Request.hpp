/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:30:07 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/15 18:22:34 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <map>
#include <string>
#include <cstring>
#include <cstdlib>
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

// class Request
// {
// private:
// 	std::string type;
// 	std::string resource;
// 	std::string protocol;
// 	std::map<std::string, std::string> headers;
// 	std::string body;
// 	bool isValid;
// 	void parse_request_line(std::string request_line);
// 	void parse_headers(std::string text_headers);
// 	void check_index(std::size_t index);
// public:
// 	Request(std::string text);
// 	std::string get_type();
// 	std::string get_resource();
// 	std::string get_protocol();
// 	std::map<std::string, std::string> get_headers();
// 	std::string get_header_value(std::string key);
// 	std::string get_body();
// 	bool valid();
// 	void print_info();
// };


class Request 
{
	private:
		std::string method;
		std::string path;
		std::string http_version;
		std::map<std::string, std::string> headers;
		std::string body;
		int port;
		void parse(const char* request_data);
		void parsePort(const char* request_data);


	public:
		Request(const char* request_data);
		bool valid() const;
		std::string getMethod() const;
		std::string getPath() const;
		std::string getHTTPVersion() const;
		std::string getHeader(const std::string& header_name) const;
		std::string getBody() const;
		int getPort() const;

		void print_info();
};



#endif