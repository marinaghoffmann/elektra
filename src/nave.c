#include "nave.h"
#include "screen.h"
#include "keyboard.h"
#include "asteroides.h"
#include <unistd.h>

#define WIDTH 130
#define HEIGHT 40

void desenharNave(int x, int y) {
    screenSetColor(LIGHTCYAN, DARKGRAY);

    screenGotoxy(x, y);     printf("  ^  ");
    screenGotoxy(x, y + 1); printf(" /_\\ ");
    screenGotoxy(x, y + 2); printf("|_o_|");

    screenSetNormal();
}

void apagaNave(int x, int y) {
    for (int i = 0; i < 3; i++) {
        screenGotoxy(x, y + i);
        printf("      ");
    }
}

void QuedasDosAsteroides() {
    atualizarAsteroides();
}
