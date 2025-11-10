#include <httpbuilder.hpp>
#include <stdio.h>

void header_builder(const ResponseStatus &status, const std::string &contentType, char *header, const long contentLength) {
    switch(status) {
        case ResponseStatus::OK:
            sprintf(header,
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: %s\r\n"
                "Content-Length: %ld\r\n"
                "\r\n",
                contentType,
                contentLength);
            break;
        case ResponseStatus::InternalServerError:
            sprintf(header,
                "HTTP/1.1 500 Internal Server Error\r\n"
                "Content-Type: %s\r\n"
                "Content-Length: %ld\r\n"
                "Connection: close\r\n"
                "\r\n",
                contentType,
                contentLength);
            break;
        case ResponseStatus::NotFound:
            sprintf(header,
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: %s\r\n"
                "Content-Length: %ld\r\n"
                "Connection: close\r\n"
                "\r\n",
                contentType,
                contentLength);
            break;
        default:
            sprintf(header,
                "HTTP/1.1 501 Not Implemented\r\n"
                "Content-Type: %s\r\n"
                "Content-Length: %ld\r\n"
                "Connection: close\r\n"
                "\r\n",
                contentType,
                contentLength);
    }
}