#include "nave.h"
#include "screen.h"
#include "keyboard.h"
#include "asteroides.h"
#include <unistd.h>

#define WIDTH 130
#define HEIGHT 40 //talvez tenha que mudar dps por causa dos asteroides, mt baixa?

//Nave nave;
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
    int rodando = 1;  // flag para manter o loop do jogo ativo

    screenClear();         // limpa a tela
    inicializarAsteroides(); // inicializa os asteroides
    desenharNave(x, y);    // desenha a nave na posição inicial
    screenUpdate();        // atualiza a tela

    while (rodando) {  // loop principal do jogo
        // **1. Verificar entrada do jogador**
        if (keyhit()) { // Verifica se há uma tecla pressionada
            tecla = capturaTecla();

            apagaNave(x, y); // apaga a nave da posição atual

            if (tecla == 27) { // a tecla "Escape" é o prefixo para as setas
                tecla = getchar();  // lê o próximo caractere que é a tecla da seta

                if (tecla == 91) { // verifica a sequência que indica que é uma seta
                    tecla = getchar();  // lê o próximo caractere da sequência

                    if (tecla == 67 && x < MAXX - 5) x++; // seta para a direita e verifica limite da tela
                    else if (tecla == 68 && x > MINX) x--; // seta para a esquerda e verifica limite da tela
                }
            }

            if (tecla == 's') { // tecla para sair do jogo
                rodando = 0;
                continue;
            }
        }

        // **2. Atualizar asteroides**
        atualizarAsteroides();

        // **3. Redesenhar nave**
        desenharNave(x, y);

        // **4. Atualizar a tela**
        screenUpdate();

        // **5. Controle de tempo**
        usleep(100000); // pausa para controlar a velocidade do jogo (em microsegundos)
    }
}




