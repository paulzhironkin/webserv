#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include <map>

class Response
{
private:
    std::string status;
    std::map<std::string, std::string> headers;
    std::string body;
    std::string generate_status_line();
    std::string generate_headers();
public:
    Response(std::string status);
    void set_header(std::string key, std::string value);
    void set_body(std::string body);
    std::string generate_response();
};

#endif
