// Bibliotecas necessárias
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// capacidade da mochila
#define MAX_ITENS 10

// 1. Criação da Struct Item

// A struct Item armazena as informações essenciais de cada objeto coletado.
typedef struct {
    char nome[30];      // Nome do item 
    char tipo[20];      // Tipo do item 
    int quantidade;     // Quantidade 
} Item;


// Variáveis Globais

// Vetor de structs para armazenar os itens na mochila (Lista Estática/Sequencial).
Item mochila[MAX_ITENS];
// Variável que rastreia o número atual de itens na mochila (tamanho lógico).
int numItens = 0;

// Funções de Gerenciamento

//Função para inserir um novo item na mochila (Cadastro de itens).

void inserirItem() {
    // Verifica se a mochila está cheia
    if (numItens >= MAX_ITENS) {
        printf("\n🚫 Mochila Cheia! Nao e possivel cadastrar mais itens. 🚫\n");
        return;
    }

    // Leitura dos dados do novo item
    printf("\n--- Cadastro de Novo Item ---\n");
    
    // Leitura do nome
    printf("Nome do Item (max 29 caracteres): ");
    // Limpa o buffer de entrada para evitar problemas com leituras anteriores
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    // fgets e melhor para ler strings com espacos e evitar buffer overflow
    if (fgets(mochila[numItens].nome, sizeof(mochila[numItens].nome), stdin) != NULL) {
        // Remove o newline ( '\n' ) que o fgets adiciona
        mochila[numItens].nome[strcspn(mochila[numItens].nome, "\n")] = 0;
    }
    
    // Leitura do tipo
    printf("Tipo do Item (ex: arma, municao, cura): ");
    // Usa scanf para simplificar a leitura de uma unica palavra para o tipo
    scanf("%s", mochila[numItens].tipo);
    
    // Leitura da quantidade
    printf("Quantidade: ");
    // Loop para garantir que a quantidade e um numero positivo valido
    while (scanf("%d", &mochila[numItens].quantidade) != 1 || mochila[numItens].quantidade <= 0) {
        printf("Quantidade invalida. Digite um numero positivo: ");
        // Limpa o buffer de entrada apos erro de leitura
        while ((c = getchar()) != '\n' && c != EOF); 
    }
    
    // O item foi cadastrado com sucesso, incrementa o contador de itens
    numItens++;
    printf("\n✅ Item cadastrado com sucesso! ✅\n");
}


int buscarItem(const char *nomeBusca) {
    // Percorre o vetor até a posicao numItens (tamanho lógico)
    for (int i = 0; i < numItens; i++) {
        // Compara a string de busca com o nome do item no inventario, ignorando case (strcasecmp e ideal, mas nao padrao C)
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            return i; // Item encontrado
        }
    }
    return -1; // Item não encontrado
}

// Função para remover um item existente da mochila
void removerItem() {
    char nomeRemover[30];
    
    if (numItens == 0) {
        printf("\n⚠️ Mochila vazia. Nada para remover. ⚠️\n");
        return;
    }

    printf("\n--- Remocao de Item ---\n");
    printf("Digite o nome exato do item para remover: ");
    // Limpa o buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    // Lê o nome do item a ser removido
    if (fgets(nomeRemover, sizeof(nomeRemover), stdin) != NULL) {
        nomeRemover[strcspn(nomeRemover, "\n")] = 0;
    }
    
    // Busca sequencial do item
    int indice = buscarItem(nomeRemover);

    if (indice != -1) {
        // Item encontrado. Remove-o movendo os elementos seguintes uma posição para tras
        for (int i = indice; i < numItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        
        // Decrementa o tamanho logico da lista
        numItens--;
        printf("\n✅ Item '%s' removido com sucesso! ✅\n", nomeRemover);
    } else {
        printf("\n❌ Item '%s' nao encontrado na mochila. ❌\n", nomeRemover);
    }
}


void listarItens() {
    printf("\n========== Conteudo da Mochila (Inventario) ==========\n");
    
    if (numItens == 0) {
        printf("A mochila esta vazia. Hora de coletar recursos!\n");
        printf("======================================================\n");
        return;
    }
    
    // Cabecalho da tabela
    printf(" Total de Itens: %d/%d\n", numItens, MAX_ITENS);
    printf("------------------------------------------------------\n");
    printf(" # | Nome                         | Tipo      | Qtd \n");
    printf("---|------------------------------|-----------|-----\n");
    
    // Percorre e exibe cada item
    for (int i = 0; i < numItens; i++) {
        printf(" %-2d| %-28s | %-9s | %-4d\n", 
               i + 1, 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
    
    printf("------------------------------------------------------\n");
}


void buscarItemPorNome() {
    char nomeBusca[30];
    
    if (numItens == 0) {
        printf("\n⚠️ Mochila vazia. Nao ha itens para buscar. ⚠️\n");
        return;
    }

    printf("\n--- Busca de Item ---\n");
    printf("Digite o nome exato do item a buscar: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    if (fgets(nomeBusca, sizeof(nomeBusca), stdin) != NULL) {
        nomeBusca[strcspn(nomeBusca, "\n")] = 0;
    }

    // Chama a funcao de busca sequencial
    int indice = buscarItem(nomeBusca);

    if (indice != -1) {
        // Item encontrado
        printf("\n✅ Item encontrado! Detalhes:\n");
        printf("----------------------------------\n");
        printf("Nome:       %s\n", mochila[indice].nome);
        printf("Tipo:       %s\n", mochila[indice].tipo);
        printf("Quantidade: %d\n", mochila[indice].quantidade);
        printf("----------------------------------\n");
    } else {
        // Item nao encontrado
        printf("\n❌ Item '%s' nao encontrado na mochila. ❌\n", nomeBusca);
    }
}


int main() {
    int opcao;
    
    printf("-------------------------------------------------------\n");
    printf("       🎮 MOCHILA INICIAL 🎮\n");
    printf("  A Mochila tem capacidade maxima para %d itens.\n", MAX_ITENS);
    printf("-------------------------------------------------------\n");

    do {
        // Exibe o menu principal para orientar o jogador
        printf("\n--- Menu Principal ---\n");
        printf("1. Inserir Novo Item (Cadastrar)\n");
        printf("2. Remover Item pelo Nome\n");
        printf("3. Listar Todos os Itens\n");
        printf("4. Buscar Item pelo Nome\n");
        printf("0. Sair do Sistema (Concluir Loot)\n");
        printf("Escolha uma opcao: ");
        
        // Leitura da opcao, garantindo que seja um numero
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer de entrada se a leitura falhar
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opcao = -1; // Forca uma opcao invalida
        }

        // Fluxo de execucao baseado na escolha
        switch (opcao) {
            case 1:
                inserirItem();
                listarItens(); // Listagem após cada operação
                break;
            case 2:
                removerItem();
                listarItens(); // Listagem após cada operação
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItemPorNome();
                break;
            case 0:
                printf("\n👋 Fechando o Inventario. Boa sorte na sua jornada! 👋\n");
                break;
            default:
                printf("\nOpcao invalida. Por favor, escolha uma das opcoes do menu.\n");
                break;
        }
        
    } while (opcao != 0); // Continua até que o jogador escolha a opção 0

    return 0;
}