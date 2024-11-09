#include "nave.h"
#include "screen.h"
#include "keyboard.h"

#define WIDTH 130
#define HEIGHT 40 //talvez tenha que mudar dps por causa dos asteroides, mt baixa?

//Nave nave;

void desenharBorda() {

    screenSetColor(WHITE, DARKGRAY);

    // desenhar bordas horizontais
    for (int x = 1; x <= WIDTH; x++) { // witdh = largura
        screenGotoxy(x, 1);          // parte de cima
        printf("=");
        screenGotoxy(x, HEIGHT);     // parte de baixo
        printf("=");
    }

    // desenhar bordas verticais
    for (int y = 1; y <= HEIGHT; y++) {
        screenGotoxy(1, y);          // parte da esquerda
        printf("||");
        screenGotoxy(WIDTH, y);      // parte da direita
        printf("||");
    }

    screenSetNormal();       
}

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
    for (int i = 0; i < 3; i++) { // 3 já que a nave ocupa 3 linhas, para que todas se movam
        screenGotoxy(x, y + i); //move o cursor para essas posições
        printf("        "); 
    }
}

void moverNave() {
    int x = (WIDTH - 5) / 2, y = HEIGHT - 4; // posição inicial da nave (MODIFICADO) agora a principio a nave iniciará no centro inferior da tela
    int tecla;

    screenClear();
    desenharBorda();
    desenharNave(x, y);
    screenUpdate();

    while (1) {  //ENTENDER UM POUCO MELHOR COMO FUNCIONA ESSA TECLA 27 E A 91
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



