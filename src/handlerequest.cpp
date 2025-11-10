#include <handlerequest.hpp>
#include <iostream>
#include <string>
#include <utils.hpp>
#include <httpbuilder.hpp>

// --- Declarations ---
void handle_get(SOCKET&, HttpRequest&);
void handle_post(SOCKET&, HttpRequest&);

// Main handler
void handle_request(SOCKET &clientSocket, HttpRequest &req) {
    if (req.method == "GET") {
        handle_get(clientSocket, req);
    } else if (req.method == "POST") {
        handle_post(clientSocket, req);
    } else {
        std::cout << "Haven't implemented this method: " << req.method << "\n";
    }
}

// --- Definitions ---
void handle_get(SOCKET &clientSocket, HttpRequest &req) {
    // Read the template content
    char* content = nullptr;
    long size = 0;
    const char* path = (req.path == "/" ? "/index.html" : req.path.c_str());
    std::string template_path = std::string("./resources/templates") + path;
    readfile(&content, &size, const_cast<char*>(template_path.c_str()));
    if (content == nullptr) {
        // TODO: Handle sending 500 Internal Server Error
        std::cerr << "Could not read the html template!\n";
        closesocket(clientSocket);
        return;
    }

    // Make the header for the http response
    char header[512];
    header_builder(header, size);

    printf("content:\n%s\n", content);
    send(clientSocket, header, strlen(header), 0);
    send(clientSocket, content, size, 0);
    std::cout << "Sent template to client!\n";
    delete[] content;
}

void handle_post(SOCKET &clientSocket, HttpRequest &req) {
    std::cout << "Haven't implemented POST methods, sorry!\n";
}