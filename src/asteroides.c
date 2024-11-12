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
#include "screen.h"
#include <stdlib.h> // para a função rand(), para os asteroides nasçam em posições aleatórias

#define MAX_ASTEROIDES 10 // número máximo de asteroides
#define MAXX 130 // limite máximo da coordanada x
#define MINX 1  // limite minimo de x
#define MAXY 40 //...
#define MINY 1

// struct para armazenar os asteroides
struct Asteroide {
    int x;
    int y;
};

void desenharAsteroides() {
    // criando uma nova struct para armazenar os asteroides
    struct Asteroide* asteroides = (struct Asteroide*)malloc(MAX_ASTEROIDES * sizeof(struct Asteroide));
    
    if (asteroides == NULL) { // para falhas
        printf("Falha na alocação de memória!\n");
        return;
    }

    // gera as posições aleatórias para os asteroides
    for (int i = 0; i < MAX_ASTEROIDES; i++) { // asteroides[i] pq vai mudando e aumentando o valor de i para mudar de asteroide
        asteroides[i].x = rand() % (MAXX - MINX) + MINX; // garante que x esteja dentro do limite, por isso (MAXX - MINX) + MINX
        asteroides[i].y = rand() % (MAXY - MINY) + MINY; // garante que y esteja dentro do limite
        
        screenGotoxy(asteroides[i].x, asteroides[i].y);
        printf("*0*");
    }
    // liberar memória
    free(asteroides);
}

