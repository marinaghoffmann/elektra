#include "asteroides.h"
#include <stdlib.h>
#include "screen.h"

#define MAX_ASTEROIDES 10
#define MAXX 120
#define MINX 1
#define MAXY 40
#define MINY 1

struct Asteroide {
    int x;
    int y;
};

// Array de asteroides como variável global
struct Asteroide asteroides[MAX_ASTEROIDES];

void inicializarAsteroides() {
    // Definir uma área segura para o nascimento dos asteroides, evitando as bordas laterais
    for (int i = 0; i < MAX_ASTEROIDES; i++) {
        // Gerar uma coordenada X aleatória que não colida com as bordas laterais (evitando as colunas 1 e WIDTH)
        // Como o asteroide ocupa três caracteres (*0*), precisamos garantir que ele não ultrapasse a borda
        asteroides[i].x = rand() % (MAXX - 2 - 2) + 2; // Limita a área de X para que o *0* não ultrapasse a borda lateral

        // Gerar uma coordenada Y aleatória dentro do topo da tela, mas dentro da área visível
        asteroides[i].y = rand() % (MAXY / 4) + 1; // Exemplo: aparecer na parte superior, mas não ultrapassar 1/4 da altura total

        // Garantir que o asteróide não vá para a borda
        if (asteroides[i].x <= 1) {
            asteroides[i].x = 2; // Ajusta a posição mínima para evitar que o *0* ultrapasse a borda esquerda
        }
        if (asteroides[i].x >= MAXX - 2) {
            asteroides[i].x = MAXX - 3; // Ajusta a posição máxima para evitar que o *0* ultrapasse a borda direita
        }
    }
}

void desenharAsteroides() {
    for (int i = 0; i < MAX_ASTEROIDES; i++) {
        screenGotoxy(asteroides[i].x, asteroides[i].y);
        printf("*0*");
    }
}

void atualizarAsteroides() {
    // Apaga a posição atual dos asteroides
    for (int i = 0; i < MAX_ASTEROIDES; i++) {
        screenGotoxy(asteroides[i].x, asteroides[i].y);
        printf("   ");
        
        // Move o asteroide para baixo
        asteroides[i].y += 1;

        // Se o asteroide sair da tela, reposiciona no topo com nova posição horizontal
        if (asteroides[i].y >= MAXY) {
            asteroides[i].y = MINY;
            asteroides[i].x = rand() % (MAXX - MINX) + MINX;
        }
    }
    desenharAsteroides();  // redesenha os asteroides em suas novas posições
}