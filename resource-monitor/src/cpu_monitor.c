#include <sys/types.h> // para pid_t
#include "monitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int collect_cpu_metrics(pid_t pid, FILE *out) {
    char stat_path[64];
    snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", pid);
    FILE *f = fopen(stat_path, "r");
    if (!f) {
        fprintf(stderr, "Erro ao abrir %s\n", stat_path);
        return -1;
    }
    // Exemplo: coleta de utime, stime, threads
    int utime, stime, num_threads;
    char buf[1024];
    if (fgets(buf, sizeof(buf), f)) {
        char *token = strtok(buf, " ");
        int i = 1;
        while (token) {
            if (i == 14) utime = atoi(token);
            if (i == 15) stime = atoi(token);
            if (i == 20) num_threads = atoi(token);
            token = strtok(NULL, " ");
            i++;
        }
        fprintf(out, "utime: %d, stime: %d, threads: %d\n", utime, stime, num_threads);
    }
    fclose(f);
    return 0;
}
