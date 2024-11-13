// bala.h
#ifndef BALA_H
#define BALA_H

#define MAX_BALAS 1000000

typedef struct {
    int x, y;
    int ativa;  // 0 para inativa, 1 para ativa
} Bala;

extern Bala balas[MAX_BALAS];  // Declaração da variável global de balas

void inicializarBalas(Bala *balas, int maxBalas);
void dispararBala(Bala *balas, int maxBalas, int x, int y);
void atualizarBalas(Bala *balas, int maxBalas);

#endif
