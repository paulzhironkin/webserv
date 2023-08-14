/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:12:14 by latahbah          #+#    #+#             */
/*   Updated: 2023/08/14 11:25:44 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(string server_config)
{
	//9 needs to cut "server {" + in the end "}" | size - 10 is length of string
	server_config = server_config.substr(9, server_config.size() - 10);
	// cout<<"\""<<server_config<<"\""<<endl;
	//split server_config by /n to lines and 
	istringstream iss(server_config);
    string line;
    vector<std::string> lines;

	//split by lines
    while (getline(iss, line)) {
		line = removeLeadingWhitespaces(line);
        lines.push_back(line);
    }
	
	for (int i = 0; i < (int)lines.size(); i++)
	{
		line = lines[i];
		//detecting type of string
		if (line.find("server_name") == 0) // need to check that only 1 time
			set_server_names(line);
		else if (line.find("listen") == 0)
			set_port_host(line);
		//unite lines if they are parts of location
		/*	rules for valid location line:
					- 3 tokens
					- first == "location"
					- last == "}"
		*/
		//location line should be only "location .... {"
		//location part should end with separate line "}"
		else if (line.find("location") == 0)
		{
			vector<string> tokens = get_tokens(line);
			if (tokens.size() != 3)
				perror("Error: invalid location line (token nums)..\n");
			if (tokens[0] != "location")
				perror("Error: invalid location line..\n");
			if (tokens[2] != "{")
				perror("Error: invalid syntax on location line..\n");
			int j = i+1;
			int isfound = 0;
			//searching for last line
			while (j < (int)lines.size())
			{
				if (lines[j] == "}")
				{
					isfound = 1;
					break;
				}
				j++;
			}
			//string where to sum all location lines
			string res;
			//if we found last location line, just to make location
			//in one string. and update i iterator
			if (isfound)
			{
				for (int k = i; k <=j; k++)
					res += lines[k];
				i = j + 1;
			}
			else
				perror("Error: syntax error in location..\n");
			Location_t new_loc;
			fill_location(new_loc, res);
			locations.push_back(new_loc);
		}
		
		//... somepoints
		//if smth bad and unrecognized - error
		else
			perror("Error: invalid line in config..\n");
	}





	

	// else if (line.find("root") == 0)
	// 		set_root(line);
	// 	else if (line.find("index") == 0)
	// 		set_index(line);
	// 	else if (line.find("default_error_page") == 0)
	// 		//cope with error page
	// 	else if (line.find("location") == 0)
	// 		//cope with location
	// 	else if (line.find("max_client_bodysize") == 0)
	// 		//cope with max_body size
	
}

/*============ Methods for parse and fill class vars ================*/

/**************************************************
 * 
 *	Fill_location recieves &location struct and 
 *	string line, parse line and fill vars 
 *	of location
 *
**************************************************/

void Server::fill_location(Location &loc, string loc_text)
{
	istringstream iss(loc_text);
    string line;
    vector<std::string> lines;

	//split location .. {...} by lines
    while (getline(iss, line)) {
		line = removeLeadingWhitespaces(line);
        lines.push_back(line);
    }
	//get resource from first line
	vector<string> tokens = get_tokens(lines[0]);
	loc.resource = tokens[1];
	
}


/**************************************************
 * 
 *	Set_server_names() parse needed string 
 *	and adds domains to server_names vector storage
 *
 *	Rules for set_server_name:
 *	- if server_name exists - it is error
 *		(should be unique line)
 *	- first is equal to "server_name"
 *
**************************************************/
void Server::set_server_names(string line)
{
	vector<string> tokens = get_tokens(line);
	if (server_names.size() > 0)
		perror("Error: server_name line should be unique..\n");
	if (tokens[0] != "server_name")
		perror("Error: invalid server_name line..\n");//TODO: hanlde valid return
	for (int i = 1; i < tokens.size(); i++)
		server_names.push_back(tokens[i]);
}

/**************************************************
 * 
 *	Set_port_host() parse line and adds 
 *	host:port pair to port_host vector storage
 *
 *	Rules for set_port_host:
 *	- first token is equal to "listen"
 *	- tokens.size is always 2
 *	- host:port pair should be unique all over 
 *		servers -> port_host
 *
**************************************************/
void Server::set_port_host(string line)
{
	vector<string> tokens = get_tokens(line);
	if (tokens[0] != "listen")
		perror("Error: invalid listen line..\n");//TODO: hanlde valid return
	else if (tokens.size() != 2)
		perror("Error: invalid listen line (tokens num)..\n");
	//find ':' symbol in token[1]
	size_t i = tokens[1].find(":");
	if (i == string::npos)
		perror("Error: invalid token in listen line..\n");
	string host = tokens[1].substr(0, i);
	int port = stoi(tokens[1].substr(i+1));
	//TODO: add check for host and port
	//TODO: check for unique pair
	port_host.push_back(make_pair(port, host));
}

/**************************************************
 * 
 *	Set_root() parse line and adds root
 *
 *	Rules for set_root:
 *	- root should be unique
 *	- tokens size should be 2
 *	- path should be dir
 *	- directory should open
 *
**************************************************/
// void Server::set_root(string line)
// {
// 	vector<string> tokens = get_tokens(line);
// 	if (root != "")
// 		perror("Error: not unique root..\n");
// 	if (tokens[0] != "root")
// 		perror("Error: invalid root line..\n");//TODO: hanlde valid return
// 	if (tokens.size() != 2)
// 		perror("Error: invalid root line (tokens num)..\n");
// 	//check whether it is directory
// 	//Maybe we dont need to check here
// 	DIR* dir = opendir(tokens[1].c_str());
//     if (dir == NULL)
//         perror("Error: invalid directory in root..\n");
//     closedir(dir);
// 	root = tokens[1];
// }

/**************************************************
 * 
 *	Set_index() parse line and adds index
 *
 *	Rules for set_index:
 *	- index should be unique
 *	- tokens size should be 2
 *
**************************************************/
// void Server::set_index(string line)
// {
// 	vector<string> tokens = get_tokens(line);
// 	if (indexes.size() > 0)
// 		perror("Error: not unique index..\n");
// 	if (tokens[0] != "index")
// 		perror("Error: invalid index line..\n");//TODO: hanlde valid return
// 	for (size_t i = 1; i < tokens.size(); i++)
// 		indexes.push_back(tokens[i]);	
// }

vector<string> Server::get_tokens(string line)
{
	//remove whitespaces on start
	line = removeLeadingWhitespaces(line);
	istringstream iss(line);
    vector<string> tokens;
    string token;

    while (iss >> token) {
        tokens.push_back(token);
    }
	for (size_t i = 0; i < tokens.size(); ++i) {
        cout << "Token " << i << ": " << tokens[i] << endl;
    }
	if (tokens.size() == 0)
		perror("Error: no tokens parsed from line..\n");//TODO: hanlde error properly
	return tokens;
}

string Server::removeLeadingWhitespaces(const string& input) {
    size_t firstNonSpace = input.find_first_not_of("\t");
    if (firstNonSpace == string::npos) {
        // The input contains only whitespace characters, return an empty string
        return "";
    }
    return input.substr(firstNonSpace);
}