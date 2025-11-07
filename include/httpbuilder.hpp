#ifndef HTTPBUILDER_HPP
#define HTTPBUILDER_HPP

/// @brief Makes an http header (Only 200 OK for now)
/// @param header Pointer to the header string to write to
/// @param size Size of the html body string
void header_builder(char *header, long size);

#endif