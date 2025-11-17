#include "monitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int collect_io_metrics(pid_t pid, FILE *out) {
    char io_path[64];
    snprintf(io_path, sizeof(io_path), "/proc/%d/io", pid);
    FILE *f = fopen(io_path, "r");
    if (!f) {
        fprintf(stderr, "Erro ao abrir %s\n", io_path);
        return -1;
    }
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        fprintf(out, "%s", line);
    }
    fclose(f);
    return 0;
}
