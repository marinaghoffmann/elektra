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
    // Define as cores da nave
    screenSetColor(LIGHTCYAN, DARKGRAY);

    // Nave redesenhada um pouco menor
    screenGotoxy(x, y);     printf("  ^  "); //começa na posição inicial e vai somando mais 1 sucetivamente
    screenGotoxy(x, y + 1); printf(" /_\\ ");
    screenGotoxy(x, y + 2); printf("|_o_|");

    // Restaura a cor padrão da tela
    screenSetNormal();
}


void apagaNave(int x, int y) {
    // apaga a nave desenhando espaços nas posições da nave para que der a ideia de movimento
    for (int i = 0; i < 3; i++) { // 5 já que a nave ocupa 5 linhas, para que todas se movam
        screenGotoxy(x, y + i); //move o cursor para essas posições
        printf("        "); 
    }
}

void moverNave() {
    int x = (MAXX - 5) / 2, y = MAXY - 3; // posição inicial da nave (MODIFICADO) agora a principio a nave iniciará no centro inferior da tela
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

                if (tecla == 67 && x < MAXX - 5) x++; // seta para a direita e verifica se a nave esta dentro do limite da tela (Houve uma modificação nessa linha para o novo tamanho da nave (de 7 foi para 5))
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



