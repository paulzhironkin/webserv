/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:44:42 by latahbah          #+#    #+#             */
/*   Updated: 2023/10/20 16:10:53 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"

WebServer::WebServer(std::vector<ServerConfig> input_servers) : servers(input_servers)
{
	nfds = 0;
	maxfds = NUM_FDS;
	if ((pollfds = (struct pollfd *)malloc((servers.size() + NUM_FDS) * sizeof (struct pollfd))) == NULL){
		perror("*Poolfds malloc error\n");
		exit(EXIT_FAILURE);
	}
	for (size_t i = 0; i < servers.size(); ++i)
	{
		uint16_t tmp = servers[i].getPort();
		char buffer[7];
		snprintf(buffer, sizeof(buffer), "%u", tmp);
		const char *port = buffer;
		Socket *new_socket = new Socket(port);
		websockets.push_back(new_socket);
		
		int listener = new_socket->get_listener();
		(pollfds + i) -> fd = listener;
		(pollfds + i) -> events = POLLIN;
		(pollfds + i) -> revents = 0;
		nfds += 1;
	}
	
}

void WebServer::launch_server()
{
	std::cout<<GREEN;
	std::cout<<"[WEBSERV]Waiting for connections.."<<std::endl;
	std::cout<<RESET;
	while (true)
	{
		//update nfds to poll all fds in pollfds
		if (poll (pollfds, nfds, 1000) == -1){
			perror("Poll error\n");
			exit(EXIT_FAILURE);
		}
		//in cycle check for ready fds
		for (int fd = 0; fd < static_cast<int>(nfds + 1); fd++)
		{
			if ((pollfds + fd) -> fd <= 0) //if fd < 0 - it is inactive
				continue;
			//flag POLLIN means fd ready for reading
			if (((pollfds + fd)->revents & POLLIN))
			{
				// request for new connection: check if fd from socket
				if ((pollfds + fd) -> fd < (int)servers.size() + 3)
				{
                    connect_client((pollfds + fd) -> fd, pollfds, nfds);
                }
				else //getting info from connection: if fd from client
				{
					get_request((pollfds + fd)->fd); // TODO: split it to get_request->parse_reqiest->send response
					send_response((pollfds + fd)->fd);
				}
			}
		}
	}
}

void WebServer::get_request(int client_fd)
{
	std::cout<<"\tget request...\n";
	ssize_t nbytes = recv(client_fd, buf, (size_t)BUF_SIZE, 0);
	if (nbytes <= 0)
	{
		perror("recv error\n");
		exit(EXIT_FAILURE);
	}
}

void WebServer::send_response(int client_fd)
{
	
	Request req(buf);
	Response resp(200);

	if (!req.valid()){
		resp.set_status(404);
		resp.set_content_type("text/html");
		resp.set_body("Poshel nahui REQ IS INVALID");
		// return ;
	} else {
		req.print_info();
		resp.set_content_type("text/html");
		ServerConfig serverConfig = getServerConfigByPort(req.getPort());
		if (!serverConfig.getRoot().empty()) // Проверка на пустой сервер
		{

			// Загрузка содержимого indexPage и установка его как тела ответа
			std::string content = responseContent(req, serverConfig);
			resp.set_body(content);
		} else {
			resp.set_body("Invalid server configuration(Poshel nahyi)");
		}
	}	
	
	std:: string response_message = resp.generate_response();
	int message_len = strlen(response_message.c_str());
	int bytes_sent = send(client_fd, response_message.c_str(), message_len, 0);
	if (bytes_sent == -1) {
		perror("Send error");
	} else {
		std::cout<<"\033[92m";
		std::cout<<"Sent "<<bytes_sent<<" bytes:"<<std::endl;
		std::cout<<response_message<<std::endl<<std::endl;
		std::cout<<RESET;
		std::cout<<CYAN;
		std::cout<<"****************************************"<<std::endl;
		std::cout<<"*                                      *"<<std::endl;
		std::cout<<"*      Socket "<<client_fd<<" closed       *"<<std::endl;
		std::cout<<"*                                      *"<<std::endl;
		std::cout<<"****************************************"<<std::endl<<std::endl;
		std::cout<<RESET;
		if (close (client_fd) == -1)
		{
			perror("Close error\n");
			exit(EXIT_FAILURE);
		}
		client_fd *= -1;
	}
}

void WebServer::connect_client(int listener, struct pollfd *pollfds, nfds_t &nfds)
{
	std::cout<<"\tconnect client...\n";
	int fd_new;
	struct sockaddr_storage client_saddr;
	socklen_t addrlen;
	addrlen = sizeof (struct sockaddr_storage);
	//write address info about new client and its fd
	// if ((fd_new = accept (listener, (struct sockaddr *) &client_saddr, &addrlen)) == -1)
	if ((fd_new = accept(listener, (struct sockaddr *) &client_saddr, &addrlen)) == -1){
		perror("Accept error\n");
		exit(EXIT_FAILURE);
	}
	// add fd_new to pollfds
	if ((int)nfds == maxfds) { // create space
		if ((pollfds = (struct pollfd *)realloc(pollfds, (maxfds + NUM_FDS) * sizeof (struct pollfd))) == NULL)
		{
			perror("Realloc error\n");
			exit(EXIT_FAILURE);
		}
		maxfds += NUM_FDS;
	}
	nfds++; //update counter of fds in pollfds
	//write info about fd in pollfds
	(pollfds + (int)nfds - 1) -> fd = fd_new;
	(pollfds + (int)nfds - 1) -> events = POLLIN;
	(pollfds + (int)nfds - 1) -> revents = 0;
	connection_info(fd_new, client_saddr);
}



void WebServer::connection_info(int client_fd, struct sockaddr_storage client_saddr)
{
	struct sockaddr_in  *ptr;
	char ip_address [INET_ADDRSTRLEN];
	ptr = (struct sockaddr_in *) &client_saddr;
	inet_ntop(AF_INET, &(ptr -> sin_addr), ip_address, sizeof (ip_address));
	std::cout<<GREEN;
	std::cout<<std::endl<<"****************************************"<<std::endl;
	std::cout<<"*                                      *"<<std::endl;
	std::cout<<"*        Open new socket fd: "<<client_fd<<"         *"<<std::endl;
	std::cout<<"*                                      *"<<std::endl;
	std::cout<<"*  Connection from client: "<<ip_address<<"   *"<<std::endl;
	std::cout<<"*                                      *"<<std::endl;
	std::cout<<"****************************************"<<std::endl<<std::endl;
	std::cout<<RESET;
}

WebServer::~WebServer()
{
	size_t socket_num = websockets.size();
	for (size_t i = 0; i < socket_num; ++i)
		delete websockets[i];
		
	for (int fd = 0; fd < static_cast<int>(nfds + 1); fd++)
	{
		int cur_fd = (pollfds + fd)->fd;
		if (cur_fd > 0)
			close(fd);
	}
}

ServerConfig WebServer::getServerConfigByPort(int port) const {

    for (size_t i = 0; i < servers.size(); ++i) {
    	const ServerConfig& serverConfig = servers[i];
        if (serverConfig.getPort() == port) {
            return serverConfig; // Возвращаем копию объекта
        }
    }
    // Возвращаем пустой объект ServerConfig, если не нашли
    return ServerConfig();
}

std::string WebServer::responseContent(Request& req, const ServerConfig& serverConfig) const {
	std::string content;
	if (req.getMethod()=="GET")
		return loadIndexContent(req,serverConfig);
	else if (req.getMethod()=="POST")
		content = "post";
	else if (req.getMethod()=="PUT")
		content = "put";
	else //DELETE
		content = "del";
	return content;
}

std::string WebServer::loadIndexContent(Request& req, const ServerConfig& serverConfig) const {
    ServerConfig nonConstServerConfig = serverConfig; // Создаем неконстантную копию объекта
    std::string indexPath = nonConstServerConfig.getRoot() + nonConstServerConfig.getIndex();

	if (req.getPath() != "/"){
		const std::vector<Location> locations = nonConstServerConfig.getLocations();
		int matches = 0;
		Location matchedLocation;
		for (size_t i = 0; i < locations.size(); ++i) {
			const Location& location = locations[i];
			if (pathMatch(location.getPath(), req.getPath()) > matches) {
				matches = pathMatch(location.getPath(), req.getPath());
				matchedLocation = location;
			}
   		}
		if (matches != 0){
			std::cout << "MATCHES for '"<<req.getPath()<< "' and '"<<matchedLocation.getPath()<<"': " << matches << std::endl;
			indexPath = matchedLocation.getRootLocation() + matchedLocation.getIndexLocation();
		}
	} 
	std::cout << "indexPath = "<< indexPath << std::endl;	
	std::ifstream indexFile(indexPath.c_str());
    if (indexFile) {
        std::stringstream buffer;
        buffer << indexFile.rdbuf();
        return buffer.str();
    }
    return ""; // Возвращаем пустую строку в случае ошибки чтения файла
}

