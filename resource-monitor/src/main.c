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
    printf("  --profile <PID>\n");
    printf("  --profile <PID> --csv <arquivo>  Exporta métricas em CSV\n");
    printf("  --namespace <PID>\n");
    printf("  --compare-ns <PID1> <PID2>\n");
    printf("  --cgroup <cgroup_path>\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        print_usage();
        return 0;
    }
    if (strcmp(argv[1], "--profile") == 0 && (argc == 3 || (argc == 5 && strcmp(argv[3], "--csv") == 0))) {
        pid_t pid = atoi(argv[2]);
        FILE *out = stdout;
        int to_csv = 0;
        if (argc == 5 && strcmp(argv[3], "--csv") == 0) {
            out = fopen(argv[4], "w");
            if (!out) { perror("fopen"); return 2; }
            to_csv = 1;
        }
        if (to_csv) fprintf(out, "utime,stime,threads,VmRSS,VmSize,read_bytes,write_bytes\n");
        // Coleta CPU
        char buf[256];
        snprintf(buf, sizeof(buf), "/proc/%d/stat", pid);
        FILE *f = fopen(buf, "r");
        int utime=0, stime=0, threads=0;
        if (f && fgets(buf, sizeof(buf), f)) {
            char *token = strtok(buf, " ");
            int i = 1;
            while (token) {
                if (i == 14) utime = atoi(token);
                if (i == 15) stime = atoi(token);
                if (i == 20) threads = atoi(token);
                token = strtok(NULL, " ");
                i++;
            }
        }
        if (f) fclose(f);
        // Coleta memória
        int vmrss=0, vmsize=0;
        snprintf(buf, sizeof(buf), "/proc/%d/status", pid);
        f = fopen(buf, "r");
        if (f) {
            while (fgets(buf, sizeof(buf), f)) {
                if (strncmp(buf, "VmRSS:", 6) == 0) vmrss = atoi(buf+6);
                if (strncmp(buf, "VmSize:", 7) == 0) vmsize = atoi(buf+7);
            }
            fclose(f);
        }
        // Coleta I/O
        int read_bytes=0, write_bytes=0;
        snprintf(buf, sizeof(buf), "/proc/%d/io", pid);
        f = fopen(buf, "r");
        if (f) {
            while (fgets(buf, sizeof(buf), f)) {
                if (strncmp(buf, "read_bytes:", 11) == 0) read_bytes = atoi(buf+11);
                if (strncmp(buf, "write_bytes:", 12) == 0) write_bytes = atoi(buf+12);
            }
            fclose(f);
        }
        if (to_csv)
            fprintf(out, "%d,%d,%d,%d,%d,%d,%d\n", utime, stime, threads, vmrss, vmsize, read_bytes, write_bytes);
        else {
            collect_cpu_metrics(pid, out);
            collect_memory_metrics(pid, out);
            collect_io_metrics(pid, out);
        }
        if (out != stdout) fclose(out);
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
