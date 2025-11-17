#include "../include/monitor.h"
#include <assert.h>
#include <stdio.h>

int main() {
    printf("Testando coleta de memória do próprio processo...\n");
    int ret = collect_memory_metrics(getpid(), stdout);
    assert(ret == 0);
    printf("OK\n");
    return 0;
}
