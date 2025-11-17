#ifndef CGROUP_H
#define CGROUP_H

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h> // para pid_t

int read_cgroup_metrics(const char *cgroup_path, FILE *out);
int create_cgroup(const char *name);
int move_process_to_cgroup(pid_t pid, const char *cgroup_path);
int set_cgroup_limits(const char *cgroup_path, int cpu_limit, int mem_limit);
int report_cgroup_usage(const char *cgroup_path, FILE *out);

#endif // CGROUP_H
