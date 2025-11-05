#pragma once
#include <stddef.h> /* Because we need to use size_t */
char **readFile(const char *path,size_t *out_count);
void free_lines(char **lines);