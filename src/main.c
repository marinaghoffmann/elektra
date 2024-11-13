#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define UPDATE_DELAY 50  // Ajuste para o timer em milissegundos
#define MAX_ASTEROIDES 10  // Número máximo de asteroides no jogo
#define MAX_BALAS 5        // Número máximo de balas simultâneas
#define NAVE_X_INICIAL 40  // Posição inicial da nave
#define NAVE_Y_INICIAL 20
#define MAXX 80
#define MAXY 25

// Variável global para pontuação
int pontuacao = 0;  // Inicializa a pontuação

// Estruturas
typedef struct {
    int x, y;
} Nave;

typedef struct {
    int x, y;
    int ativo;
} Asteroide;

typedef struct {
    int x, y;
    int ativa;
} Bala;

// Funções de manipulação da nave
void inicializarNave(Nave *nave) {
    nave->x = NAVE_X_INICIAL;
    nave->y = NAVE_Y_INICIAL;
}

void moverNave(Nave *nave, int direcao) {
    if (direcao == -1 && nave->x > 0) {
        nave->x--;  // Move para a esquerda
    } else if (direcao == 1 && nave->x < MAXX - 1) {
        nave->x++;  // Move para a direita
    }
}

void desenharNave(const Nave *nave) {
    screenGotoxy(nave->x, nave->y);
    screenSetColor(WHITE, DARKGRAY);
    printf("  ^  ");
    
    screenGotoxy(nave->x, nave->y + 1);
    printf(" /_\\ ");
    
    screenGotoxy(nave->x, nave->y + 2);
    printf("|_o_|");
}

// Funções de manipulação dos asteroides
void inicializarAsteroides(Asteroide asteroides[], int maxAsteroides) {
    for (int i = 0; i < maxAsteroides; i++) {
        asteroides[i].ativo = 0;
    }
}

void atualizarAsteroides(Asteroide asteroides[], int maxAsteroides) {
    for (int i = 0; i < maxAsteroides; i++) {
        if (!asteroides[i].ativo && rand() % 20 == 0) {
            asteroides[i].x = rand() % MAXX;
            asteroides[i].y = 0;
            asteroides[i].ativo = 1;
        } else if (asteroides[i].ativo) {
            asteroides[i].y++;
            if (asteroides[i].y >= MAXY) {
                asteroides[i].ativo = 0;
            }
        }
    }
}

void desenharAsteroides(const Asteroide asteroides[], int maxAsteroides) {
    for (int i = 0; i < maxAsteroides; i++) {
        if (asteroides[i].ativo) {
            screenGotoxy(asteroides[i].x, asteroides[i].y);
            screenSetColor(BLUE, DARKGRAY);
            printf("*0*");
        }
    }
}

// Funções de manipulação das balas
void inicializarBalas(Bala *balas, int maxBalas) {
    for (int i = 0; i < maxBalas; i++) {
        balas[i].ativa = 0;
    }
}

void dispararBala(Bala balas[], int maxBalas, int x, int y) {
    for (int i = 0; i < maxBalas; i++) {
        if (!balas[i].ativa) {
            balas[i].x = x;
            balas[i].y = y - 1;
            balas[i].ativa = 1;
            break;
        }
    }
}

void atualizarBalas(Bala balas[], int maxBalas) {
    for (int i = 0; i < maxBalas; i++) {
        if (balas[i].ativa) {
            balas[i].y--;
            if (balas[i].y < 0) {
                balas[i].ativa = 0;
            }
        }
    }
}

void verificarColisaoComAsteroides(Bala balas[], int maxBalas, Asteroide asteroides[], int maxAsteroides, int distanciaColisao) {
    for (int i = 0; i < maxBalas; i++) {
        if (balas[i].ativa) {
            for (int j = 0; j < maxAsteroides; j++) {
                if (asteroides[j].ativo && abs(balas[i].x - asteroides[j].x) <= distanciaColisao && abs(balas[i].y - asteroides[j].y) <= distanciaColisao) {
                    balas[i].ativa = 0;
                    asteroides[j].ativo = 0;
                    pontuacao++;  // Incrementa a pontuação
                }
            }
        }
    }
}

void exibirPontuacao() {
    screenGotoxy(MAXX / 2 - 10, 0);  // Posiciona no topo, centralizado
    screenSetColor(WHITE, DARKGRAY);
    printf("Pontuação: %d", pontuacao);
}

void jogo() {
    Nave nave;  // Declara a nave
    inicializarNave(&nave);  // Inicializa a nave

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
                return;  // Retorna para o menu
            }
        }

        // Atualização condicional para controlar a taxa de atualização
        if (timerTimeOver()) {
            screenClear();

            // Atualiza os asteroides e os desenha
            atualizarAsteroides(asteroides, MAX_ASTEROIDES);
            desenharAsteroides(asteroides, MAX_ASTEROIDES);

            // Atualiza posição das balas e verifica colisão
            atualizarBalas(balas, MAX_BALAS);  // Atualiza as balas (movendo-as para cima)
            verificarColisaoComAsteroides(balas, MAX_BALAS, asteroides, MAX_ASTEROIDES, 2);  // Verifica colisões

            // Desenha a nave
            desenharNave(&nave);

            // Exibe a pontuação
            exibirPontuacao();

            // Desenha as balas ativas
            for (int i = 0; i < MAX_BALAS; i++) {
                if (balas[i].ativa) {
                    screenGotoxy(balas[i].x, balas[i].y);
                    screenSetColor(YELLOW, DARKGRAY);
                    printf("|");
                }
            }

            fflush(stdout);  // Garante a atualização imediata da tela
        }
    }
}

int main() {
    srand(time(NULL));  // Inicializa o gerador de números aleatórios
    jogo();  // Chama a função do jogo
    return 0;
}
