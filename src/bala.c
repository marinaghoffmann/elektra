#include "bala.h"
#include "asteroides.h"
#include <stdlib.h>  // Para a função abs
#include <math.h>

Bala balas[MAX_BALAS];  // Inicializa a lista de balas

void inicializarBalas(Bala *balas, int maxBalas) {
    for (int i = 0; i < maxBalas; i++) {
        balas[i].ativa = 0;  // Marca todas as balas como inativas inicialmente
    }
}

void dispararBala(Bala *balas, int maxBalas, int x, int y) {
    for (int i = 0; i < maxBalas; i++) {
        if (balas[i].ativa == 0) {  // Se a bala está inativa
            balas[i].x = x;
            balas[i].y = y - 1;  // A bala começa acima da nave
            balas[i].ativa = 1;  // Marca a bala como ativa
            break;
        }
    }
}

void atualizarBalas(Bala *balas, int maxBalas) {
    for (int i = 0; i < maxBalas; i++) {
        if (balas[i].ativa) {
            balas[i].y--;  // Move a bala para cima
            if (balas[i].y < 0) {
                balas[i].ativa = 0;  // Marca a bala como inativa se sair da tela
            }
        }
    }
}

void verificarColisaoComAsteroides(Bala *balas, int maxBalas, Asteroide *asteroides, int maxAsteroides, int distancia_colisao) { //GNT< ESTUDAR ESSA FUNCAOO
    for (int i = 0; i < maxBalas; i++) {
        if (balas[i].ativa) {  // Verifica se a bala está ativa
            for (int j = 0; j < maxAsteroides; j++) {
                if (asteroides[j].ativo) {  // Verifica se o asteroide está ativo
                    // Calcula a diferença de distância entre a bala e o asteroide
                    int distanciaX = abs(balas[i].x - asteroides[j].x);
                    int distanciaY = abs(balas[i].y - asteroides[j].y);

                    // Verifica se a distância está dentro da área de colisão
                    if (distanciaX <= distancia_colisao && distanciaY <= distancia_colisao) {
                        // Colisão detectada, destrói a bala e o asteroide
                        asteroides[j].ativo = 0;  // Remove o asteroide
                        balas[i].ativa = 0;  // Remove a bala
                        break;  // Sai do loop de asteroides
                    }
                }
            }
        }
    }
}
