# Arquitetura do Resource Monitor

O projeto é modularizado em três componentes principais:

- **Resource Profiler**: Coleta métricas de CPU, memória e I/O de processos.
- **Namespace Analyzer**: Analisa namespaces ativos e isolamento de processos.
- **Control Group Manager**: Gerencia cgroups, aplica limites e coleta métricas.

Cada módulo possui código-fonte dedicado em `src/` e headers em `include/`. O Makefile compila todos os módulos em um binário único.

## Fluxo de Execução

1. O usuário executa o binário com argumentos específicos.
2. O `main.c` direciona para o módulo correspondente.
3. Cada módulo lê arquivos de `/proc` ou `/sys/fs/cgroup` conforme necessário.
4. Saída formatada em stdout (pode ser redirecionada para CSV/JSON).

## Exemplo de Uso

```sh
./resource-monitor --profile 1234
./resource-monitor --namespace 1234
./resource-monitor --compare-ns 1234 5678
./resource-monitor --cgroup /sys/fs/cgroup/teste
```

## Observações

- Não utiliza bibliotecas externas.
- Código limpo, comentado e modular.
- Testes básicos em `tests/`.
- Scripts auxiliares em `scripts/`.
