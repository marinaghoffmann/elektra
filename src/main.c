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
    screenSetColor(LIGHTCYAN, DARKGRAY);
    printf("███████╗██╗░░░░░███████╗██╗░░██╗████████╗██████╗░░█████╗░\n");

    screenGotoxy(MINX + 25, MINY + 11);
    screenSetColor(LIGHTCYAN, DARKGRAY);
    printf("██╔════╝██║░░░░░██╔════╝██║░██╔╝╚══██╔══╝██╔══██╗██╔══██╗\n");
    screenGotoxy(MINX + 25, MINY + 12);
    screenSetColor(LIGHTCYAN, DARKGRAY);
    printf("█████╗░░██║░░░░░█████╗░░█████═╝░░░░██║░░░██████╔╝███████║\n");
    screenGotoxy(MINX + 25, MINY + 13);
    screenSetColor(LIGHTCYAN, DARKGRAY);
    printf("██╔══╝░░██║░░░░░██╔══╝░░██╔═██╗░░░░██║░░░██╔══██╗██╔══██║\n");
    screenGotoxy(MINX + 25, MINY + 14);
    screenSetColor(LIGHTCYAN, DARKGRAY);
    printf("███████╗███████╗███████╗██║░╚██╗░░░██║░░░██║░░██║██║░░██║\n");
    screenGotoxy(MINX + 25, MINY + 15);
    screenSetColor(LIGHTCYAN, DARKGRAY);
    printf("╚══════╝╚══════╝╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝\n");

    // Exibe mensagens com instruções para o jogador
    screenGotoxy(MINX + 25, MINY + 18);
    screenSetColor(BLUE, DARKGRAY);
    printf("Proteja o planeta da tempestade de asteroides!");

    screenGotoxy(MINX + 25, MINY + 19);
    screenSetColor(BLUE, DARKGRAY);
    printf("Use as setas da direita e esquerda para mover a nave, e o espaço para atirar.");

    screenGotoxy(MINX + 25, MINY + 20);
    screenSetColor(BLUE, DARKGRAY);
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

//#define WIDTH 80
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

//int main() {
    //keyboardInit();
    //telainicial();

    //while (1) {
        //inicio();
        //while (!game_over) {
            //screenClear();
            //if (keyhit()) {
                //char ch = readch();
                //if (ch == 'q' || ch == 'Q') break;
                //if (ch == ' ') atirar();
                //if (ch == '\033') {
                    //if (keyhit() && readch() == '[') {
                        //char direction = readch();
                        //if (direction == 'D') moverNave('L');
                        //if (direction == 'C') moverNave('R');
                    //}
                //}
            //}
            //desenharNave();
            //moverTiros();
            //gerarAsteroides();
            //moverAsteroides();
            //colisao();
            //usleep(velocidade_asteroides);
        //}
        //telaGameOver();
    //}
    //keyboardClose();
    //return 0;
//}

int main(){
    screenInit(1);      // inicializa a tela, AMANDA(ainda vou desenhar as bordas da tela, n tô conseguindo deixar a nave embaixo)

    telainicial();

    desenharNave(40, 5);  // desenha a nave na posição (40, 5)
    moverNave();          
    
    // apaga a nave da tela depois do movimento
    apagaNave(40, 5);     // dpaga a nave da posição original 

    screenDestroy(); 

    return 0; 
}