#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define UPDATE_DELAY 50  
#define MAX_ASTEROIDES 10  
#define MAX_BALAS 5        
#define NAVE_X_INICIAL 40  
#define NAVE_Y_INICIAL 20
#define DURACAO_JOGO 60  

<<<<<<< HEAD
=======

// Variável global
>>>>>>> bc2e75900315801c8fab8441dd42cde89a679086
int pontuacao = 0;  

typedef struct {
    int x, y;
} Nave;

typedef struct {
    int x, y;
    int ativa;
} Bala;

typedef struct Asteroide {
    int x, y;
    int ativo;
    struct Asteroide *prox;  
} Asteroide;

void exibirPontuacoes();
void salvarPontuacao(int pontuacao);
void jogo();
void inicializarAsteroides(Asteroide asteroides[], int tamanho);


Asteroide *listaAsteroides() {
    Asteroide *lista = NULL;
    return lista;
}

void inicializarAsteroides(Asteroide asteroides[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        asteroides[i].x = 0;
        asteroides[i].y = 0;
        asteroides[i].ativo = 1;  
        asteroides[i].prox = NULL;
    }
}

void adicionarAsteroide(Asteroide **lista, int x, int y) {
    Asteroide *novo = malloc(sizeof(Asteroide));
    if (novo == NULL) {
        printf("Erro ao alocar memória para asteroide\n");
        exit(1);
    }
    novo->x = x;
    novo->y = y;
    novo->ativo = 1;
    novo->prox = *lista;
    *lista = novo;  
}

void removerAsteroide(Asteroide **lista, Asteroide *asteroide) {
    if (*lista == asteroide) {
        *lista = asteroide->prox;
    } else {
        Asteroide *temp = *lista;
        while (temp != NULL && temp->prox != asteroide) {
            temp = temp->prox;
        }
        if (temp != NULL) {
            temp->prox = asteroide->prox;
        }
    }
    free(asteroide);
}


void inicializarNave(Nave *nave) {
    nave->x = NAVE_X_INICIAL;
    nave->y = NAVE_Y_INICIAL;
}

void moverNave(Nave *nave, int direcao) {
    if (direcao == -1 && nave->x > 0) {
        nave->x--;  
    } else if (direcao == 1 && nave->x < MAXX - 5) {
        nave->x++;  
    } else if (direcao == -2 && nave->y > 0) {
        nave->y--; 
    } else if (direcao == 2 && nave->y < MAXY - 3) {
        nave->y++; 
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

void atualizarAsteroides(Asteroide asteroides[], int maxAsteroides) {
    int contadorAsteroides = 0; 

    if (contadorAsteroides % 2 == 0) { 
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
    contadorAsteroides++;
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
<<<<<<< HEAD
                    pontuacao++;  
=======
                    pontuacao++; 
>>>>>>> bc2e75900315801c8fab8441dd42cde89a679086
                }
            }
        }
    }
}

void exibirEstrelas() {
    int i, j;
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 80; j++) { 
            if (rand() % 100 < 5) { 
                screenGotoxy(j, i);
                screenSetColor(YELLOW, DARKGRAY);
                printf("*");
            }
        }
    }
}

void menu() {
    screenClear();
    srand(time(NULL)); 

<<<<<<< HEAD
    for (int y = 0; y < 10; y++) { 
        screenClear(); 
=======
    for (int y = 0; y < 10; y++) { // 10 é o número de linhas que o título vai cair
        screenClear(); // Limpa a tela a cada iteração
>>>>>>> bc2e75900315801c8fab8441dd42cde89a679086
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
        usleep(200000); 
    }

    screenGotoxy(MINX + 5, MINY + 30);
    screenSetColor(WHITE, DARKGRAY);
    printf("Proteja o planeta da tempestade de asteroides!");
    screenGotoxy(MINX + 5, MINY + 31);
    printf("Destrua-os antes que eles atinjam a Terra.");
    screenGotoxy(MINX + 5, MINY + 32);
    printf("Use as teclas de seta para mover a nave e espaço para atirar.");
    screenGotoxy(MINX + 5, MINY + 33);
    printf("Pressione 'C' para começar ou 'S' para sair e 'V' para ver pontuações anteriores.");

    exibirEstrelas(); 

    fflush(stdout);

    while (1) {
        if (keyhit()) {
            char ch = readch();
            if (ch == 'C' || ch == 'c') {
                salvarPontuacao(pontuacao); 
                pontuacao = 0; 
                jogo();
                return; 
            } else if (ch == 'S' || ch == 's') {
                exit(0); 
            } else if (ch == 'V' || ch == 'v'){
                exibirPontuacoes(); 
                screenClear();
                screenGotoxy(MAXX / 2 - 10, MAXY - 2);
            }
        }
    }
}

void exibirPontuacao() {
    screenGotoxy(MAXX / 2 - 15, 0); 
    screenSetColor(WHITE, DARKGRAY);
    printf("Pontuação: %d", pontuacao);
}

void exibirTempoRestante(int tempoRestante) {
    screenGotoxy(MAXX / 2 + 5, 0);  
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

    fflush(stdout); 

    while (1) {
        if (keyhit() && readch() == '1') {
            menu(); 
            return; 
        }
    }
}

void gameOver() {
    salvarPontuacao(pontuacao);
    for (int y = 0; y < 10; y++) { 
        screenClear(); 
        screenGotoxy(MINX + 5, MINY + 10 + y);
        screenSetColor(RED, BLACK);
        printf("████████╗██╗███╗   ███╗███████╗     ██████╗ ██╗   ██╗████████╗\n");
        screenGotoxy(MINX + 5, MINY + 11 + y);
        printf("╚══██╔══╝██║████╗ ████║██╔════╝    ██╔═══██╗██║   ██║╚══██╔══╝\n");
        screenGotoxy(MINX + 5, MINY + 12 + y);
        printf("   ██║   ██║██╔████╔██║█████╗      ██║   ██║██║   ██║   ██║   \n");
        screenGotoxy(MINX + 5, MINY + 13 + y);
        printf("   ██║   ██║██║╚██╔╝██║██╔══╝      ██║   ██║██║   ██║   ██║   \n");
        screenGotoxy(MINX + 5, MINY + 14 + y);
        printf("   ██║   ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝╚██████╔╝   ██║   \n");
        screenGotoxy(MINX + 5, MINY + 15 + y);
        printf("   ╚═╝   ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝  ╚═════╝    ╚═╝   \n");

        fflush(stdout);
        usleep(200000); 
    }

    screenGotoxy(MAXX / 2 - 25, MAXY / 2 + 6);
    screenSetColor(WHITE, BLACK);
    printf("Tempo esgotado! Aperte 'C' para tentar novamente ou '1' para voltar ao menu.");
    screenGotoxy(MAXX / 2 - 25, MAXY / 2 + 8);
    screenSetColor(WHITE, BLACK);
    printf("Pontuação final: %d", pontuacao);

    fflush(stdout);

    while (1) {
        if (keyhit()) {
            char ch = readch();
            if (ch == '1') {
                menu(); 
                return; 
            } else if (ch == 'C' || ch == 'c') {
                pontuacao = 0;
                jogo(); 
                return; 
            }
        }
    }
}

void salvarPontuacao(int pontuacao) {
    FILE *file = fopen("pontuacoes.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar pontuação.\n");
        return;
    }
    fprintf(file, "%d\n", pontuacao); 
    fclose(file);
}


void exibirPontuacoes() {
    FILE *file = fopen("pontuacoes.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de pontuações.\n");
        return;
    }

    int pontuacoes[100]; 
    int count = 0;

    while (fscanf(file, "%d", &pontuacoes[count]) == 1) {
        count++;
    }
    fclose(file);

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (pontuacoes[i] < pontuacoes[j]) {
                int temp = pontuacoes[i];
                pontuacoes[i] = pontuacoes[j];
                pontuacoes[j] = temp;
            }
        }
    }

    screenClear();
    screenGotoxy(MAXX / 2 - 10, MINY + 5);
    printf("Ranking de Pontuações:");
    for (int i = 0; i < count && i < 10; i++) {  
        screenGotoxy(MAXX / 2 - 10, MINY + 7 + i);
        printf("%dº Lugar: %d pontos", i + 1, pontuacoes[i]);
    }

    screenGotoxy(MAXX / 2 - 10, MAXY - 2);
    printf("Pressione 1 para voltar ao menu.");

    fflush(stdout);
    screenGotoxy(MAXX / 2 - 15, MAXY - 2);
    screenSetColor(RED, DARKGRAY);
    printf("Pressione 1 para voltar ao menu principal.");

    fflush(stdout);

    while (1) {
        if (keyhit() && readch() == '1') {
            menu(); 
            return;
        }
    }
}

void jogo() {
    int tempoRestante = DURACAO_JOGO;  
    clock_t inicio = clock();       
    int *pontuacao = malloc(sizeof(int));
    if (!pontuacao) {
        fprintf(stderr, "Erro ao alocar memória para a pontuação!\n");
        exit(1);
    }

    *pontuacao = 0;
    Nave nave;  
    inicializarNave(&nave);  

    Asteroide asteroides[MAX_ASTEROIDES];
    inicializarAsteroides(asteroides, MAX_ASTEROIDES);

    Bala balas[MAX_BALAS];
    inicializarBalas(balas, MAX_BALAS);  

    timerInit(UPDATE_DELAY);

    while (tempoRestante > 0) {
        if (((clock() - inicio) / CLOCKS_PER_SEC) >= 1) {
            tempoRestante--;          
            inicio = clock();         
        }

        if (keyhit()) {
            char ch = readch();
            if (ch == 27) {
                ch = readch();
                if (ch == '[') {
                    ch = readch();
                    if (ch == 'D') moverNave(&nave, -1); 
                    if (ch == 'C') moverNave(&nave, 1); 
                    if (ch == 'A') moverNave(&nave, -2);
                    if (ch == 'B') moverNave(&nave, 2); 
                }
            } else if (ch == ' ') {
                dispararBala(balas, MAX_BALAS, nave.x, nave.y);
            } else if (ch == 'S' || ch == 's') {
                exibirTelaSaida();
                return;
            }
        }

        if (timerTimeOver()) {
            screenClear();

            atualizarAsteroides(asteroides, MAX_ASTEROIDES);
            desenharAsteroides(asteroides, MAX_ASTEROIDES);

            atualizarBalas(balas, MAX_BALAS);  
            verificarColisaoComAsteroides(balas, MAX_BALAS, asteroides, MAX_ASTEROIDES, 2);  

            desenharNave(&nave);

            exibirPontuacao();
            exibirTempoRestante(tempoRestante);

            for (int i = 0; i < MAX_BALAS; i++) {
                if (balas[i].ativa) {
                    screenGotoxy(balas[i].x, balas[i].y);
                    screenSetColor(YELLOW, DARKGRAY);
                    printf("|");
                }
            }

            fflush(stdout);  
        }
    }
    free(pontuacao);
    gameOver();
}

int main() {
    menu();
<<<<<<< HEAD
    srand(time(NULL));  
=======
    srand(time(NULL));  // Inicializa o gerador de números aleatórios
>>>>>>> bc2e75900315801c8fab8441dd42cde89a679086
    jogo(); 
    return 0;
}
