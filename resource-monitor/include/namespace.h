#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h> // para pid_t

int list_namespaces(pid_t pid, FILE *out);
int compare_namespaces(pid_t pid1, pid_t pid2, FILE *out);
int report_namespace_isolation(FILE *out);

#endif // NAMESPACE_H
