#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "asteroides.h"
#include "bala.h"
#include "nave.h"

#define UPDATE_DELAY 50  // Ajuste para o timer em milissegundos
#define MAX_ASTEROIDES 10  // Número máximo de asteroides no jogo

// Função principal do jogo

void menu() {
    screenClear();

    screenGotoxy(MINX + 5, MINY + 10);
    screenSetColor(WHITE, DARKGRAY);
    printf("███████╗██╗░░░░░███████╗██╗░░██╗████████╗██████╗░░█████╗░\n");
    screenGotoxy(MINX + 5, MINY + 11);
    screenSetColor(WHITE, DARKGRAY);
    printf("██╔════╝██║░░░░░██╔════╝██║░██╔╝╚══██╔══╝██╔══██╗██╔══██╗\n");
    screenGotoxy(MINX + 5, MINY + 12);
    screenSetColor(WHITE, DARKGRAY);
    printf("█████╗░░██║░░░░░█████╗░░█████═╝░░░░██║░░░██████╔╝███████║\n");
    screenGotoxy(MINX + 5, MINY + 13);
    screenSetColor(WHITE, DARKGRAY);
    printf("██╔══╝░░██║░░░░░██╔══╝░░██╔═██╗░░░░██║░░░██╔══██╗██╔══██║\n");
    screenGotoxy(MINX + 5, MINY + 14);
    screenSetColor(WHITE, DARKGRAY);
    printf("███████╗███████╗███████╗██║░╚██╗░░░██║░░░██║░░██║██║░░██║\n");
    screenGotoxy(MINX + 5, MINY + 15);
    screenSetColor(WHITE, DARKGRAY);
    printf("╚══════╝╚══════╝╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝\n");
    screenGotoxy(MINX + 5, MINY + 16);
    screenSetColor(WHITE, DARKGRAY);
    printf("Proteja o planeta da tempestade de asteroides!");
    screenGotoxy(MINX + 5, MINY + 17);
    screenSetColor(WHITE, DARKGRAY);
    printf("Pressione 'C' para começar ou 'S' para sair.");

    screenGotoxy(MINX + 5, MINY + 21);
    printf("Destrua os asteroides antes que eles atinjam a Terra.");
    screenGotoxy(MINX + 5, MINY + 22);
    printf("CUIDADO! Não seja atingido.");
    screenGotoxy(MINX + 5, MINY + 23);
    printf("Use as teclas de seta para mover a nave e espaço para atirar.");
    screenGotoxy(MINX + 5, MINY + 24);
    printf("Aperte 'C' para começar. Boa sorte!...");

    fflush(stdout);

    // Espera pela entrada do usuário
    while (1) {
        if (keyhit()) {
            char ch = readch();
            if (ch == 'C' || ch == 'c') {
                return;  // Sai do menu e começa o jogo
            } else if (ch == 'S' || ch == 's') {
                exit(0);  // Sai do jogo
            }
        }
    }
}

void jogo() {
    Nave nave;  // Declara a nave
    inicializarNave(&nave);  // Inicializa a nave

    int tickMovimento = 0;  // Contador para controlar a taxa de atualização

    // Inicializa os asteroides
    Asteroide asteroides[MAX_ASTEROIDES];
    inicializarAsteroides(asteroides, MAX_ASTEROIDES);

    // Inicializa as balas
    Bala balas[MAX_BALAS];
    inicializarBalas(balas, MAX_BALAS);  // Inicializa todas as balas como inativas

    // Inicia o timer com um delay configurável
    timerInit(UPDATE_DELAY);

    // Loop principal do jogo
    while (1) {
        // Verifica se a tecla foi pressionada
        if (keyhit()) {
            char ch = readch();
            if (ch == 27) {  // Se a tecla pressionada é ESC (início da sequência de setas)
                ch = readch();  // Lê o próximo caractere
                if (ch == '[') {  // Verifica se é a sequência correta
                    ch = readch();  // Lê o próximo caractere
                    if (ch == 'D') {
                        moverNave(&nave, -1);  // Move a nave para a esquerda
                    } else if (ch == 'C') {
                        moverNave(&nave, 1);  // Move a nave para a direita
                    }
                }
            } else if (ch == ' ') {
                // Dispara uma nova bala
                dispararBala(balas, MAX_BALAS, nave.x, nave.y);  // Dispara se houver uma bala inativa
            } else if (ch == 'S' || ch == 's') {
                // Se pressionar 'S', volta para o menu
                menu();
                return;  // Retorna para o menu e interrompe o jogo atual
            }
        }

        // Atualização condicional para controlar a taxa de atualização
        if (timerTimeOver()) {
            screenClear();

            // Atualiza os asteroides e os desenha
            atualizarAsteroides(asteroides, MAX_ASTEROIDES);
            desenharAsteroides(asteroides, MAX_ASTEROIDES);

            // Desenha a nave
            desenharNave(&nave);

            // Atualiza posição das balas e verifica colisão
            atualizarBalas(balas, MAX_BALAS);  // Atualiza as balas (movendo-as para cima)

            // Desenha as balas ativas
            for (int i = 0; i < MAX_BALAS; i++) {
                if (balas[i].ativa) {
                    screenGotoxy(balas[i].x, balas[i].y);
                    screenSetColor(RED, DARKGRAY);
                    printf("|");
                }
            }

            // Verifica colisão com os asteroides
            verificarColisaoComAsteroides(balas, MAX_BALAS, asteroides, MAX_ASTEROIDES, 2);  // Distância de colisão 2

            fflush(stdout);  // Garante a atualização imediata da tela
            tickMovimento++; // Incrementa o contador de tick
        }
    }
}


int main() {
    // Inicialização de componentes do jogo
    // Exemplo: screenInit(), keyboardInit(), etc.

    menu();  // Exibe o menu antes de começar o jogo
    jogo();  // Chama a função do jogo

    return 0;
}
