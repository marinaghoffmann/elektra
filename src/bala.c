// bala.c
#include "bala.h"

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
