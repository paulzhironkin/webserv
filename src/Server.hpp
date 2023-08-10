/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:12:28 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/10 11:36:54 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include "Socket.hpp"
#include <string>
#include <utility>

using namespace std;

typedef struct Location {
	string resource; 					//resource in location description
	string try_files;					// need to parse it also
	vector<string> allowed_methods; 	//methods allow to recieve
	string redirection_path; 			//path for redirection
	string root;						//optional, if not use main root in server
	int autoindex; 						// 0 - OFF , 1 - ON
}	Location_t;

class Server
{
public:
	vector<Socket> sockets; 			//vector of sockets for the server
	vector<int> listeners; 				//vector of open fds for the server
	string server_name; 				// could be or not
	vector<pair<int, string> > port_host;//host:port storage
	string root;						//root directory to find files out
	string index; 						//main page
	string default_error_page; 			//defualt error page
	int max_client_body; 				//max size for body in request
	vector<Location_t> locations;		//vector of loactions
	
	Server();
	
	//need add method to check mandatory fileds is filled
};

#endif