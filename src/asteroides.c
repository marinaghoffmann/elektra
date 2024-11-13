#include "asteroides.h"
#include "screen.h"
#include <stdlib.h>
#include "bala.h"

void inicializarAsteroides(Asteroide asteroides[], int maxAsteroides) {
    for (int i = 0; i < maxAsteroides; i++) {
        asteroides[i].ativo = 0;
    }
}

void atualizarAsteroides(Asteroide asteroides[], int maxAsteroides) {
    for (int i = 0; i < maxAsteroides; i++) {
        if (!asteroides[i].ativo && rand() % 20 == 0) {
            asteroides[i].x = rand() % MAXX;
            asteroides[i].y = 0;
            asteroides[i].ativo = 1;
        } else if (asteroides[i].ativo) {
            asteroides[i].y++;
            if (asteroides[i].y >= MAXY) {
                asteroides[i].ativo = 0;
            }
        }
    }
}

// Função para verificar a colisão entre bala e asteroide
void verificarColisaoAsteroide(Bala balas[], int maxBalas, Asteroide asteroides[], int maxAsteroides) {
    for (int i = 0; i < maxBalas; i++) {
        if (balas[i].ativa) {
            for (int j = 0; j < maxAsteroides; j++) {
                if (asteroides[j].ativo) {
                    // Verifica se a bala atingiu o asteroide
                    if (balas[i].x == asteroides[j].x && balas[i].y == asteroides[j].y) {
                        // A bala atingiu o asteroide, faz o asteroide subir
                        asteroides[j].y--;  // Faz o asteroide subir
                        balas[i].ativa = 0;  // Desativa a bala
                    }
                }
            }
        }
    }
}

void desenharAsteroides(const Asteroide asteroides[], int maxAsteroides) {
    for (int i = 0; i < maxAsteroides; i++) {
        if (asteroides[i].ativo) {
            screenGotoxy(asteroides[i].x, asteroides[i].y);
            screenSetColor(BLUE, DARKGRAY);
            printf("*0*");
        }
    }
}

