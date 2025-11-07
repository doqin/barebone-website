#include <utils.hpp>
#include <stdio.h>
#include <stdlib.h>

void readfile(char **content, long *size, char *directory) {
  FILE *file = fopen(directory, "rb");  // Use binary mode to preserve exact byte count
  if (!file) {
    perror("Failed to open HTML file");
    *content = NULL;
    *size = 0;
    return;
  }

  fseek(file, 0, SEEK_END);
  *size = ftell(file);
  rewind(file);

  *content = (char*)malloc(*size + 1);  // +1 for null terminator
  if (!*content) {
    perror("Memory allocation failed");
    fclose(file);
    return;
  }

  fread(*content, 1, *size, file);
  (*content)[*size] = '\0';  // Add null terminator
  fclose(file);
}