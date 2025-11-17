#include "namespace.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int list_namespaces(pid_t pid, FILE *out) {
    char ns_path[64];
    snprintf(ns_path, sizeof(ns_path), "/proc/%d/ns", pid);
    DIR *dir = opendir(ns_path);
    if (!dir) {
        fprintf(stderr, "Erro ao abrir %s\n", ns_path);
        return -1;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            char link_path[128], buf[128];
            snprintf(link_path, sizeof(link_path), "%s/%s", ns_path, entry->d_name);
            ssize_t len = readlink(link_path, buf, sizeof(buf)-1);
            if (len > 0) {
                buf[len] = '\0';
                fprintf(out, "%s: %s\n", entry->d_name, buf);
            }
        }
    }
    closedir(dir);
    return 0;
}

int compare_namespaces(pid_t pid1, pid_t pid2, FILE *out) {
    // Implementação simplificada: compara inode dos namespaces
    // ...
    fprintf(out, "Comparação de namespaces não implementada\n");
    return 0;
}

int report_namespace_isolation(FILE *out) {
    // Implementação simplificada: relatório global
    fprintf(out, "Relatório global de namespaces não implementado\n");
    return 0;
}
