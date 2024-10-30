#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

void telainicial() {
    screenClear();

    screenGotoxy(MINX + 5, MINY + 2);
    screenSetColor(LIGHTCYAN, BLACK);
    printf("███████╗██╗░░░░░███████╗██╗░░██╗████████╗██████╗░░█████╗░\n");

    screenGotoxy(MINX + 5, MINY + 3);
    screenSetColor(LIGHTCYAN, BLACK);
    printf("██╔════╝██║░░░░░██╔════╝██║░██╔╝╚══██╔══╝██╔══██╗██╔══██╗\n");

    screenGotoxy(MINX + 5, MINY + 4);
    screenSetColor(LIGHTCYAN, BLACK);
    printf("█████╗░░██║░░░░░█████╗░░█████═╝░░░░██║░░░██████╔╝███████║\n");

    screenGotoxy(MINX + 5, MINY + 5);
    screenSetColor(LIGHTCYAN, BLACK);
    printf("██╔══╝░░██║░░░░░██╔══╝░░██╔═██╗░░░░██║░░░██╔══██╗██╔══██║\n");

    screenGotoxy(MINX + 5, MINY + 6);
    screenSetColor(LIGHTCYAN, BLACK);
    printf("███████╗███████╗███████╗██║░╚██╗░░░██║░░░██║░░██║██║░░██║\n");

    screenGotoxy(MINX + 5, MINY + 7);
    screenSetColor(LIGHTCYAN, BLACK);
    printf("╚══════╝╚══════╝╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝\n");


    screenGotoxy(MINX + 5, MINY + 10);
    screenSetColor(BLUE, BLACK);
    printf("Proteja o planeta da tempestade de asteroides!");

    screenGotoxy(MINX + 5, MINY + 11);
    screenSetColor(BLUE, BLACK);
    printf("Pressione 'C' para começar ou 'S' para sair.");

    screenGotoxy(MINX + 5, MINY + 12);
    printf("Destrua os asteroides antes que eles atinjam a Terra.");

    screenGotoxy(MINX + 5, MINY + 13);
    printf("CUIDADO! Não seja atingido.");

    screenGotoxy(MINX + 5, MINY + 14);
    printf("Use as teclas de seta para mover a nave e espaço para atirar.");

    screenGotoxy(MINX + 5, MINY + 15);
    printf("Aperte 'C' para começar. Boa sorte!...");

    fflush(stdout);  

    while (1) {
        if (keyhit()) {
            char ch = readch();
            if (ch == 'C' || ch == 'c') {
                return; // sair da tela inicial para o jogo -> por enquanto n funciona
            } else if (ch == 'S' || ch == 's') {
                exit(0); // sair do jogo
            }
        }
    }
}


int main() {
    telainicial();
    
    return 0;
}
