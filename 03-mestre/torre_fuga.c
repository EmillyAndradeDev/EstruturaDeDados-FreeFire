#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

// Capacidade máxima de componentes para a torre.
#define MAX_COMPONENTES 20
#define CHAVE_BUSCA "chip central" 


// 1. Criação da Struct Componente

typedef struct {
    char nome[30];
    char tipo[20]; 
    int prioridade; // 1 (mais alta) a 10 (mais baixa)
} Componente;


// 2. Variáveis Globais de Estado

Componente componentes[MAX_COMPONENTES];
int numComponentes = 0;

// Variáveis de medição de desempenho
long long comparacoes = 0;
clock_t tempoExecucao;


// 3. Funções de Utilitário e I/O


void mostrarComponentes() {
    printf("\n------- Componentes da Torre de Resgate (%d/%d) -------\n", numComponentes, MAX_COMPONENTES);
    if (numComponentes == 0) {
        printf("Nenhum componente cadastrado.\n");
        printf("-------------------------------------------------------\n");
        return;
    }
    
    printf(" # | Prioridade | Tipo (20) | Nome (30)\n");
    printf("---|------------|-----------|------------------------------\n");
    for (int i = 0; i < numComponentes; i++) {
        printf(" %-2d| %-10d | %-9s | %-28s\n", 
               i + 1, 
               componentes[i].prioridade, 
               componentes[i].tipo, 
               componentes[i].nome);
    }
    printf("-------------------------------------------------------\n");
}

// Função para cadastrar novos componentes.

void cadastrarComponentes() {
    if (numComponentes >= MAX_COMPONENTES) {
        printf("\n🚫 Limite maximo de componentes (%d) alcancado. 🚫\n", MAX_COMPONENTES);
        return;
    }

    printf("\n--- Cadastro de Componente (%d/%d) ---\n", numComponentes + 1, MAX_COMPONENTES);
    Componente novo;

    // Leitura do Nome
    printf("Nome do Componente (ex: chip central): ");
    int c; while ((c = getchar()) != '\n' && c != EOF); 
    if (fgets(novo.nome, sizeof(novo.nome), stdin) != NULL) {
        novo.nome[strcspn(novo.nome, "\n")] = 0;
    }

    // Leitura do Tipo
    printf("Tipo (ex: controle, suporte, propulsao): ");
    scanf("%s", novo.tipo);
    
    // Leitura da Prioridade (1 a 10)
    printf("Prioridade (1=Mais Alta, 10=Mais Baixa): ");
    while (scanf("%d", &novo.prioridade) != 1 || novo.prioridade < 1 || novo.prioridade > 10) {
        printf("Prioridade invalida. Digite um valor entre 1 e 10: ");
        while ((c = getchar()) != '\n' && c != EOF); 
    }
    
    componentes[numComponentes++] = novo;
    printf("\n✅ Componente '%s' cadastrado com sucesso! ✅\n", novo.nome);
}

//Função utilitária para trocar dois componentes (Swap).
void trocar(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

// 4. Algoritmos de Ordenação (Medição de Desempenho)

void bubbleSortNome(Componente arr[], int n) {
    comparacoes = 0;
    clock_t inicio = clock();
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Comparação de strings
            comparacoes++;
            if (strcmp(arr[j].nome, arr[j + 1].nome) > 0) {
                trocar(&arr[j], &arr[j + 1]);
            }
        }
    }
    
    tempoExecucao = clock() - inicio;
}


void insertionSortTipo(Componente arr[], int n) {
    comparacoes = 0;
    clock_t inicio = clock();
    
    for (int i = 1; i < n; i++) {
        Componente chave = arr[i];
        int j = i - 1;

        while (j >= 0) {
            // Comparação de strings
            comparacoes++;
            if (strcmp(arr[j].tipo, chave.tipo) > 0) {
                arr[j + 1] = arr[j];
                j = j - 1;
            } else {
                break;
            }
        }
        arr[j + 1] = chave;
    }
    
    tempoExecucao = clock() - inicio;
}


void selectionSortPrioridade(Componente arr[], int n) {
    comparacoes = 0;
    clock_t inicio = clock();
    
    for (int i = 0; i < n - 1; i++) {
        int indiceMin = i;
        for (int j = i + 1; j < n; j++) {
            // Comparação de inteiros
            comparacoes++;
            // Prioridade 1 é mais alta, entao buscamos o menor numero (maior prioridade)
            if (arr[j].prioridade < arr[indiceMin].prioridade) {
                indiceMin = j;
            }
        }
        // Coloca o elemento com a menor prioridade no local correto
        if (indiceMin != i) {
            trocar(&arr[indiceMin], &arr[i]);
        }
    }
    
    tempoExecucao = clock() - inicio;
}

// 5. Algoritmo de Busca

void buscaBinariaPorNome(Componente arr[], int n, const char nomeChave[]) {
    // A busca binária deve ser chamada apenas após a ordenação por nome
    // Para fins educacionais e de desempenho, reutilizamos o contador global
    comparacoes = 0; 
    
    int esquerda = 0;
    int direita = n - 1;
    int indiceEncontrado = -1;

    clock_t inicio = clock();

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        int resultado = strcmp(arr[meio].nome, nomeChave);
        comparacoes++;

        if (resultado == 0) {
            indiceEncontrado = meio;
            break; 
        }
        
        // Se o nome no meio e "maior" que a chave, busca na esquerda
        if (resultado > 0) {
            direita = meio - 1;
        } 
        // Se o nome no meio e "menor" que a chave, busca na direita
        else {
            esquerda = meio + 1;
        }
    }
    
    tempoExecucao = clock() - inicio;

    printf("\n--- Resultado da Busca Binaria ---\n");
    printf("Componente Chave: '%s'\n", nomeChave);
    
    if (indiceEncontrado != -1) {
        printf("✅ Componente Chave encontrado! Montagem OK.\n");
        printf("Localizado na Posicao: %d\n", indiceEncontrado + 1);
        printf("Detalhes: Prioridade %d, Tipo %s\n", arr[indiceEncontrado].prioridade, arr[indiceEncontrado].tipo);
    } else {
        printf("❌ Componente Chave nao encontrado. A montagem falhou.\n");
    }

    printf("Comparações realizadas: %lld\n", comparacoes);
    printf("Tempo de Execucao: %.6f segundos.\n", (double)tempoExecucao / CLOCKS_PER_SEC);
}

// Função de interface para exibir os resultados da medição de desempenho da ordenação.
void exibirResultadoMedicao(const char *algoritmo, const char *criterio) {
    printf("\n--- Desempenho da Ordenacao (%s) ---\n", algoritmo);
    printf("Criterio: %s\n", criterio);
    printf("Comparações realizadas: %lld\n", comparacoes);
    printf("Tempo de Execucao: %.6f segundos.\n", (double)tempoExecucao / CLOCKS_PER_SEC);
}

// 6. Função Principal 

int main() {
    int opcao;
    int ordenadoPorNome = 0; // Flag para validar a busca binária

    printf("-------------------------------------------------------\n");
    printf("  🏆 NIVEL MESTRE: ESTRATEGIA DE FUGA E ORDENACAO 🏆\n");
    printf("  Monte a Torre de Resgate priorizando seus componentes.\n");
    printf("-------------------------------------------------------\n");

    // Preenchendo alguns dados iniciais para teste (opcional)
    Componente inicial[] = {
        {"Blindagem Reforcada", "suporte", 6},
        {"Chip Central", CHAVE_BUSCA, 1}, // O componente chave
        {"Fusivel de Alta", "controle", 8},
        {"Rotor Principal", "propulsao", 3},
        {"Kit de Ferramentas", "suporte", 5}
    };
    for(int i = 0; i < sizeof(inicial)/sizeof(Componente); i++) {
        componentes[numComponentes++] = inicial[i];
    }
    printf("5 componentes iniciais carregados para a missao.\n");
    mostrarComponentes();

    do {
        printf("\n--- Menu Estrategico (Componentes: %d/%d) ---\n", numComponentes, MAX_COMPONENTES);
        printf("1. Cadastrar Novo Componente\n");
        printf("--- Opcoes de Estrategia de Montagem (Ordenacao) ---\n");
        printf("2. Bubble Sort (Ordenar por NOME)\n");
        printf("3. Insertion Sort (Ordenar por TIPO)\n");
        printf("4. Selection Sort (Ordenar por PRIORIDADE)\n");
        printf("--- Busca e Ativacao ---\n");
        printf("5. Buscar Componente Chave (Busca Binaria - Requer Opcao 2)\n");
        printf("6. Mostrar Componentes Atuais\n");
        printf("0. Sair e Finalizar Missao\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF);
            opcao = -1; 
        }

        switch (opcao) {
            case 1: 
                cadastrarComponentes(); 
                mostrarComponentes();
                ordenadoPorNome = 0; // Invalida a busca binaria apos a insercao
                break;
            case 2:
                bubbleSortNome(componentes, numComponentes);
                exibirResultadoMedicao("Bubble Sort", "NOME (Alfabetica)");
                mostrarComponentes();
                ordenadoPorNome = 1; // Marca como ordenado por nome
                break;
            case 3:
                insertionSortTipo(componentes, numComponentes);
                exibirResultadoMedicao("Insertion Sort", "TIPO (Alfabetica)");
                mostrarComponentes();
                ordenadoPorNome = 0;
                break;
            case 4:
                selectionSortPrioridade(componentes, numComponentes);
                exibirResultadoMedicao("Selection Sort", "PRIORIDADE (1=Alta)");
                mostrarComponentes();
                ordenadoPorNome = 0;
                break;
            case 5:
                if (ordenadoPorNome == 0) {
                    printf("\n⚠️ ATENCAO: A Busca Binaria requer que os componentes estejam ordenados por NOME (Opcao 2) primeiro! ⚠️\n");
                } else {
                    buscaBinariaPorNome(componentes, numComponentes, CHAVE_BUSCA);
                }
                break;
            case 6:
                mostrarComponentes();
                break;
            case 0:
                printf("\n🚀 Missao Finalizada. O sistema de priorizacao funcionou! 🚀\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
                break;
        }
        
    } while (opcao != 0);

    return 0;
}