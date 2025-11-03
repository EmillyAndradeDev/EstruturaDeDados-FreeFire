// Mochila com VETOR (Lista Sequencial), incluindo Ordenação e Busca Binária.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Capacidade máxima da mochila (tamanho fixo)
#define MAX_ITENS 10

// Variáveis Globais para Contagem de Operações (Requisito 6)
long long comparacoesSequencial = 0;
long long comparacoesBinaria = 0;

// Criação da Struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Variáveis de Estado 
Item mochilaVetor[MAX_ITENS];
int numItensVetor = 0; // Tamanho lógico

// Função utilitária para exibir um item.
void exibirItem(const Item *item) {
    printf("Nome: %-28s | Tipo: %-9s | Qtd: %-4d\n", 
           item->nome, item->tipo, item->quantidade);
}

// Funções da Mochila

void inserirItemVetor() {
    if (numItensVetor >= MAX_ITENS) {
        printf("\n🚫 Mochila Cheia. Nao e possivel cadastrar mais itens. 🚫\n");
        return;
    }

    printf("\n--- Cadastro (Vetor) ---\n");
    Item novoItem;

    printf("Nome do Item: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    if (fgets(novoItem.nome, sizeof(novoItem.nome), stdin) != NULL) {
        novoItem.nome[strcspn(novoItem.nome, "\n")] = 0;
    }

    printf("Tipo do Item (ex: arma, municao): ");
    scanf("%s", novoItem.tipo);
    
    printf("Quantidade: ");
    while (scanf("%d", &novoItem.quantidade) != 1 || novoItem.quantidade <= 0) {
        printf("Quantidade invalida. Digite um numero positivo: ");
        while ((c = getchar()) != '\n' && c != EOF); 
    }
    
    mochilaVetor[numItensVetor] = novoItem;
    numItensVetor++;
    printf("\n✅ Item cadastrado no VETOR com sucesso! ✅\n");
}

int buscarSequencialVetor(const char *nomeBusca) {
    comparacoesSequencial = 0;
    for (int i = 0; i < numItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            return i;
        }
    }
    return -1;
}

void removerItemVetor() {
    if (numItensVetor == 0) {
        printf("\n⚠️ Mochila Vazia. ⚠️\n");
        return;
    }

    char nomeRemover[30];
    printf("\n--- Remocao (Vetor) ---\n");
    printf("Digite o nome exato do item para remover: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    if (fgets(nomeRemover, sizeof(nomeRemover), stdin) != NULL) {
        nomeRemover[strcspn(nomeRemover, "\n")] = 0;
    }
    
    int indice = buscarSequencialVetor(nomeRemover);

    if (indice != -1) {
        // Deslocamento de elementos para preencher a lacuna
        for (int i = indice; i < numItensVetor - 1; i++) {
            mochilaVetor[i] = mochilaVetor[i + 1];
        }
        numItensVetor--;
        printf("\n✅ Item '%s' removido do VETOR com sucesso! ✅\n", nomeRemover);
    } else {
        printf("\n❌ Item '%s' nao encontrado no VETOR. ❌\n", nomeRemover);
    }
}

void listarItensVetor() {
    printf("\n-------- Mochila com VETOR (Lista Sequencial) --------\n");
    if (numItensVetor == 0) {
        printf("A mochila (Vetor) esta vazia.\n");
        return;
    }
    
    printf(" Total de Itens: %d/%d\n", numItensVetor, MAX_ITENS);
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < numItensVetor; i++) {
        printf(" %-2d| ", i + 1);
        exibirItem(&mochilaVetor[i]);
    }
    printf("------------------------------------------------------------\n");
}

void ordenarVetor() {
    if (numItensVetor <= 1) return;

    Item temp;
    // Bubble Sort
    for (int i = 0; i < numItensVetor - 1; i++) {
        for (int j = 0; j < numItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("\n✅ Mochila (Vetor) ordenada por nome! ✅\n");
}

int buscarBinariaVetor(const char *nomeBusca) {
    comparacoesBinaria = 0;
    int esquerda = 0;
    int direita = numItensVetor - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        int resultado = strcmp(mochilaVetor[meio].nome, nomeBusca);
        comparacoesBinaria++; 

        if (resultado == 0) {
            return meio; 
        }
        
        if (resultado > 0) {
            direita = meio - 1;
        } else {
            esquerda = meio + 1;
        }
    }
    return -1; 
}

// Função Principal (Menu)

int main() {
    int opcao;
    char nomeBusca[30];
    int indice;

    printf("----------------------------------------------------\n");
    printf("   🛠️  NIVEL AVENTUREIRO: MOCHILA COM VETOR 🛠️\n");
    printf("  Lista Sequencial com Ordenacao e Busca Binaria.\n");
    printf("----------------------------------------------------\n");

    do {
        printf("\n--- Menu Vetor ---\n");
        printf("1. Inserir Novo Item\n");
        printf("2. Remover Item pelo Nome\n");
        printf("3. Listar Todos os Itens\n");
        printf("4. Buscar Sequencial por Nome (Comparações: %lld)\n", comparacoesSequencial);
        printf("5. Ordenar Itens (Bubble Sort)\n");
        printf("6. Buscar Binaria por Nome (Comparações: %lld)\n", comparacoesBinaria);
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF);
            opcao = -1; 
        }

        switch (opcao) {
            case 1: inserirItemVetor(); listarItensVetor(); break;
            case 2: removerItemVetor(); listarItensVetor(); break;
            case 3: listarItensVetor(); break;
            case 4:
                if (numItensVetor == 0) { printf("\n⚠️ Vetor Vazio. ⚠️\n"); break; }
                printf("Nome do item para busca sequencial: ");
                int c; while ((c = getchar()) != '\n' && c != EOF);
                if (fgets(nomeBusca, sizeof(nomeBusca), stdin) != NULL) { nomeBusca[strcspn(nomeBusca, "\n")] = 0; }
                indice = buscarSequencialVetor(nomeBusca);
                if (indice != -1) {
                    printf("\n✅ Item encontrado! Comparações: %lld ✅\n", comparacoesSequencial);
                    exibirItem(&mochilaVetor[indice]);
                } else {
                    printf("\n❌ Item nao encontrado. Comparações: %lld ❌\n", comparacoesSequencial);
                }
                break;
            case 5: ordenarVetor(); listarItensVetor(); break;
            case 6:
                if (numItensVetor == 0) { printf("\n⚠️ Vetor Vazio. ⚠️\n"); break; }
                printf("Nome do item para busca binaria: ");
                int d; while ((d = getchar()) != '\n' && d != EOF);
                if (fgets(nomeBusca, sizeof(nomeBusca), stdin) != NULL) { nomeBusca[strcspn(nomeBusca, "\n")] = 0; }
                
                // Verifica se a busca binária é válida (requer ordenação prévia)
                // Uma verificação simples: se o vetor está ordenado, o primeiro item deve ser menor ou igual ao segundo (se houver)
                if (numItensVetor > 1 && strcmp(mochilaVetor[0].nome, mochilaVetor[1].nome) > 0) {
                     printf("\n⚠️ ATENCAO: O vetor nao parece estar ordenado. Ordene o vetor primeiro (Opcao 5). ⚠️\n");
                     break;
                }

                indice = buscarBinariaVetor(nomeBusca);
                if (indice != -1) {
                    printf("\n✅ Item encontrado! Comparações: %lld ✅\n", comparacoesBinaria);
                    exibirItem(&mochilaVetor[indice]);
                } else {
                    printf("\n❌ Item nao encontrado. Comparações: %lld ❌\n", comparacoesBinaria);
                }
                break;
            case 0: printf("\n👋 Saindo da Mochila Vetor. 👋\n"); break;
            default: printf("\nOpcao invalida.\n"); break;
        }
    } while (opcao != 0);

    return 0;
}