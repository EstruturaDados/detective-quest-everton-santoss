#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

// ==============================
// 📂 ESTRUTURAS
// ==============================

// Estrutura da pista (para reutilizar)
typedef struct Pista {
    char texto[100];
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;

// Nó de lista de pistas associadas a um suspeito
typedef struct NodoPista {
    char texto[100];
    struct NodoPista* prox;
} NodoPista;

// Estrutura do suspeito (usada na tabela hash)
typedef struct Suspeito {
    char nome[50];
    int contador; // quantas vezes foi associado a uma pista
    NodoPista* pistas;
    struct Suspeito* prox; // para colisões (lista encadeada)
} Suspeito;


// ==============================
// 🔢 FUNÇÕES DA TABELA HASH
// ==============================

// Função de hash simples: soma dos valores ASCII da primeira letra
int hashFunc(const char* nome) {
    return (nome[0] % TAM_HASH);
}

// Inicializa tabela hash com NULL
void inicializarHash(Suspeito* tabela[]) {
    for (int i = 0; i < TAM_HASH; i++) {
        tabela[i] = NULL;
    }
}

// Cria um novo suspeito
Suspeito* criarSuspeito(const char* nome) {
    Suspeito* novo = (Suspeito*) malloc(sizeof(Suspeito));
    strcpy(novo->nome, nome);
    novo->contador = 0;
    novo->pistas = NULL;
    novo->prox = NULL;
    return novo;
}

// Busca um suspeito na tabela hash
Suspeito* buscarSuspeito(Suspeito* tabela[], const char* nome) {
    int indice = hashFunc(nome);
    Suspeito* atual = tabela[indice];
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

// Insere um novo suspeito na tabela hash (caso não exista)
Suspeito* inserirSuspeito(Suspeito* tabela[], const char* nome) {
    int indice = hashFunc(nome);
    Suspeito* existente = buscarSuspeito(tabela, nome);

    if (existente != NULL) {
        return existente;
    }

    Suspeito* novo = criarSuspeito(nome);
    novo->prox = tabela[indice]; // trata colisão via encadeamento
    tabela[indice] = novo;
    return novo;
}

// Associa uma pista a um suspeito
void inserirHash(Suspeito* tabela[], const char* suspeitoNome, const char* pistaTexto) {
    Suspeito* suspeito = inserirSuspeito(tabela, suspeitoNome);

    // Cria novo nó de pista
    NodoPista* novaPista = (NodoPista*) malloc(sizeof(NodoPista));
    strcpy(novaPista->texto, pistaTexto);
    novaPista->prox = suspeito->pistas;
    suspeito->pistas = novaPista;

    suspeito->contador++;
}

// Lista todas as associações (suspeito -> pistas)
void listarAssociacoes(Suspeito* tabela[]) {
    printf("\n=== 🔍 Relação de Suspeitos e Pistas ===\n");
    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito* atual = tabela[i];
        while (atual != NULL) {
            printf("\n👤 Suspeito: %s (mencionado %d vezes)\n", atual->nome, atual->contador);
            NodoPista* pista = atual->pistas;
            while (pista != NULL) {
                printf("   - %s\n", pista->texto);
                pista = pista->prox;
            }
            atual = atual->prox;
        }
    }
    printf("=======================================\n");
}

// Retorna o suspeito mais provável (com maior contador)
Suspeito* suspeitoMaisProvavel(Suspeito* tabela[]) {
    Suspeito* maisProvavel = NULL;
    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito* atual = tabela[i];
        while (atual != NULL) {
            if (maisProvavel == NULL || atual->contador > maisProvavel->contador) {
                maisProvavel = atual;
            }
            atual = atual->prox;
        }
    }
    return maisProvavel;
}


// ==============================
// 🎯 DEMONSTRAÇÃO
// ==============================
int main() {
    Suspeito* tabela[TAM_HASH];
    inicializarHash(tabela);

    // Simula pistas encontradas e suas associações
    inserirHash(tabela, "Everton", "Uma faca manchada de algo suspeito.");
    inserirHash(tabela, "Coronel", "Um livro antigo com anotações estranhas.");
    inserirHash(tabela, "Seu Prata", "Pegadas levando até o portão dos fundos.");
    inserirHash(tabela, "Dedim golveia", "Uma foto rasgada mostrando um rosto desconhecido.");
    inserirHash(tabela, "Santos", "Pegadas levando até o portão dos fundos.");
    inserirHash(tabela, "Teste", "Uma luva encontrada perto da janela quebrada.");

    // Exibe associações
    listarAssociacoes(tabela);

    // Mostra o suspeito mais provável
    Suspeito* principal = suspeitoMaisProvavel(tabela);
    if (principal != NULL) {
        printf("\n🕵️ Suspeito mais provável: %s (%d pistas associadas)\n",
               principal->nome, principal->contador);
    } else {
        printf("\nNenhum suspeito encontrado!\n");
    }

    return 0;
}
