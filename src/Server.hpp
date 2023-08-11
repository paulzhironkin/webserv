/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:12:28 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/11 12:47:54 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include "Socket.hpp"
#include <string>
#include <utility>
#include <sstream>
#include <dirent.h>

using namespace std;

typedef struct Location {
	string resource; 					// resource in location description
	string try_files;					// need to parse it also
	vector<string> allowed_methods; 	// methods allow to recieve
	string redirection_path; 			// path for redirection
	string root;						// optional, if not use main root in server
	int autoindex; 						// 0 - OFF , 1 - ON
}	Location_t;

class Server
{
public:
	vector<Socket> sockets; 			// vector of sockets for the server
	vector<int> listeners; 				// vector of open fds for the server
	vector<string> server_names; 		// could be or not
	vector<pair<int, string>> port_host;// host:port storage
	string root;						// root directory to find files out
	vector<string> indexes; 						// main page
	string default_error_page; 			// defualt error page
	int max_client_body; 				// max size for body in request
	vector<Location_t> locations;		// vector of loactions
	
	Server(string server_config);
private:
	void set_server_names(string line);
	void set_port_host(string line);
	void set_root(string line);
	void set_index(string index);

	
	
	
	string removeLeadingWhitespaces(const std::string& input);
	vector<string> get_tokens(string line); // solit line by words
	
	//need add method to check mandatory fileds is filled
};

#endif