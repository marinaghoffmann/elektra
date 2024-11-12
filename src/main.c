#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "asteroides.h"
#include "bala.h"
#include "nave.h"

// Variáveis de controle do jogo
//int score = 0;
//int game_over = 0;        // Número inicial de asteroides ativos

// Função que exibe a tela inicial do jogo
void telainicial()
{
    screenClear(); // Limpa a tela antes de exibir a tela inicial

    // Desenha o título do jogo na tela com a cor ciano claro
    screenGotoxy(MINX + 25, MINY + 10);
    screenSetColor(WHITE, DARKGRAY);
    printf("███████╗██╗░░░░░███████╗██╗░░██╗████████╗██████╗░░█████╗░\n");

    screenGotoxy(MINX + 25, MINY + 11);
    screenSetColor(WHITE, DARKGRAY);
    printf("██╔════╝██║░░░░░██╔════╝██║░██╔╝╚══██╔══╝██╔══██╗██╔══██╗\n");
    screenGotoxy(MINX + 25, MINY + 12);
    screenSetColor(WHITE, DARKGRAY);
    printf("█████╗░░██║░░░░░█████╗░░█████═╝░░░░██║░░░██████╔╝███████║\n");
    screenGotoxy(MINX + 25, MINY + 13);
    screenSetColor(WHITE, DARKGRAY);
    printf("██╔══╝░░██║░░░░░██╔══╝░░██╔═██╗░░░░██║░░░██╔══██╗██╔══██║\n");
    screenGotoxy(MINX + 25, MINY + 14);
    screenSetColor(WHITE, DARKGRAY);
    printf("███████╗███████╗███████╗██║░╚██╗░░░██║░░░██║░░██║██║░░██║\n");
    screenGotoxy(MINX + 25, MINY + 15);
    screenSetColor(WHITE, DARKGRAY);
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
    while (1)
    {
        if (keyhit())
        { // Verifica se alguma tecla foi pressionada
            char ch = readch();
            if (ch == 'C' || ch == 'c')
            {
                return; // Sai da tela inicial para começar o jogo
            }
            else if (ch == 'S' || ch == 's')
            {
                exit(0); // Sai do jogo
            }
        }
    }
}

//void inicio() {
    //iniciarNave();
    //for (int i = 0; i < MAX_BALAS; i++) balas[i].ativo = 0;
    //for (int i = 0; i < MAX_ASTEROIDES; i++) asteroides[i].ativo = 0;
    //score = 0;
    //game_over = 0;
//}

//#define WIDTH 81
//#define HEIGHT 24 

//void colisao() {
    //for (int i = 0; i < MAX_BALAS; i++) {
        //if (balas[i].ativo) {
            //for (int j = 0; j < MAX_ASTEROIDES; j++) {
                //if (asteroides[j].ativo && balas[i].x == asteroides[j].x && balas[i].y == asteroides[j].y) {
                    //balas[i].ativo = 0;
                    //asteroides[j].ativo = 0;
                    //score += 10;
                    //if (score % 50 == 0) {
                        //if (asteroides_ativos < MAX_ASTEROIDES) asteroides_ativos++;
                        //if (velocidade_asteroides > 100000) velocidade_asteroides -= 20000;
                    //}
                //}
            //}
        //}
    //}
    //for (int i = 0; i < MAX_ASTEROIDES; i++) {
        //if (asteroides[i].ativo && asteroides[i].y >= HEIGHT - 2 && abs(asteroides[i].x - nave.x) < 5) {
            //game_over = 1;
        //}
    //}
//}

//void telaGameOver() {
    //screenClear();
    //printf("Game Over! Pontuação final: %d\n", score);
    //screenGotoxy(0, 2);
    //printf("Deseja jogar novamente? (s para sim / n para não): ");
    //fflush(stdout);
    //while (1) {
        //if (keyhit()) {
            //char ch = readch();
            //if (ch == 's' || ch == 'S') {
                //inicio();
                //return;
            //}
            //else if (ch == 'n' || ch == 'N') {
                //telainicial();
                //return;
            //}
        //}
    //}
//}

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

        // **3. Desenhar tudo**
        desenharNave(nave_x, nave_y);
        desenharAsteroides();

        // **4. Atualizar a tela**
        screenUpdate();

        // **5. Controle de tempo**
        usleep(100000); // Define o tempo de atualização do jogo
    }

    screenDestroy(); // Finaliza a tela
    return 0;
}