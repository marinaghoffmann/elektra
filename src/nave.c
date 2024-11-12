#include "nave.h"
#include "screen.h"
#include "keyboard.h"

#define WIDTH 130
#define HEIGHT 40 //talvez tenha que mudar dps por causa dos asteroides, mt baixa?

//Nave nave;

void desenharBorda() {

    screenSetColor(WHITE, DARKGRAY);

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
    int x = (WIDTH - 5) / 2, y = HEIGHT - 4;  // posição inicial da nave
    int tecla;

    screenClear();        // limpa a tela para começar o jogo
    desenharBorda();      // desenha a borda da tela
    inicializarAsteroides(); // inicializa as posições iniciais dos asteroides
    desenharNave(x, y);   // desenha a nave na posição inicial
    screenUpdate();       // atualiza a tela para mostrar a nave e borda

    while (1) {  // loop principal do jogo
        tecla = capturaTecla(); // lê a tecla clicada no teclado e armazena em tecla

        apagaNave(x, y); // apaga a nave da posição atual

        // move a nave com base na tecla pressionada
        if (tecla == 27) {  // a tecla "Escape" é o prefixo para as setas
            tecla = getchar();  // lê o próximo caractere que é a tecla da seta

            if (tecla == 91) { // verifica a sequência que indica que é uma seta
                tecla = getchar();  // lê o próximo caractere da sequência

                if (tecla == 67 && x < MAXX - 5) x++; // seta para a direita e verifica limite da tela
                else if (tecla == 68 && x > MINX) x--; // seta para a esquerda e verifica limite da tela
            }
        }

        if (tecla == 's') {     // se o jogador pressionar 's', sai para a tela inicial
            telainicial();
            break;
        }

        atualizarAsteroides();  // move os asteroides para baixo e redesenha em novas posições
        desenharNave(x, y);     // redesenha a nave na nova posição
        screenUpdate();         // atualiza a tela para exibir as posições da nave e asteroides

        usleep(100000);  // pausa para controlar a velocidade de atualização do jogo (em microsegundos)
    }
}



