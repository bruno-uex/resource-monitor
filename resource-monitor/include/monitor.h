#ifndef MONITOR_H
#define MONITOR_H

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>

int collect_cpu_metrics(pid_t pid, FILE *out);
int collect_memory_metrics(pid_t pid, FILE *out);
int collect_io_metrics(pid_t pid, FILE *out);

#endif // MONITOR_H
