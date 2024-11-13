#ifndef ASTEROIDES_H
#define ASTEROIDES_H

#define MAX_ASTEROIDES 10

typedef struct {
    int x, y;
    int ativo;
} Asteroide;

void inicializarAsteroides(Asteroide asteroides[], int maxAsteroides);
void atualizarAsteroides(Asteroide asteroides[], int maxAsteroides);
void desenharAsteroides(const Asteroide asteroides[], int maxAsteroides);

#endif
