#include "monitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int collect_memory_metrics(pid_t pid, FILE *out) {
    char status_path[64];
    snprintf(status_path, sizeof(status_path), "/proc/%d/status", pid);
    FILE *f = fopen(status_path, "r");
    if (!f) {
        fprintf(stderr, "Erro ao abrir %s\n", status_path);
        return -1;
    }
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "VmRSS:", 6) == 0 || strncmp(line, "VmSize:", 7) == 0) {
            fprintf(out, "%s", line);
        }
    }
    fclose(f);
    return 0;
}
