//#include <stdlib.h>
//#include "asteroides.h"
//#include "screen.h"

//#define WIDTH 80
//#define HEIGHT 24

//extern int game_over;
//int velocidade_asteroides = 300000;
//int asteroides_ativos = 1;
//Asteroide asteroides[MAX_ASTEROIDES];

//void gerarAsteroides() {
    //int asteroides_count = 0;
    //for (int i = 0; i < MAX_ASTEROIDES; i++) {
        //if (asteroides[i].ativo)
            //asteroides_count++;
    //}
    //if (asteroides_count < asteroides_ativos) {
        //for (int i = 0; i < MAX_ASTEROIDES; i++) {
            //if (!asteroides[i].ativo) {
                //asteroides[i].x = rand() % WIDTH;
                //asteroides[i].y = 0;
                //asteroides[i].ativo = 1;
                //break;
            //}
        //}
    //}
//}

//void moverAsteroides() {
    //for (int i = 0; i < MAX_ASTEROIDES; i++) {
        //if (asteroides[i].ativo) {
            //asteroides[i].y++;
            //if (asteroides[i].y >= HEIGHT - 1) {
                //game_over = 1;
            //}
        //}
    //}
//}

#include "asteroides.h"
#include <stdio.h>

void print_asteroides() {
    printf("função asteroides ta pegando!\n");
}

