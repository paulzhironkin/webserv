#include "Response.hpp"

Response::Response(int status){
    this->status = get_status_text(status);

}

void Response::set_header(std::string key, std::string value)
{
    headers[key] = value;
}

void Response::set_body(std::string body)
{
    this->body = body;
}

void Response::set_content_type(std::string content_type)
{
    set_header("Content-Type", content_type);
}

void Response::set_content_length(std::string content_length)
{
    set_header("Content-Length", content_length);
}

void Response::set_location(std::string location)
{
    set_header("Location", location);
}

void Response::set_server(std::string server)
{
    set_header("Server", server);
}

void Response::set_date(std::string date)
{
    set_header("Date", date);
}

void Response::set_cache_control(std::string cache_control)
{
    set_header("Cache-Control", cache_control);
}

void Response::set_access_control_allow_origin(std::string allow_origin)
{
    set_header("Access-Control-Allow-Origin", allow_origin);
}

void Response::set_set_cookie(std::string cookie)
{
    set_header("Set-Cookie", cookie);
}

void Response::set_content_disposition(std::string disposition)
{
    set_header("Content-Disposition", disposition);
}

void Response::set_status(int status)
{
    this->status = get_status_text(status);
}

std::string Response::get_status_text(int status)
{
    switch (status) {
        case OK:
            return "200 OK";
        case CREATED:
            return "201 Created";
        case ACCEPTED:
            return "202 Accepted";
        case NO_CONTENT:
            return "204 No Content";
        case BAD_REQUEST:
            return "400 Bad Request";
        case UNAUTHORIZED:
            return "401 Unauthorized";
        case FORBIDDEN:
            return "403 Forbidden";
        case NOT_FOUND:
            return "404 Not Found";
        case METHOD_NOT_ALLOWED:
            return "405 Method Not Allowed";
        case INTERNAL_SERVER_ERROR:
            return "500 Internal Server Error";
        case NOT_IMPLEMENTED:
            return "501 Not Implemented";
        case BAD_GATEWAY:
            return "502 Bad Gateway";
        case SERVICE_UNAVAILABLE:
            return "503 Service Unavailable";
        case GATEWAY_TIMEOUT:
            return "504 Gateway Timeout";
        case HTTP_VERSION_NOT_SUPPORTED:
            return "505 HTTP Version Not Supported";
        case UNPROCESSABLE_ENTITY:
            return "422 Unprocessable Entity";
        case TOO_MANY_REQUESTS:
            return "429 Too Many Requests";
        case UNAVAILABLE_FOR_LEGAL_REASONS:
            return "451 Unavailable For Legal Reasons";
        case PAYLOAD_TOO_LARGE:
            return "413 Payload Too Large";
        case URI_TOO_LONG:
            return "414 URI Too Long";
        default:
            return "200 OK";
    }
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
