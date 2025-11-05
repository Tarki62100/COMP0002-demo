#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

char **readFile(const char *path, size_t *out_count)
{
    FILE *fptr = fopen(path, "r");
    if (!fptr) {
        perror("Couldn't open file");
        return NULL;
    }

    size_t cap = 16;
    size_t count = 0;
    char **lines = malloc(cap * sizeof *lines);
    if (!lines) { fclose(fptr); return NULL; }

    char buf[1024];
    while (fgets(buf, sizeof buf, fptr)) {
        size_t len = strlen(buf) + 1;
        char *line = malloc(len);
        if (!line) {
            // cleanup on allocation failure
            for (size_t i = 0; i < count; ++i) free(lines[i]);
            free(lines);
            fclose(fptr);
            return NULL;
        }
        memcpy(line, buf, len);

        if (count == cap) {
            size_t ncap = cap * 2;
            char **tmp = realloc(lines, ncap * sizeof *lines);
            if (!tmp) {
                free(line);
                for (size_t i = 0; i < count; ++i) free(lines[i]);
                free(lines);
                fclose(fptr);
                return NULL;
            }
            lines = tmp;
            cap = ncap;
        }
        lines[count++] = line;
    }

    fclose(fptr);

    // make array NULL-terminated
    char **tmp = realloc(lines, (count + 1) * sizeof *lines);
    if (tmp) lines = tmp;
    lines[count] = NULL;

    if (out_count) *out_count = count;
    return lines;
}

void free_lines(char **lines)
{
    if (!lines) return;
    for (size_t i = 0; lines[i]; ++i) free(lines[i]);
    free(lines);
}
