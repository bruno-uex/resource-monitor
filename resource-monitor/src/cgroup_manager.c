#include "cgroup.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int read_cgroup_metrics(const char *cgroup_path, FILE *out) {
    char stat_path[128];
    snprintf(stat_path, sizeof(stat_path), "%s/cpu.stat", cgroup_path);
    FILE *f = fopen(stat_path, "r");
    if (!f) {
        fprintf(stderr, "Erro ao abrir %s\n", stat_path);
        return -1;
    }
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        fprintf(out, "%s", line);
    }
    fclose(f);
    return 0;
}

int create_cgroup(const char *name) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "mkdir -p /sys/fs/cgroup/%s", name);
    return system(cmd);
}

int move_process_to_cgroup(pid_t pid, const char *cgroup_path) {
    char procs_path[128];
    snprintf(procs_path, sizeof(procs_path), "%s/cgroup.procs", cgroup_path);
    FILE *f = fopen(procs_path, "w");
    if (!f) return -1;
    fprintf(f, "%d\n", pid);
    fclose(f);
    return 0;
}

int set_cgroup_limits(const char *cgroup_path, int cpu_limit, int mem_limit) {
    // Exemplo: limita CPU e memória (simplificado)
    char cpu_path[128], mem_path[128];
    snprintf(cpu_path, sizeof(cpu_path), "%s/cpu.max", cgroup_path);
    snprintf(mem_path, sizeof(mem_path), "%s/memory.max", cgroup_path);
    FILE *fcpu = fopen(cpu_path, "w");
    FILE *fmem = fopen(mem_path, "w");
    if (fcpu) { fprintf(fcpu, "%d\n", cpu_limit); fclose(fcpu); }
    if (fmem) { fprintf(fmem, "%d\n", mem_limit); fclose(fmem); }
    return 0;
}

int report_cgroup_usage(const char *cgroup_path, FILE *out) {
    // Relatório simplificado
    fprintf(out, "Relatório de uso de cgroup não implementado\n");
    return 0;
}
