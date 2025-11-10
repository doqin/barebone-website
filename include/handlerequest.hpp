#ifndef HANDLEREQUEST_HPP
#define HANDLEREQUEST_HPP
#include <types.hpp>
#include <winsock2.h>

/// @brief Main request handler for the web app
/// @param clientSocket Client's socket
/// @param req HTTP Request object
void handle_request(SOCKET &clientSocket, HttpRequest &req);

#endif