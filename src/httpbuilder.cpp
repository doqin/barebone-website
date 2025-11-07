#include <httpbuilder.hpp>
#include <stdio.h>

void header_builder(char* header, long size) {
    sprintf(header,
          "HTTP/1.1 200 OK\r\n"
          "Content-Type: text/html\r\n"
          "Content-Length: %ld\r\n"
          "\r\n",
          size);
}