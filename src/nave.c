#include "nave.h"
#include "screen.h"

void inicializarNave(Nave *nave) {
    nave->x = NAVE_X_INICIAL;
    nave->y = NAVE_Y_INICIAL;
}

void moverNave(Nave *nave, int direcao) {
    if (direcao == -1 && nave->x > 0) {
        nave->x--;  // Move para a esquerda
    } else if (direcao == 1 && nave->x < MAXX - 1) {
        nave->x++;  // Move para a direita
    }
}

void desenharNave(const Nave *nave) {
    screenGotoxy(nave->x, nave->y);
    screenSetColor(LIGHTBLUE, DARKGRAY);
    printf("  ^  ");
    
    screenGotoxy(nave->x, nave->y + 1);
    printf(" /_\\ ");
    
    screenGotoxy(nave->x, nave->y + 2);
    printf("|_o_|");
}
