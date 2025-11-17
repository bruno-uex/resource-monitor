#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "monitor.h"
#include "namespace.h"
#include "cgroup.h"

void print_usage() {
    printf("Resource Monitor\n");
    printf("Uso:\n");
    printf("  --profile <PID>         Coleta métricas de CPU, memória e I/O do processo\n");
    printf("  --namespace <PID>       Lista namespaces do processo\n");
    printf("  --compare-ns <PID1> <PID2>  Compara namespaces entre dois processos\n");
    printf("  --cgroup <cgroup_path>  Lê métricas do cgroup\n");
    printf("  --help                  Mostra esta mensagem\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        print_usage();
        return 0;
    }
    if (strcmp(argv[1], "--profile") == 0 && argc == 3) {
        pid_t pid = atoi(argv[2]);
        collect_cpu_metrics(pid, stdout);
        collect_memory_metrics(pid, stdout);
        collect_io_metrics(pid, stdout);
    } else if (strcmp(argv[1], "--namespace") == 0 && argc == 3) {
        pid_t pid = atoi(argv[2]);
        list_namespaces(pid, stdout);
    } else if (strcmp(argv[1], "--compare-ns") == 0 && argc == 4) {
        pid_t pid1 = atoi(argv[2]);
        pid_t pid2 = atoi(argv[3]);
        compare_namespaces(pid1, pid2, stdout);
    } else if (strcmp(argv[1], "--cgroup") == 0 && argc == 3) {
        read_cgroup_metrics(argv[2], stdout);
    } else {
        print_usage();
        return 1;
    }
    return 0;
}
