#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include <map>

enum  {
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    NO_CONTENT = 204,
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    METHOD_NOT_ALLOWED = 405,
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    BAD_GATEWAY = 502,
    SERVICE_UNAVAILABLE = 503,
    GATEWAY_TIMEOUT = 504,
    HTTP_VERSION_NOT_SUPPORTED = 505,
    UNPROCESSABLE_ENTITY = 422,
    TOO_MANY_REQUESTS = 429,
    UNAVAILABLE_FOR_LEGAL_REASONS = 451,
    PAYLOAD_TOO_LARGE = 413,
    URI_TOO_LONG = 414,
};

class Response
{
private:
    std::string status;
    std::map<std::string, std::string> headers;
    std::string body;
    std::string generate_status_line();
    std::string generate_headers();
    std::string get_status_text(int status);
public:
    Response(int status);
    void set_header(std::string key, std::string value);
    void set_body(std::string body);
    void set_content_type(std::string content_type);
    void set_content_length(std::string content_length);
    void set_location(std::string location);
    void set_server(std::string server);
    void set_date(std::string date);
    void set_cache_control(std::string cache_control);
    void set_access_control_allow_origin(std::string allow_origin);
    void set_set_cookie(std::string cookie);
    void set_content_disposition(std::string disposition);
    void set_status(int status);
    std::string generate_response();
};

#endif
