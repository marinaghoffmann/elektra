#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "screen.h"   // Biblioteca para manipulação da tela, como posição do cursor e cores
#include "keyboard.h" // Biblioteca para leitura de teclas não-bloqueante
#include "timer.h"    // Biblioteca para controle de temporização
#include <unistd.h>   // Para a função usleep

// Função que exibe a tela inicial do jogo
void telainicial()
{
    screenClear(); // Limpa a tela antes de exibir a tela inicial

    // Desenha o título do jogo na tela com a cor ciano claro
    screenGotoxy(MINX + 25, MINY + 10);
    screenSetColor(LIGHTCYAN, BLACK);
    printf("███████╗██╗░░░░░███████╗██╗░░██╗████████╗██████╗░░█████╗░\n");

    screenGotoxy(MINX + 25, MINY + 11);
    screenSetColor(LIGHTCYAN, BLACK);
    printf("██╔════╝██║░░░░░██╔════╝██║░██╔╝╚══██╔══╝██╔══██╗██╔══██╗\n");
    screenGotoxy(MINX + 25, MINY + 12);
    screenSetColor(LIGHTCYAN, BLACK);
    printf("█████╗░░██║░░░░░█████╗░░█████═╝░░░░██║░░░██████╔╝███████║\n");
    screenGotoxy(MINX + 25, MINY + 13);
    screenSetColor(LIGHTCYAN, BLACK);
    printf("██╔══╝░░██║░░░░░██╔══╝░░██╔═██╗░░░░██║░░░██╔══██╗██╔══██║\n");
    screenGotoxy(MINX + 25, MINY + 14);
    screenSetColor(LIGHTCYAN, BLACK);
    printf("███████╗███████╗███████╗██║░╚██╗░░░██║░░░██║░░██║██║░░██║\n");
    screenGotoxy(MINX + 25, MINY + 15);
    screenSetColor(LIGHTCYAN, BLACK);
    printf("╚══════╝╚══════╝╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝\n");

    // Exibe mensagens com instruções para o jogador
    screenGotoxy(MINX + 25, MINY + 18);
    screenSetColor(BLUE, BLACK);
    printf("Proteja o planeta da tempestade de asteroides!");

    screenGotoxy(MINX + 25, MINY + 19);
    screenSetColor(BLUE, BLACK);
    printf("Use as setas da direita e esquerda para mover a nave, e o espaço para atirar.");

    screenGotoxy(MINX + 25, MINY + 20);
    screenSetColor(BLUE, BLACK);
    printf("Pressione 'C' para começar ou 'S' para sair.");

    fflush(stdout); // Garante que a saída seja exibida imediatamente

    // Espera até que o jogador pressione 'C' ou 'S'
    while (1)
    {
        if (keyhit())
        { // Verifica se alguma tecla foi pressionada
            char ch = readch();
            if (ch == 'C' || ch == 'c')
            {
                return; // Sai da tela inicial para começar o jogo
            }
            else if (ch == 'S' || ch == 's')
            {
                exit(0); // Sai do jogo
            }
        }
    }
}

// Definições de largura e altura da tela e limites de balas e asteroides
#define WIDTH 80
#define HEIGHT 24
#define MAX_BALAS 5
#define MAX_ASTEROIDES 10

// Estrutura para representar uma bala no jogo
typedef struct
{
    int x, y;  // Coordenadas da bala na tela
    int ativo; // Indica se a bala está ativa (1) ou não (0)
} Bala;

// Estrutura para representar um asteroide
typedef struct
{
    int x, y;  // Coordenadas do asteroide
    int ativo; // Indica se o asteroide está ativo
} Asteroide;

// Estrutura para representar a nave do jogador
typedef struct
{
    int x; // Coordenada x da nave (y é fixa)
} Nave;

Nave nave;                            // Instância da nave do jogador
Bala balas[MAX_BALAS];                // Array de balas
Asteroide asteroides[MAX_ASTEROIDES]; // Array de asteroides
int score = 0;                        // Pontuação do jogador
int game_over = 0;                    // Flag para verificar se o jogo terminou

// Função que inicializa o estado do jogo
void inicio()
{
    nave.x = WIDTH / 2; // Posiciona a nave no centro da tela
    for (int i = 0; i < MAX_BALAS; i++)
        balas[i].ativo = 0; // Inativa todas as balas
    for (int i = 0; i < MAX_ASTEROIDES; i++)
        asteroides[i].ativo = 0; // Inativa todos os asteroides
    score = 0;                   // Reseta a pontuação
    game_over = 0;               // Reseta o estado de game over
}

// Função que desenha a nave na tela
void imgnave()
{
    screenGotoxy(nave.x, HEIGHT - 2); // Define a posição da nave
    printf("<=^=>");                  // Desenha a nave com símbolo
}

// Função para mover a nave com base na direção
void movimento(char direcao)
{
    if (direcao == 'L' && nave.x > 0)
        nave.x--; // Move para a esquerda
    if (direcao == 'R' && nave.x < WIDTH - 5)
        nave.x++; // Move para a direita
}

// Função para atirar uma bala
void atirar()
{
    for (int i = 0; i < MAX_BALAS; i++)
    {
        if (!balas[i].ativo)
        {                            // Procura uma bala inativa
            balas[i].x = nave.x + 2; // Posiciona a bala na frente da nave
            balas[i].y = HEIGHT - 3; // Define a posição inicial
            balas[i].ativo = 1;      // Ativa a bala
            break;
        }
    }
}

// Função para mover as balas
void movertiros()
{
    for (int i = 0; i < MAX_BALAS; i++)
    {
        if (balas[i].ativo)
        {                 // Verifica se a bala está ativa
            balas[i].y--; // Move a bala para cima
            if (balas[i].y < 0)
                balas[i].ativo = 0; // Desativa a bala ao sair da tela
        }
    }
}

// Função para gerar novos asteroides
void gerarasteroides()
{
    for (int i = 0; i < MAX_ASTEROIDES; i++)
    {
        if (!asteroides[i].ativo)
        {                                     // Procura um asteroide inativo
            asteroides[i].x = rand() % WIDTH; // Define posição aleatória no eixo x
            asteroides[i].y = 0;              // Começa no topo da tela
            asteroides[i].ativo = 1;          // Ativa o asteroide
            break;
        }
    }
}

// Função para mover os asteroides
void moverasteroides()
{
    for (int i = 0; i < MAX_ASTEROIDES; i++)
    {
        if (asteroides[i].ativo)
        {
            asteroides[i].y++; // Move o asteroide para baixo
            if (asteroides[i].y >= HEIGHT - 1)
            {
                game_over = 1; // Se o asteroide atinge a parte inferior, o jogo termina
            }
        }
    }
}

// Função para detectar colisões entre balas e asteroides
void colisao()
{
    for (int i = 0; i < MAX_BALAS; i++)
    {
        if (balas[i].ativo)
        { // Verifica se a bala está ativa
            for (int j = 0; j < MAX_ASTEROIDES; j++)
            {
                if (asteroides[j].ativo && balas[i].x == asteroides[j].x && balas[i].y == asteroides[j].y)
                {
                    balas[i].ativo = 0;      // Desativa a bala
                    asteroides[j].ativo = 0; // Desativa o asteroide
                    score += 10;             // Incrementa a pontuação
                }
            }
        }
    }

    // Verifica colisão entre asteroides e a nave
    for (int i = 0; i < MAX_ASTEROIDES; i++)
    {
        if (asteroides[i].ativo && asteroides[i].y >= HEIGHT - 2 && abs(asteroides[i].x - nave.x) < 5)
        {
            game_over = 1; // O jogo termina se a nave for atingida
        }
    }
}

void telaGameOver()
{
    screenClear();
    printf("Game Over! Pontuação final: %d\n", score);

    // Pergunta ao jogador se deseja jogar novamente
    screenGotoxy(0, 2);
    printf("Deseja jogar novamente? (s para sim / n para não): ");
    fflush(stdout);

    while (1)
    {
        if (keyhit())
        { // Verifica se uma tecla foi pressionada
            char ch = readch();
            if (ch == 's' || ch == 'S')
            {
                inicio(); // Reinicia o jogo
                return;
            }
            else if (ch == 'n' || ch == 'N')
            {
                telainicial(); // Retorna para a tela inicial
                return;
            }
        }
    }
}

// Função principal que inicializa o jogo e executa o loop principal
int main()
{
    keyboardInit(); // Inicializa o teclado
    telainicial();  // Exibe a tela inicial

    while (1)
    {
        inicio(); // Inicializa nave, tiros e asteroides

        while (!game_over)
        {
            screenClear(); // Limpa a tela

            // Leitura de teclas para controle da nave
            if (keyhit())
            {
                char ch = readch();
                if (ch == 'q' || ch == 'Q')
                    break; // Sai do jogo
                if (ch == ' ')
                    atirar(); // Atira

                // Detecta setas esquerda e direita
                if (ch == '\033')
                { // Código de escape
                    if (keyhit() && readch() == '[')
                    { // Verifica se '[' segue o escape
                        char direction = readch();
                        if (direction == 'D')
                            movimento('L'); // Seta para esquerda
                        else if (direction == 'C')
                            movimento('R'); // Seta para direita
                    }
                }
            }

            imgnave();         // Exibe a nave
            movertiros();      // Atualiza posição dos tiros
            moverasteroides(); // Atualiza posição dos asteroides
            colisao();         // Verifica colisões

            // Desenha os tiros ativos
            for (int i = 0; i < MAX_BALAS; i++)
            {
                if (balas[i].ativo)
                {
                    screenGotoxy(balas[i].x, balas[i].y);
                    printf("|");
                }
            }

            // Desenha os asteroides ativos
            for (int i = 0; i < MAX_ASTEROIDES; i++)
            {
                if (asteroides[i].ativo)
                {
                    screenGotoxy(asteroides[i].x, asteroides[i].y);
                    printf("O");
                }
            }

            // Exibe a pontuação do jogador
            screenGotoxy(0, 0);
            printf("Score: %d", score);

            // Gera novos asteroides conforme o jogo avança
            gerarasteroides();

            // Controle da velocidade do jogo
            usleep(50000); // Ajuste o valor conforme necessário
        }

        // Chama a função de Game Over que permite ao jogador decidir jogar novamente
        telaGameOver();
    }

    keyboardDestroy(); // Restaura as configurações do teclado
    return 0;
}
