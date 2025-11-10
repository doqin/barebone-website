#include <handlerequest.hpp>
#include <iostream>
#include <string>
#include <utils.hpp>
#include <httpbuilder.hpp>

// --- Declarations ---

void handle_get(SOCKET&, HttpRequest&);
void handle_post(SOCKET&, HttpRequest&);
void send_not_found(SOCKET&);
void send_not_implemented(SOCKET&);

// --- Main handler ---

void handle_request(SOCKET &clientSocket, HttpRequest &req) {
    if (req.method == "GET") {
        handle_get(clientSocket, req);
    } else if (req.method == "POST") {
        handle_post(clientSocket, req);
    } else {
        std::cout << "Haven't implemented this method: " << req.method << "\n";
        send_not_implemented(clientSocket);
    }
}

// --- Definitions ---

/// @brief Handler for GET requests
/// @param clientSocket Client's socket
/// @param req HTTP Request
void handle_get(SOCKET &clientSocket, HttpRequest &req) {
    // Read the template content
    char* content = nullptr;
    long content_length = 0;
    const char* path = (req.path == "/" ? "/index.html" : req.path.c_str());
    std::string template_path = std::string("./static") + path;
    std::string content_type = get_content_type(template_path.c_str());
    if (content_type == "unknown" || content_type == "not_found") {
        std::cerr << "Could not find " << path << "!\n";
        send_not_found(clientSocket);
        return;
    }
    readfile(&content, &content_length, template_path.c_str());
    if (content == nullptr) {
        std::cerr << "Could not find " << path << "!\n";
        send_not_found(clientSocket);
        return;
    }

    // Make the header for the http response
    char header[512];
    header_builder(ResponseStatus::OK, content_type, header, content_length);

    send(clientSocket, header, strlen(header), 0);
    send(clientSocket, content, content_length, 0);
    std::cout << "Sent template to client!\n";
    delete[] content;
}

/// @brief Handler for POST requests
/// @param clientSocket Client's socket
/// @param req HTTP Request
void handle_post(SOCKET &clientSocket, HttpRequest &req) {
    std::cerr << "Haven't implemented POST methods, sorry!\n";
    send_not_implemented(clientSocket);
}

// --- Helpers ---

/// @brief Send a not found response to the client
/// @param clientSocket Client's socket
void send_not_found(SOCKET &clientSocket) {
    char* content = nullptr;
    long content_length = 0;
    readfile(&content, &content_length, "./static/not_found.html");
    if (content == nullptr) {
        std::cerr << "Could not find not_found.html!\n";
        return;
    }

    char header[512];
    header_builder(ResponseStatus::NotFound, "text/html", header, content_length);

    send(clientSocket, header, strlen(header), 0);
    send(clientSocket, content, content_length, 0);
    std::cout << "Sent 404 Not Found to client!\n";
}

/// @brief Send a not implemented response to the client
/// @param clientSocket Client's socket
void send_not_implemented(SOCKET &clientSocket) {
    const char* content = "501 Not Implemented";
    long content_length = strlen(content);

    char header[512];
    header_builder(ResponseStatus::NotImplemented, "text/plain", header, content_length);

    send(clientSocket, header, strlen(header), 0);
    send(clientSocket, content, content_length, 0);
    std::cout << "Sent 501 Not Implemented to client!\n";
}