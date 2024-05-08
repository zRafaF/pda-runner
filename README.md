# PDA Runner


Este projeto se trata de um programa que:

1. Recebe uma descrição de um autômato à pilha.
2. Recebe uma sequência de palavras
3. Para cada palavra determina se é ou não aceito pelo PDA


## Entrada

A entrada começa com 2 valores:

* `Q`: Número de estados `{q0, q1, q2, ..., qQ-1}`
* `T`: Número de transições

O **alfabeto de entrada** são **letras minúsculas** `Σ={a, b, c, ..., z}`

O **alfabeto da pilha** são **letras maíusculas** `Γ={A, B, C, ..., Z}` e `Z` é o símbolo inicialmente na pilha.


As próximas `T` linhas de entrada descrevem 

## Como utilizar

A seguir são apresentados os passos para compilar e executar o programa.

Antes de começar é necessário ter [Make](https://www.gnu.org/software/make/) instalado em seu ambiente.

Para **compilar** os binários utilize:


``` bash
make
```

Ou então para **compilar e executar** utilize:
``` bash
make run
```
