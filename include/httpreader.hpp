#ifndef HTTPREADER_HPP
#define HTTPREADER_HPP
#include <types.hpp>

/// @brief Creates an http request object from a string
/// @param request The request string 
/// @return An HTTP Request object
HttpRequest parse_http_request(const std::string &request);

#endif