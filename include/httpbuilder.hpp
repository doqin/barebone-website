#ifndef HTTPBUILDER_HPP
#define HTTPBUILDER_HPP
#include <types.hpp>

/// @brief Makes an http header
/// @param status Type of response header
/// @param contentType Type of body it is
/// @param header Pointer to the header string to write to
/// @param contentLength Size of the html body string
void header_builder(const ResponseStatus &status, const std::string &contentType, char *header, const long contentLength);

#endif