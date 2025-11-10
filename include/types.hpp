#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <unordered_map>

/// @brief An HTTP Request object
struct HttpRequest {
    std::string method;
    std::string path;
    std::string version;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

#endif