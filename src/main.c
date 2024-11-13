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
#define DURACAO_JOGO 60  // Duração do jogo em segundos

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

void exibirEstrelas() {
    int i, j;
    for (i = 0; i < 20; i++) { // Número de linhas
        for (j = 0; j < 80; j++) { // Largura da tela
            if (rand() % 100 < 5) { // 5% de chance de colocar uma estrela
                screenGotoxy(j, i);
                screenSetColor(YELLOW, DARKGRAY);
                printf("*");
            }
        }
    }
}

void menu() {
    screenClear();
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Animação do título caindo
    for (int y = 0; y < 10; y++) { // 10 é o número de linhas que o título vai cair
        screenClear(); // Limpa a tela a cada iteração
        screenGotoxy(MINX + 5, MINY + 10 + y);
        screenSetColor(WHITE, DARKGRAY);
        printf("▓█████  ██▓    ▓█████  ██ ▄█▀▄▄▄█████▓ ██▀███   ▄▄▄      \n");
        screenGotoxy(MINX + 5, MINY + 11 + y);
        printf("▓█   ▀ ▓██▒    ▓█   ▀  ██▄█▒ ▓  ██▒ ▓▒▓██ ▒ ██▒▒████▄    \n");
        screenGotoxy(MINX + 5, MINY + 12 + y);
        printf("▒███   ▒██░    ▒███   ▓███▄░ ▒ ▓██░ ▒░▓██ ░▄█ ▒▒██  ▀█▄  \n");
        screenGotoxy(MINX + 5, MINY + 13 + y);
        printf("▒▓█  ▄ ▒██░    ▒▓█  ▄ ▓██ █▄ ░ ▓██▓ ░ ▒██▀▀█▄  ░██▄▄▄▄██ \n");
        screenGotoxy(MINX + 5, MINY + 14 + y);
        printf("░▒████▒░██████▒░▒████▒▒██▒ █▄  ▒██▒ ░ ░██▓ ▒██▒ ▓█   ▓██▒\n");
        screenGotoxy(MINX + 5, MINY + 15 + y);
        printf("░░ ▒░ ░░ ▒░▓  ░░░ ▒░ ░▒ ▒▒ ▓▒  ▒ ░░   ░ ▒▓ ░▒▓░ ▒▒   ▓▒█░\n");
        screenGotoxy(MINX + 5, MINY + 16 + y);
        printf(" ░ ░  ░░ ░ ▒  ░ ░ ░  ░░ ░▒ ▒░    ░      ░▒ ░ ▒░  ▒   ▒▒ ░\n");
        screenGotoxy(MINX + 5, MINY + 17 + y);
        printf("   ░     ░ ░      ░   ░ ░░ ░   ░        ░░   ░   ░   ▒   \n");
        screenGotoxy(MINX + 5, MINY + 18 + y);
        printf("   ░  ░    ░  ░   ░  ░░  ░               ░           ░  ░\n");

        fflush(stdout);
        usleep(200000); // Pausa de 200ms entre cada linha
    }

    // Exibe as instruções
    screenGotoxy(MINX + 5, MINY + 30);
    screenSetColor(WHITE, DARKGRAY);
    printf("Proteja o planeta da tempestade de asteroides!");
    screenGotoxy(MINX + 5, MINY + 31);
    printf("Destrua-os antes que eles atinjam a Terra.");
    screenGotoxy(MINX + 5, MINY + 32);
    printf("Use as teclas de seta para mover a nave e espaço para atirar.");
    screenGotoxy(MINX + 5, MINY + 33);
    printf("Pressione 'C' para começar ou 'S' para sair.");

    // Exibe as estrelas no fundo
    exibirEstrelas();  // Chama a função para exibir as estrelas no fundo

    fflush(stdout);

    // Espera pela entrada do usuário
    while (1) {
        if (keyhit()) {
            char ch = readch();
            if (ch == 'C' || ch == 'c') {
                return;  // Sai do menu e começa o jogo
            } else if (ch == 'S' || ch == 's') {
                exit(0);  // Sai do jogo
            }
        }
    }
}

void exibirPontuacao() {
    screenGotoxy(MAXX / 2 - 15, 0);  // Posiciona mais à esquerda, para evitar sobreposição com o tempo
    screenSetColor(WHITE, DARKGRAY);
    printf("Pontuação: %d", pontuacao);
}

void exibirTempoRestante(int tempoRestante) {
    screenGotoxy(MAXX / 2 + 5, 0);  // Posiciona mais à direita, para evitar sobreposição com a pontuação
    screenSetColor(WHITE, DARKGRAY);
    printf("Tempo restante: %02d:%02d", tempoRestante / 60, tempoRestante % 60);
}

void exibirTelaSaida() {
    screenClear();
    screenGotoxy(MAXX / 2 - 20, MAXY / 2 - 1);
    screenSetColor(RED, DARKGRAY);
    printf("Você abandonou a missão, o planeta foi destruído!");
    
    screenGotoxy(MAXX / 2 - 10, MAXY / 2 + 1);
    printf("Pontuação final: %d", pontuacao);
    
    screenGotoxy(MAXX / 2 - 10, MAXY / 2 + 3);
    printf("Aperte 1 para voltar à tela inicial.");

    fflush(stdout); // Garante que a tela seja atualizada sem `screenRefresh`

    // Aguarda o jogador pressionar '1' para voltar à tela inicial
    while (1) {
        if (keyhit() && readch() == '1') {
            menu(); // Chama a função que exibe a tela inicial
            return; // Sai da função para retornar à tela inicial
        }
    }
}

void gameOver() {
    screenClear();
    screenGotoxy(MAXX / 2 - 20, MAXY / 2 - 1);
    screenSetColor(RED, DARKGRAY);
    printf("TIME OUT!");
    
    screenGotoxy(MAXX / 2 - 10, MAXY / 2 + 1);
    printf("Pontuação final: %d", pontuacao);
    
    screenGotoxy(MAXX / 2 - 10, MAXY / 2 + 3);
    printf("Aperte 1 para voltar à tela inicial.");

    fflush(stdout); // Garante que a tela seja atualizada sem `screenRefresh`

    // Aguarda o jogador pressionar '1' para voltar à tela inicial
    while (1) {
        if (keyhit() && readch() == '1') {
            menu(); // Chama a função que exibe a tela inicial
            return; // Sai da função para retornar à tela inicial
        }
    }
}

void jogo() {
    int tempoRestante = DURACAO_JOGO;  // Inicializa o tempo restante
    clock_t inicio = clock();       
    int *pontuacao = malloc(sizeof(int));
    if (!pontuacao) {
        fprintf(stderr, "Erro ao alocar memória para a pontuação!\n");
        exit(1);
    }

    *pontuacao = 0;
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

    while (tempoRestante > 0) {
        // Verifica se o tempo passou 1 segundo
        if (((clock() - inicio) / CLOCKS_PER_SEC) >= 1) {
            tempoRestante--;          // Reduz o tempo restante
            inicio = clock();         // Reinicia o tempo base
        }

        // Verifica teclas pressionadas
        if (keyhit()) {
            char ch = readch();
            if (ch == 27) {
                ch = readch();
                if (ch == '[') {
                    ch = readch();
                    if (ch == 'D') moverNave(&nave, -1); // Esquerda
                    if (ch == 'C') moverNave(&nave, 1);  // Direita
                }
            } else if (ch == ' ') {
                dispararBala(balas, MAX_BALAS, nave.x, nave.y);
            } else if (ch == 'S' || ch == 's') {
                exibirTelaSaida();
                return;
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

            desenharNave(&nave);

            exibirPontuacao();

            exibirTempoRestante(tempoRestante);

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
    gameOver();
}

int main() {
    menu();
    srand(time(NULL));  // Inicializa o gerador de números aleatórios
    jogo();  // Chama a função do jogo
    return 0;
}
