// Mochila com LISTA ENCADEDADA (Estrutura Dinâmica).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variável Global para Contagem de Operações (Busca Sequencial)
long long comparacoesSequencial = 0;

// Criação das Structs
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct para o Nó da Lista Encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

//  Variáveis de Estado 
No* cabeca = NULL; // Ponteiro para o início da lista

// Função utilitária para exibir um item.
void exibirItem(const Item *item) {
    printf("Nome: %-28s | Tipo: %-9s | Qtd: %-4d\n", 
           item->nome, item->tipo, item->quantidade);
}

// Funções da Mochila com Lista Encadeada

void inserirItemLista() {
    printf("\n--- Cadastro (Lista Encadeada) ---\n");
    
    // Aloca memoria para o novo No (Alocacao Dinamica)
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\n❌ Erro de alocacao de memoria. ❌\n");
        return;
    }

    // Leitura dos dados
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
    
    // Configura o novo Nó
    novoNo->dados = novoItem;
    
    // Insere no início (mais eficiente para Lista Encadeada)
    novoNo->proximo = cabeca;
    cabeca = novoNo;
    
    printf("\n✅ Item cadastrado na LISTA ENCAD. com sucesso! ✅\n");
}

No* buscarSequencialLista(const char *nomeBusca) {
    comparacoesSequencial = 0;
    No* atual = cabeca;
    
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void removerItemLista() {
    if (cabeca == NULL) {
        printf("\n⚠️ Lista Encadeada Vazia. ⚠️\n");
        return;
    }

    char nomeRemover[30];
    printf("\n--- Remocao (Lista Encadeada) ---\n");
    printf("Digite o nome exato do item para remover: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    if (fgets(nomeRemover, sizeof(nomeRemover), stdin) != NULL) {
        nomeRemover[strcspn(nomeRemover, "\n")] = 0;
    }
    
    No* atual = cabeca;
    No* anterior = NULL;

    // Busca o nó a ser removido
    while (atual != NULL && strcmp(atual->dados.nome, nomeRemover) != 0) {
        comparacoesSequencial++;
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (atual != NULL) {
        if (anterior == NULL) {
            cabeca = atual->proximo; // Remove a cabeça
        } else {
            anterior->proximo = atual->proximo; // Remove um nó do meio/fim
        }
        
        free(atual); // Libera a memória alocada dinamicamente
        printf("\n✅ Item '%s' removido da LISTA ENCAD. com sucesso! ✅\n", nomeRemover);
    } else {
        printf("\n❌ Item '%s' nao encontrado na LISTA ENCAD. ❌\n", nomeRemover);
    }
}

void listarItensLista() {
    printf("\n======= Mochila com LISTA ENCAD. (Estrutura Dinamica) =======\n");
    if (cabeca == NULL) {
        printf("A mochila (Lista Encadeada) esta vazia.\n");
        printf("============================================================\n");
        return;
    }
    
    No* atual = cabeca;
    int i = 1;
    printf("------------------------------------------------------------\n");
    while (atual != NULL) {
        printf(" %-2d| ", i++);
        exibirItem(&atual->dados);
        atual = atual->proximo;
    }
    printf("------------------------------------------------------------\n");
}

void liberarLista() {
    No* atual = cabeca;
    No* proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    cabeca = NULL;
}

//  Função Principal (Menu)

int main() {
    int opcao;
    char nomeBusca[30];
    No* noEncontrado;

    printf("----------------------------------------------------\n");
    printf("   🛠️  NIVEL AVENTUREIRO: MOCHILA COM LISTA ENCAD. 🛠️\n");
    printf("  Estrutura Dinamica. Foco na alocacao e remocao de nos.\n");
    printf("----------------------------------------------------\n");

    do {
        printf("\n--- Menu Lista Encadeada ---\n");
        printf("1. Inserir Novo Item (Inicio)\n");
        printf("2. Remover Item pelo Nome\n");
        printf("3. Listar Todos os Itens\n");
        printf("4. Buscar Sequencial por Nome (Comparações: %lld)\n", comparacoesSequencial);
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF);
            opcao = -1; 
        }

        switch (opcao) {
            case 1: inserirItemLista(); listarItensLista(); break;
            case 2: removerItemLista(); listarItensLista(); break;
            case 3: listarItensLista(); break;
            case 4:
                if (cabeca == NULL) { printf("\n⚠️ Lista Vazia. ⚠️\n"); break; }
                printf("Nome do item para busca sequencial: ");
                int c; while ((c = getchar()) != '\n' && c != EOF);
                if (fgets(nomeBusca, sizeof(nomeBusca), stdin) != NULL) { nomeBusca[strcspn(nomeBusca, "\n")] = 0; }
                
                noEncontrado = buscarSequencialLista(nomeBusca);
                
                if (noEncontrado != NULL) {
                    printf("\n✅ Item encontrado! Comparações: %lld ✅\n", comparacoesSequencial);
                    exibirItem(&noEncontrado->dados);
                } else {
                    printf("\n❌ Item nao encontrado. Comparações: %lld ❌\n", comparacoesSequencial);
                }
                break;
            case 0: 
                printf("\n👋 Saindo da Mochila Lista Encadeada. Liberando memoria... 👋\n"); 
                liberarLista();
                break;
            default: printf("\nOpcao invalida.\n"); break;
        }
    } while (opcao != 0);

    return 0;
}