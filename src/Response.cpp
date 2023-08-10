#include "Response.hpp"

Response::Response(std::string status) : status(status) {}

void Response::set_header(std::string key, std::string value)
{
    headers[key] = value;
}

void Response::set_body(std::string body)
{
    this->body = body;
}

std::string Response::generate_status_line()
{
    return "HTTP/1.1 " + status + "\r\n";
}

std::string Response::generate_headers()
{
    std::string result;
    std::map<std::string, std::string>::iterator it;
    for (it = headers.begin(); it != headers.end(); ++it) {
        result += it->first + ": " + it->second + "\r\n";
    }
    return result;
}

std::string Response::generate_response()
{
    std::string response = generate_status_line();
    response += generate_headers();
    response += "\r\n" + body;
    return response;
}
