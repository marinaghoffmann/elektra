#ifndef NAVE_H
#define NAVE_H

#define NAVE_X_INICIAL 40
#define NAVE_Y_INICIAL (MAXY - 1)  // Posiciona a nave na parte inferior da tela

typedef struct {
    int x, y;   // Posições
} Nave;

void inicializarNave(Nave *nave);
void moverNave(Nave *nave, int direcao);
void desenharNave(const Nave *nave);

#endif
