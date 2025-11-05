/* fileReader.h — public declarations for fileReader.c */
#pragma once
#include <stddef.h> /* Because we need to use size_t */
char **read_lines(const char *path, size_t *out_count);
void free_lines(char **lines);
//Here is how the complete fileReader.h looks like after incorporating the suggestions:
/* fileReader.h — public declarations for fileReader.c */
