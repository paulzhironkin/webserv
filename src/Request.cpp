/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:42:47 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/09 15:33:03 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

// Request::Request(std::string text)
// {
// 	isValid = true;
// 	std::size_t index;
// 	//parsing first line
// 	index = text.find("\r\n");
// 	check_index(index);
// 	std::string request_line = text.substr(0, index + 2);
// 	parse_request_line(request_line);
// 	text.erase(0, index + 2);
// 	//parsing headers
// 	std::string head_break = "\r\n\r\n";
// 	index = text.find(head_break);
// 	check_index(index);
// 	std::string text_headers;
// 	text_headers = text.substr(0, index + 2);
// 	parse_headers(text_headers);
// 	text.erase(0,index + 4);
// 	//parsing body
// 	body = text.substr();
// 	print_info();
// }

// void Request::parse_request_line(std::string request_line)
// {
// 	std::size_t index;
// 	index = request_line.find(" ");
// 	check_index(index);
// 	type = request_line.substr(0, index);
// 	request_line.erase(0, index + 1);
// 	index = request_line.find(" ");
// 	check_index(index);
// 	resource = request_line.substr(0, index);
// 	request_line.erase(0, index + 1);
// 	index = request_line.find("\r\n");
// 	check_index(index);
// 	protocol = request_line.substr(0, index);
// }

// void Request::parse_headers(std::string str)
// {
// 	std::size_t index;
// 	std::size_t colon_index;
// 	std::string header;
// 	std::string key;
// 	std::string value;
// 	while (str.size())
// 	{
// 		index = str.find("\r\n");
// 		check_index(index);
// 		header = str.substr(0, index);
// 		colon_index = header.find(":");
// 		check_index(colon_index);
// 		key = header.substr(0, colon_index);
// 		value = header.substr(colon_index + 2, index);
// 		headers[key] = value;
// 		str.erase(0, index + 2);
// 	}
// }

// void Request::check_index(std::size_t index)
// {
// 	if (index == std::string::npos)
// 		isValid = false;
// }

// //================ GETTERS =====================//
 
// std::string Request::get_type()
// {
// 	return type;
// }
// std::string Request::get_resource()
// {
// 	return resource;
// }
// std::string Request::get_protocol()
// {
// 	return protocol;
// }

// std::map<std::string, std::string> Request::get_headers()
// {
// 	return headers;
// }

// std::string Request::get_header_value(std::string key)
// {
// 	std::map<std::string, std::string>::iterator it = headers.find(key);
// 	if (it != headers.end())
// 		return it->second;
// 	else
// 		return NULL;
// }

// std::string Request::get_body()
// {
// 	return body;
// }

// bool Request::valid()
// {
// 	return isValid;
// }


#include "Request.hpp"

#include <vector>
#include <sstream>

Request::Request(const char* request_data) {
    parse(request_data);
}

bool Request::valid() const {
    return !method.empty() && !path.empty() && !http_version.empty();
}

std::string Request::getMethod() const {
    return method;
}

std::string Request::getPath() const {
    return path;
}

std::string Request::getHTTPVersion() const {
    return http_version;
}

std::string Request::getHeader(const std::string& header_name) const {
    std::map<std::string, std::string>::const_iterator it = headers.find(header_name);
    if (it != headers.end()) {
        return it->second;
    }
    return "";
}

std::string Request::getBody() const {
    return body;
}

int Request::getPort() const {
    return port;
}

void Request::parse(const char* request_data) {
	parsePort(request_data);
    // Разбиваем запрос по строкам
    std::vector<std::string> lines;
    std::string request_str(request_data);
    size_t start = 0;
    size_t end = request_str.find("\r\n");
    while (end != std::string::npos) {
        lines.push_back(request_str.substr(start, end - start));
        start = end + 2; // Пропускаем \r\n
        end = request_str.find("\r\n", start);
    }

    // Парсим первую строку запроса (метод, путь и версия HTTP)
    if (lines.size() > 0) {
        std::string first_line = lines[0];
        size_t space1 = first_line.find(' ');
        size_t space2 = first_line.find(' ', space1 + 1);
        if (space1 != std::string::npos && space2 != std::string::npos) {
            method = first_line.substr(0, space1);
            path = first_line.substr(space1 + 1, space2 - space1 - 1);
            http_version = first_line.substr(space2 + 1);
        }
    }

    // Парсим заголовки
    for (size_t i = 1; i < lines.size(); ++i) {
        size_t colon_pos = lines[i].find(':');
        if (colon_pos != std::string::npos) {
            std::string header_name = lines[i].substr(0, colon_pos);
            std::string header_value = lines[i].substr(colon_pos + 2); // Пропускаем двоеточие и пробел
            headers[header_name] = header_value;
        }
    }

    // Парсим тело запроса
    size_t body_start = request_str.find("\r\n\r\n");
    if (body_start != std::string::npos && body_start + 4 < request_str.size()) {
        body = request_str.substr(body_start + 4);
    }
}

void Request::parsePort(const char* request_data) {
    // Парсим порт из запроса
    const char* port_start = std::strstr(request_data, "Host: ");
    if (port_start != NULL) {
        port_start += 6; // Пропускаем "Host: "
        const char* port_end = std::strchr(port_start, ':');
        if (port_end != NULL) {
            std::string port_str(port_start, port_end);
            int port = std::atoi(port_str.c_str());
        }
    }
}
//================ Print info about request =====================//

void Request::print_info()
{
	std::cout<<"Client request:"<<std::endl<<std::endl;
	std::cout<<RED;
	std::cout<<"Request line: "<<std::endl;
	std::cout<<"Type:     ["<<method<<"]"<<std::endl;
	std::cout<<"Resource: ["<<path<<"]"<<std::endl;
	std::cout<<"Protocol: ["<<http_version<<"]"<<std::endl<<std::endl;
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