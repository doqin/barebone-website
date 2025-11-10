#include <httpreader.hpp>
#include <sstream>

HttpRequest parse_http_request(const std::string &request) {
    HttpRequest req;
    std::istringstream stream(request);
    std::string line;

    if (std::getline(stream, line)) {
        std::istringstream lineStream(line);
        lineStream >> req.method >> req.path >> req.version;
    }

    while (std::getline(stream, line) && line != "\r") {
        if (line.back() == '\r') line.pop_back(); // remove trailing \r
        std::size_t pos = line.find(": ");
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 2);
            req.headers[key] = value;
        }
    }

    std::string body;
    while (std::getline(stream, line)) {
        body += line + "\n";
    }
    req.body = body;

    return req;
}