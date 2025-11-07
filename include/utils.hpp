#ifndef UTILS_HPP
#define UTILS_HPP

/// @brief Utility function to read file and copy it to a string buffer
/// @param content Pointer to the string
/// @param size Pointer to the size variable of the string
/// @param directory Path to the file
void readfile(char **content, long *size, char *directory);

#endif