#include <winsock2.h>
#include <iostream>
#include <httpreader.hpp>
#include <handlerequest.hpp>

// socket's port
#define PORT 2452

#define BUFFER_SIZE 4096

WSADATA wsa_data;
SOCKET server_socket;
sockaddr_in server_addr;

void clean_up() {
    closesocket(server_socket);
    WSACleanup();
    exit(0);
}

void sigint_handler(int signum) {
    clean_up();
}

int main()
{
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        std::cerr << "WSAStartup failed.\n";
        exit(1);
    }

    // Create socket
    // AF_INET -> use IPv4, SOCK_STREAM -> stream socket, 0 -> use default protocol (TCP)
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET)
    {
        std::cerr << "Socket failed: " << WSAGetLastError() << "\n";
        exit(1);
    }

    server_addr.sin_family = AF_INET;         // Use IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        std::cerr << "Bind failed: " << WSAGetLastError() << "\n";
        clean_up();
    }

    if (listen(server_socket, 10) == SOCKET_ERROR)
    {
        std::cerr << "Listen failed: " << WSAGetLastError() << "\n";
        clean_up();
    }

    std::cout << "HTTP server listening on http://localhost:" << PORT << std::endl;

    signal(SIGINT, sigint_handler);

    while (true)
    {
        // Accept incoming connection
        // Return a file descriptor for a new socket
        // NULL means we don't care about the client's address info
        sockaddr_in client_addr;
        int client_addrsize = sizeof(client_addr);
        SOCKET client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addrsize);
        if (client_socket == INVALID_SOCKET)
        {
            std::cerr << "Accept failed: " << WSAGetLastError() << "\n";
            continue;
        }

        char buffer[BUFFER_SIZE];
        // Read message from client
        int bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_read < 0) {
            std::cerr << "Receiving message failed: " << WSAGetLastError() << "\n";
            closesocket(client_socket);
            continue;
        }
        buffer[bytes_read] = '\0';

        // Parse the http request
        HttpRequest request = parse_http_request(buffer);
        request.print();

        handle_request(client_socket, request);

        // Clean up
        closesocket(client_socket);
    }
    // Clean up
    clean_up();
}