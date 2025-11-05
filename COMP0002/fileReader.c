#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **read_lines_fgets(const char *path, size_t *out_count)
{
    FILE *f = fopen(path, "r");
    if (!f) return NULL;

    size_t cap = 16, count = 0;
    char **lines = malloc(cap * sizeof *lines);
    if (!lines) { fclose(f); return NULL; }

    char buf[1024];
    while (fgets(buf, sizeof buf, f)) {
        size_t len = strlen(buf) + 1;
        char *line = malloc(len);
        if (!line) {
            for (size_t i = 0; i < count; ++i) free(lines[i]);
            free(lines);
            fclose(f);
            return NULL;
        }
        memcpy(line, buf, len);

        if (count >= cap) {
            size_t newcap = cap * 2;
            char **tmp = realloc(lines, newcap * sizeof *lines);
            if (!tmp) {
                for (size_t i = 0; i < count; ++i) free(lines[i]);
                free(lines);
                free(line);
                fclose(f);
                return NULL;
            }
            lines = tmp;
            cap = newcap;
        }

        lines[count++] = line;
    }

    fclose(f);

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

int main(void)
{
    size_t n;
    char **lines = read_lines_fgets("map.txt", &n);
    if (!lines) { perror("read_lines_fgets"); return 1; }

    for (size_t i = 0; i < n; ++i) printf("%s", lines[i]);

    free_lines(lines);
    return 0;
}

