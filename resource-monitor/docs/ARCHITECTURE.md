# Arquitetura do Resource Monitor

O projeto é modularizado em três componentes principais:

- **Resource Profiler**: Coleta métricas de CPU, memória e I/O de processos.
- **Namespace Analyzer**: Analisa namespaces ativos e isolamento de processos.
- **Control Group Manager**: Gerencia cgroups, aplica limites e coleta métricas.

Cada módulo possui código-fonte dedicado em `src/` e headers em `include/`. O Makefile compila todos os módulos em um binário único.
