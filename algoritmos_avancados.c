#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==========================
// ESTRUTURAS
// ==========================

// Estrutura da Sala
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Estrutura da Pista (nó da árvore BST)
typedef struct Pista {
    char texto[100];
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;


// ==========================
// FUNÇÕES DAS SALAS
// ==========================

// Cria uma nova sala
Sala* criarSala(const char* nome) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Conecta duas salas (esquerda e direita)
void conectarSalas(Sala* origem, Sala* esquerda, Sala* direita) {
    origem->esquerda = esquerda;
    origem->direita = direita;
}


// ==========================
// FUNÇÕES DA ÁRVORE DE PISTAS
// ==========================

// Cria uma nova pista
Pista* criarPista(const char* texto) {
    Pista* nova = (Pista*) malloc(sizeof(Pista));
    strcpy(nova->texto, texto);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Insere uma pista na árvore (ordem alfabética)
Pista* inserirPista(Pista* raiz, const char* texto) {
    if (raiz == NULL) {
        return criarPista(texto);
    }

    int cmp = strcmp(texto, raiz->texto);
    if (cmp < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, texto);
    } else if (cmp > 0) {
        raiz->direita = inserirPista(raiz->direita, texto);
    }
    // se for igual, não insere (evita duplicatas)
    return raiz;
}

// Exibe as pistas em ordem alfabética
void emOrdem(Pista* raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esquerda);
    printf("🔎 %s\n", raiz->texto);
    emOrdem(raiz->direita);
}

// Lista todas as pistas coletadas
void listarPistas(Pista* raiz) {
    printf("\n=== 📜 Pistas Coletadas ===\n");
    if (raiz == NULL) {
        printf("Nenhuma pista coletada ainda.\n");
    } else {
        emOrdem(raiz);
    }
    printf("===========================\n\n");
}


// ==========================
// FUNÇÃO PRINCIPAL DE EXPLORAÇÃO
// ==========================

void explorarSalas(Sala* salaAtual, Pista** arvorePistas) {
    if (salaAtual == NULL) {
        printf("Você chegou a um beco sem saída!\n");
        return;
    }

    printf("\n🏠 Você está na sala: %s\n", salaAtual->nome);

    // Adiciona automaticamente pistas dependendo da sala
    if (strcmp(salaAtual->nome, "Biblioteca") == 0) {
        *arvorePistas = inserirPista(*arvorePistas, "Um livro antigo com anotações estranhas.");
    } else if (strcmp(salaAtual->nome, "Cozinha") == 0) {
        *arvorePistas = inserirPista(*arvorePistas, "Uma faca manchada de algo suspeito.");
    } else if (strcmp(salaAtual->nome, "Sótão") == 0) {
        *arvorePistas = inserirPista(*arvorePistas, "Uma foto rasgada mostrando um rosto desconhecido.");
    } else if (strcmp(salaAtual->nome, "Jardim") == 0) {
        *arvorePistas = inserirPista(*arvorePistas, "Pegadas levando até o portão dos fundos.");
    }

    printf("Ir para (e) esquerda, (d) direita, (p) pistas, ou (s) sair: ");

    char opcao;
    scanf(" %c", &opcao);

    if (opcao == 's') {
        printf("Exploração encerrada. Até a próxima!\n");
        return;
    } else if (opcao == 'e') {
        explorarSalas(salaAtual->esquerda, arvorePistas);
    } else if (opcao == 'd') {
        explorarSalas(salaAtual->direita, arvorePistas);
    } else if (opcao == 'p') {
        listarPistas(*arvorePistas);
        explorarSalas(salaAtual, arvorePistas);
    } else {
        printf("Opção inválida!\n");
        explorarSalas(salaAtual, arvorePistas);
    }
}


// ==========================
// FUNÇÃO MAIN
// ==========================

int main() {
    // Criação das salas fixas
    Sala* hallEntrada = criarSala("Hall de Entrada");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* sotao = criarSala("Sótão");
    Sala* jardim = criarSala("Jardim");

    // Conectando as salas
    conectarSalas(hallEntrada, biblioteca, cozinha);
    conectarSalas(biblioteca, sotao, NULL);
    conectarSalas(cozinha, NULL, jardim);

    // Raiz da árvore de pistas
    Pista* arvorePistas = NULL;

    // Começa a exploração
    explorarSalas(hallEntrada, &arvorePistas);

    // Mostra todas as pistas coletadas ao final
    printf("\n🧩 Revisão final de pistas:\n");
    listarPistas(arvorePistas);

    // Libera memória (básico)
    free(hallEntrada);
    free(biblioteca);
    free(cozinha);
    free(sotao);
    free(jardim);

    // (Liberação completa da árvore de pistas omitida por simplicidade)
    return 0;
}
