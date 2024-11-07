#include "nave.h"
#include "screen.h"
#include "keyboard.h"

//#define WIDTH 80
//#define HEIGHT 24

//Nave nave;

//void iniciarNave() {
    //nave.x = WIDTH / 2;
//}

//void desenharNave() {
    //screenGotoxy(nave.x, HEIGHT - 2);
    //printf("<=^=>");
//}

//void moverNave(char direcao) {
    //if (direcao == 'L' && nave.x > 0)
        //nave.x -= 2;
    //if (direcao == 'R' && nave.x < WIDTH - 5)
        //nave.x += 2;
//}

void desenharNave(int x, int y) {
    /// desenha a nave na posição (x, y)
    screenSetColor(LIGHTCYAN, DARKGRAY);

    screenGotoxy(x, y);     printf("   /\\   "); //inicio da posição escolhida na main
    screenGotoxy(x, y + 1); printf("  /  \\  "); //a posição escolhida +1
    screenGotoxy(x, y + 2); printf(" /    \\ "); // e assim por diante...
    screenGotoxy(x, y + 3); printf(" |    | ");  // AMANDA: vou melhorar essa nave, ta mt feia né? 
    screenGotoxy(x, y + 4); printf(" \\____/ ");
    
    screenSetNormal(); // setar a tela para o "normal"
}

void apagaNave(int x, int y) {
    // apaga a nave desenhando espaços nas posições da nave para que der a ideia de movimento
    for (int i = 0; i < 5; i++) { // 5 já que a nave ocupa 5 linhas, para que todas se movam
        screenGotoxy(x, y + i); //move o cursor para essas posições
        printf("        "); 
    }
}

void moverNave() {
    int x = 40, y = 5; // posição inicial da nave
    int tecla;

    screenClear();
    desenharNave(x, y);
    screenUpdate();

    while (1) {
        tecla = capturaTecla(); // lê a tecla clicada no teclado e armazena em tecla 

        apagaNave(x, y); // apaga a nave da posição atual

        // move a nave com base na tecla pressionada
        if (tecla == 27) {  // a tecla "Escape" é o prefixo para as setas, as setas são uma tecla especial
            tecla = getchar();  // lê o próximo caractere que é a tecla da seta

            if (tecla == 91) { // verifica a sequência que indica que é uma seta, para que seja lido como seta
                tecla = getchar();  // lê o próximo caractere da sequência

                if (tecla == 67 && x < MAXX - 7) x++; // seta para a direita e verifica se a nave esta dentro do limite da tela
                else if (tecla == 68 && x > MINX) x--;    // seta para a esquerda e verifica se a nave esta dentro do limite da tela
            }
        }

        if (tecla == 's') {
            telainicial();  
            break;          
        }

        desenharNave(x, y);
        screenUpdate(); // atualiza a tela para exibir as posições da nave
    }
}



