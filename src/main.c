#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "asteroides.h"
#include "bala.h"
#include "nave.h"

// Função que exibe a tela inicial do jogo
void telainicial() {
    screenClear(); // Limpa a tela antes de exibir a tela inicial

    screenGotoxy(MINX + 25, MINY + 10);
    screenSetColor(WHITE, BLACK);
    printf("███████╗██╗░░░░░███████╗██╗░░██╗████████╗██████╗░░█████╗░\n");
    screenGotoxy(MINX + 25, MINY + 11);
    screenSetColor(WHITE, BLACK);
    printf("██╔════╝██║░░░░░██╔════╝██║░██╔╝╚══██╔══╝██╔══██╗██╔══██╗\n");

    screenGotoxy(MINX + 25, MINY + 12);
    screenSetColor(WHITE, BLACK);
    printf("█████╗░░██║░░░░░█████╗░░█████═╝░░░░██║░░░██████╔╝███████║\n");
    screenGotoxy(MINX + 25, MINY + 13);
    screenSetColor(WHITE, BLACK);
    printf("██╔══╝░░██║░░░░░██╔══╝░░██╔═██╗░░░░██║░░░██╔══██╗██╔══██║\n");
    screenGotoxy(MINX + 25, MINY + 14);
    screenSetColor(WHITE, BLACK);
    printf("███████╗███████╗███████╗██║░╚██╗░░░██║░░░██║░░██║██║░░██║\n");
    screenGotoxy(MINX + 25, MINY + 15);
    screenSetColor(WHITE, BLACK);
    printf("╚══════╝╚══════╝╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝\n");

    // Exibe mensagens com instruções para o jogador
    screenGotoxy(MINX + 25, MINY + 18);
    screenSetColor(LIGHTBLUE, DARKGRAY);
    printf("Proteja o planeta da tempestade de asteroides!");

    screenGotoxy(MINX + 25, MINY + 19);
    screenSetColor(LIGHTBLUE, DARKGRAY);
    printf("Use as setas da direita e esquerda para mover a nave, e o espaço para atirar.");

    screenGotoxy(MINX + 25, MINY + 20);
    screenSetColor(LIGHTBLUE, DARKGRAY);
    printf("Pressione 'C' para começar ou 'S' para sair.\n");

    fflush(stdout); // Garante que a saída seja exibida imediatamente

    // Espera até que o jogador pressione 'C' ou 'S'
    while (1) {
        if (keyhit()) { // Verifica se alguma tecla foi pressionada
            char ch = readch();
            if (ch == 'C' || ch == 'c') {
                return; // Sai da tela inicial para começar o jogo
            } else if (ch == 'S' || ch == 's') {
                exit(0); // Sai do jogo
            }
        }
    }
}

// Função que exibe a tela do jogo
void telaJogo(int nave_x, int nave_y) {
    screenClear(); // Limpa a tela antes de desenhar a tela do jogo

    // Aqui você pode desenhar elementos do jogo, como a nave e asteroides
    desenharNave(nave_x, nave_y);
    desenharAsteroides();

    // Atualiza a tela
    screenUpdate();
}

#define WIDTH 130
#define HEIGHT 40 

int main() {
    screenInit(1); // inicializa a tela
    telainicial();

    int nave_x = (WIDTH - 5) / 2;
    int nave_y = HEIGHT - 4;

    inicializarAsteroides(); // Inicializa asteroides

    // Loop principal
    while (1) {
        // **1. Checar entrada do jogador**
        if (keyhit()) {
            char tecla = readch();
            apagaNave(nave_x, nave_y); // apaga a nave da posição atual

            // Movimenta nave com setas
            if (tecla == 27 && getchar() == 91) {
                tecla = getchar();
                if (tecla == 67 && nave_x < WIDTH - 5) nave_x++;   // Direita
                else if (tecla == 68 && nave_x > 0) nave_x--;      // Esquerda
            }
            if (tecla == 's') break; // Sai do jogo se pressionar 's'
        }

        // **2. Atualizar asteroides**
        atualizarAsteroides();

        // **3. Desenhar a tela do jogo**
        telaJogo(nave_x, nave_y);

        // **4. Controle de tempo**
        usleep(100000); // Define o tempo de atualização do jogo
    }

    screenDestroy(); // Finaliza a tela
    return 0;
}