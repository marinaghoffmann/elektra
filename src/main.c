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
// Função principal do jogo
void jogo() {
    Nave nave;  // Declara a nave
    inicializarNave(&nave);  // Inicializa a nave

    int tickMovimento = 0;  // Contador para controlar a taxa de atualização

    // Inicializa os asteroides
    Asteroide asteroides[MAX_ASTEROIDES];
    inicializarAsteroides(asteroides, MAX_ASTEROIDES);

    // Inicializa as balas (um milhão de balas disponíveis)
    inicializarBalas(balas, MAX_BALAS);  // Inicializa todas as balas como inativas

    // Inicia o timer com um delay configurável
    timerInit(UPDATE_DELAY);

    // Loop principal do jogo
    while (1) {
        // Verifica se a tecla foi pressionada
        if (keyhit()) {
            char ch = readch();
            if (ch == 'a') {
                moverNave(&nave, -1);  // Move a nave para a esquerda
            } else if (ch == 'd') {
                moverNave(&nave, 1);  // Move a nave para a direita
            } else if (ch == ' ') {
                // Dispara uma nova bala
                dispararBala(balas, MAX_BALAS, nave.x, nave.y);  // Dispara se houver uma bala inativa
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
            for (int i = 0; i < MAX_BALAS; i++) {
                if (balas[i].ativa) {
                    for (int j = 0; j < MAX_ASTEROIDES; j++) {
                        if (asteroides[j].ativo && balas[i].x == asteroides[j].x && balas[i].y == asteroides[j].y) {
                            // Colidiu com um asteroide, destrói a bala e o asteroide
                            asteroides[j].ativo = 0;  // Remove o asteroide
                            balas[i].ativa = 0;  // Remove a bala
                            break;  // Sai do loop de asteroides
                        }
                    }
                }
            }

            fflush(stdout);  // Garante a atualização imediata da tela
            tickMovimento++; // Incrementa o contador de tick
        }
    }
}


// Função principal
int main() {
    // Inicialização de componentes do jogo
    // Exemplo: screenInit(), keyboardInit(), etc.

    jogo();  // Chama a função do jogo

    return 0;
}
