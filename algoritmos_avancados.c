#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da Sala
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Função para criar uma sala com nome
Sala* criarSala(const char* nome) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Função para conectar duas salas
void conectarSalas(Sala* origem, Sala* esquerda, Sala* direita) {
    origem->esquerda = esquerda;
    origem->direita = direita;
}

// Função para explorar as salas (recursiva)
void explorarSalas(Sala* salaAtual) {
    if (salaAtual == NULL) {
        printf("Você chegou a um beco sem saída!\n");
        return;
    }

    printf("\nVocê está na sala: %s\n", salaAtual->nome);
    printf("Ir para (e) esquerda, (d) direita, ou (s) sair: ");

    char opcao;
    scanf(" %c", &opcao);

    if (opcao == 's') {
        printf("Exploração encerrada. Até a próxima!\n");
        return;
    } else if (opcao == 'e') {
        explorarSalas(salaAtual->esquerda);
    } else if (opcao == 'd') {
        explorarSalas(salaAtual->direita);
    } else {
        printf("Opção inválida!\n");
        explorarSalas(salaAtual);
    }
}

int main() {
    // Criação das salas fixas
    Sala* hallEntrada = criarSala("Hall de Entrada");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* sotao = criarSala("Sótão");
    Sala* jardim = criarSala("Jardim");

    // Conectando as salas (formando uma pequena árvore)
    conectarSalas(hallEntrada, biblioteca, cozinha);
    conectarSalas(biblioteca, sotao, NULL);
    conectarSalas(cozinha, NULL, jardim);

    // Começa a exploração
    explorarSalas(hallEntrada);

    // Libera a memória (opcional)
    free(hallEntrada);
    free(biblioteca);
    free(cozinha);
    free(sotao);
    free(jardim);

    return 0;
}