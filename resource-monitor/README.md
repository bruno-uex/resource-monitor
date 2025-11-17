# Resource Monitor

Ferramenta para profiling, análise de namespaces e gerenciamento de cgroups em sistemas Linux, desenvolvida em C/C++ seguindo as especificações acadêmicas.

## Estrutura do Projeto

- `src/`: Código-fonte dos módulos principais
- `include/`: Headers
- `docs/`: Documentação
- `tests/`: Testes unitários
- `scripts/`: Scripts auxiliares

## Compilação

Requer GCC (C23) e ambiente Linux com acesso a `/proc` e `/sys/fs/cgroup`.

```sh
make
```

## Uso

### Coletar métricas de um processo
```sh
./resource-monitor --profile <PID>
```

### Analisar namespaces de um processo
```sh
./resource-monitor --namespace <PID>
```

### Comparar namespaces entre dois processos
```sh
./resource-monitor --compare-ns <PID1> <PID2>
```

### Ler métricas de um cgroup
```sh
./resource-monitor --cgroup <caminho_cgroup>
```

## Testes

```sh
make test
./tests/test_cpu
./tests/test_memory
./tests/test_io
```

## Scripts Auxiliares

- `scripts/visualize.py`: Visualização de métricas (requer Python, pandas, matplotlib)
- `scripts/compare_tools.sh`: Comparação com ferramentas externas

## Autoria

Desenvolvido por Bruno Horning para fins acadêmicos. Proibida a cópia ou uso não autorizado.
