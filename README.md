# 🎒 EstruturaDeDados-FreeFire: Projeto de Simulação de Inventário em C

## 🎯 Visão Geral do Projeto

Este projeto simula um sistema de **Gerenciamento de Inventário** (Mochila) inspirado em jogos de sobrevivência, utilizando a linguagem **C**. O objetivo central é implementar e comparar diferentes **Estruturas de Dados** e **Algoritmos** para organizar e acessar itens de forma eficiente. O projeto avança em complexidade, demonstrando o impacto da escolha da estrutura no desempenho e na flexibilidade.

---

## 🚀 Status do Desenvolvimento 

| Nível | Status | Estruturas e Conceitos Aplicados |
| :--- | :--- | :--- |
| **Novato** | ✅ Concluído | **Structs** (`Item`), **Lista Sequencial (Vetor)**, **Busca Linear**, CRUD básico. |
| **Aventureiro** | ✅ Concluído | **Lista Sequencial** vs. **Lista Encadeada**, **Alocação Dinâmica** (`malloc`/`free`), **Busca Binária**, **Bubble Sort**, **Modularização**. |
| **Mestre** | ✅ Concluído | **Análise de Algoritmos** (Bubble, Insertion, Selection Sort), Medição de **Tempo (`clock()`)** e **Comparações**, **Busca Binária** otimizada. |

---

## ✨ Funcionalidades por Nível

### ✅ Nível Novato: A Mochila Estática

O Nível Novato estabelece o sistema de inventário com capacidade fixa, focando na organização em vetor.

* **Estrutura Base:** Criação da `struct Item` (nome, tipo, quantidade).
* **Armazenamento:** Uso de um **vetor** com capacidade máxima de 10 itens (Lista Sequencial Estática).
* **Operações Básicas (CRUD):** Inserção no final do vetor, remoção com deslocamento, listagem e **Busca Sequencial** por nome.

### ✅ Nível Aventureiro: Comparação de Estruturas

O Nível Aventureiro foca na comparação direta entre a Lista Sequencial e a Lista Encadeada, introduzindo alocação dinâmica.

* **Implementações Paralelas:** Duas versões do sistema:
    1.  **Vetor:** Implementação completa com tamanho fixo.
    2.  **Lista Encadeada:** Utiliza `struct No` e **ponteiros** (`malloc`, `free`) para flexibilidade total (Alocação Dinâmica).
* **Busca Otimizada:** Implementação do **Bubble Sort** no vetor para habilitar a **Busca Binária** (mais eficiente que a Sequencial).
* **Análise Empírica:** Contagem de operações de comparação para as buscas Sequencial e Binária, comparando o desempenho.
* **Modularização:** Código dividido em arquivos separados (`mochila_lista.c` e `mochila_vetor.c`) para isolar as estruturas.

### ✅ Nível Mestre: Estratégia e Análise de Desempenho

O Nível Mestre aborda a organização estratégica com a implementação e análise de algoritmos de ordenação avançados.

* **Nova Estrutura:** Criação da `struct Componente` (nome, tipo, prioridade).
* **Três Algoritmos de Ordenação:**
    * **Bubble Sort:** Ordenação por Nome.
    * **Insertion Sort:** Ordenação por Tipo.
    * **Selection Sort:** Ordenação por Prioridade (Inteiro).
* **Medição de Desempenho:** O sistema mede e exibe o **tempo de execução** (`clock()`) e o **número de comparações** para cada algoritmo.
* **Busca Final:** Aplicação da **Busca Binária** otimizada no vetor ordenado por nome para localizar o "componente-chave" da missão.

---
## 📁 Estrutura do Projeto (Modularização)

O projeto é organizado em diretórios, representando a evolução dos conceitos aplicados em cada nível.

```bash
estrutura-de-dados-02-projeto-free-fire/
├── README.md
├── 01-novato/
│   └── mochila-inicial.c          
├── 02-aventureiro/
│   ├── mochila_lista.c            
│   └── mochila_vetor.c            
└── 03-mestre/
    └── torre_fuga.c 
```
---

## ⚙️ Como Compilar e Executar (Geral)

Para rodar qualquer nível do projeto, é necessário ter o compilador **GCC** instalado no sistema. O processo envolve navegar até a pasta do nível desejado, compilar o arquivo (ou arquivos) e executar o binário gerado.

### 1. Navegação no Terminal

Abra o seu terminal e navegue até a pasta do nível que deseja testar:

```bash
# Exemplo para o Nível Aventureiro
cd estrutura-de-dados-02-projeto-free-fire/aventureiro
```

### 2. Compilação do Código

Use o ```gcc``` para compilar o arquivo ```C``` e gerar o executável.

| **Nível** | Comando de Compilação |
| :--: | :--: |
| **Novato** | ```gcc mochila-inicial.c -o inventario``` |
| **Aventureiro (Vetor)** | ```gcc mochila_vetor.c -o mochila_v``` |
| **Aventureiro (Lista)** | ```gcc mochila_lista.c -o mochila_l``` |
| **Mestre** | ```gcc torre_fuga.c -o torre_fuga``` |

### 3. Execução do Programa

Execute o arquivo compilado no terminal:

```bash
# Substitua o nome pelo executável gerado
./[nome_do_executavel]
```

O programa exibirá um menu interativo para testar as operações de CRUD, ordenação e busca.