#include <types.hpp>
#include <iostream>

void HttpRequest::print() {
    std::cout << "Method: " << this->method << "\n";
    std::cout << "Path: " << this->path << "\n";
    std::cout << "Version: " << this->version << "\n";

    std::cout << "Headers:\n";
    for (const auto& [key, value] : this->headers) {
        std::cout << "\t" << key << ": " << value << "\n";
    }

    std::cout << "Body:\n\t" << this->body << "\n";
}