#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "asteroides.h"
#include "bala.h"
#include "nave.h"

#define UPDATE_DELAY 50  // Ajuste para o timer em milissegundos
#define MAX_ASTEROIDES 10  // Número máximo de asteroides no jogo

// Função principal do jogo

void exibirEstrelas() {
    int i, j;
    for (i = 0; i < 20; i++) { // Número de linhas
        for (j = 0; j < 80; j++) { // Largura da tela
            if (rand() % 100 < 5) { // 5% de chance de colocar uma estrela
                screenGotoxy(j, i);
                screenSetColor(YELLOW, DARKGRAY);
                printf("*");
            }
        }
    }
}

void menu() {
    screenClear();
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Animação do título caindo
    for (int y = 0; y < 10; y++) { // 10 é o número de linhas que o título vai cair
        screenClear(); // Limpa a tela a cada iteração
        screenGotoxy(MINX + 5, MINY + 10 + y);
        screenSetColor(WHITE, DARKGRAY);
        printf("▓█████  ██▓    ▓█████  ██ ▄█▀▄▄▄█████▓ ██▀███   ▄▄▄      \n");
        screenGotoxy(MINX + 5, MINY + 11 + y);
        printf("▓█   ▀ ▓██▒    ▓█   ▀  ██▄█▒ ▓  ██▒ ▓▒▓██ ▒ ██▒▒████▄    \n");
        screenGotoxy(MINX + 5, MINY + 12 + y);
        printf("▒███   ▒██░    ▒███   ▓███▄░ ▒ ▓██░ ▒░▓██ ░▄█ ▒▒██  ▀█▄  \n");
        screenGotoxy(MINX + 5, MINY + 13 + y);
        printf("▒▓█  ▄ ▒██░    ▒▓█  ▄ ▓██ █▄ ░ ▓██▓ ░ ▒██▀▀█▄  ░██▄▄▄▄██ \n");
        screenGotoxy(MINX + 5, MINY + 14 + y);
        printf("░▒████▒░██████▒░▒████▒▒██▒ █▄  ▒██▒ ░ ░██▓ ▒██▒ ▓█   ▓██▒\n");
        screenGotoxy(MINX + 5, MINY + 15 + y);
        printf("░░ ▒░ ░░ ▒░▓  ░░░ ▒░ ░▒ ▒▒ ▓▒  ▒ ░░   ░ ▒▓ ░▒▓░ ▒▒   ▓▒█░\n");
        screenGotoxy(MINX + 5, MINY + 16 + y);
        printf(" ░ ░  ░░ ░ ▒  ░ ░ ░  ░░ ░▒ ▒░    ░      ░▒ ░ ▒░  ▒   ▒▒ ░\n");
        screenGotoxy(MINX + 5, MINY + 17 + y);
        printf("   ░     ░ ░      ░   ░ ░░ ░   ░        ░░   ░   ░   ▒   \n");
        screenGotoxy(MINX + 5, MINY + 18 + y);
        printf("   ░  ░    ░  ░   ░  ░░  ░               ░           ░  ░\n");

        fflush(stdout);
        usleep(200000); // Pausa de 200ms entre cada linha
    }

    // Exibe as instruções
    screenGotoxy(MINX + 5, MINY + 30);
    screenSetColor(WHITE, DARKGRAY);
    printf("Proteja o planeta da tempestade de asteroides!");
    screenGotoxy(MINX + 5, MINY + 31);
    printf("Destrua-os antes que eles atinjam a Terra. CUIDADO! Não seja atingido.");
    screenGotoxy(MINX + 5, MINY + 32);
    printf("Use as teclas de seta para mover a nave e espaço para atirar.");
    screenGotoxy(MINX + 5, MINY + 33);
    printf("Pressione 'C' para começar ou 'S' para sair.");

    // Exibe as estrelas no fundo
    exibirEstrelas();  // Chama a função para exibir as estrelas no fundo

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
                    screenSetColor(YELLOW, DARKGRAY);
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
