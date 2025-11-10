#include <utils.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include <algorithm>

void readfile(char **content, long *size, const char *directory)
{
    FILE *file = fopen(directory, "rb"); // Use binary mode to preserve exact byte count
    if (!file)
    {
        perror("Failed to open file");
        *content = NULL;
        *size = 0;
        return;
    }

    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    rewind(file);

    *content = (char *)malloc(*size + 1); // +1 for null terminator
    if (!*content)
    {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(*content, 1, *size, file);
    (*content)[*size] = '\0'; // Add null terminator
    fclose(file);
}

namespace fs = std::filesystem;

std::string get_content_type(const char *directory) {
    fs::path p(directory);
    
    if (!fs::exists(p)) return "not_found";
    if (!p.has_extension()) return "unknown";

    std::string ext = p.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower); // lowercase

    if (ext == ".html" || ext == ".htm") return "text/html";
    if (ext == ".css") return "text/css";
    if (ext == ".js") return "text/javascript";
    if (ext == ".png") return "image/png";
    if (ext == ".ico") return "image/x-icon";
    if (ext == ".jpg" || ext == ".jpeg") return "image/jpeg";
    if (ext == ".gif") return "image/gif";
    if (ext == ".bmp") return "image/bmp";
    if (ext == ".svg") return "image/svg+xml";

    return "unknown";
}