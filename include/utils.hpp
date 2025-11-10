#ifndef UTILS_HPP
#define UTILS_HPP
#include <string>

/// @brief Utility function to read file and copy it to a string buffer
/// @param content Pointer to the string
/// @param size Pointer to the size variable of the string
/// @param directory Path to the file
void readfile(char **content, long *size, const char *directory);

/// @brief Gets the content-type from a file
/// @param directory Path to the file
/// @return Name of the content-type
std::string get_content_type(const char *directory);

#endif