/**
 * screen.c
 * Simplified version to draw visible borders around the screen.
 */

#include "screen.h"

// Define caracteres para as bordas
#define HLINE '='   // Linha horizontal
#define VLINE '|'   // Linha vertical
#define CORNER '+'  // Cantos

void screenDrawBorders() 
{
    // Limpa a tela
    screenClear();

    // Desenha o canto superior esquerdo
    screenGotoxy(MINX, MINY);
    printf("%c", CORNER);

    // Linha superior
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MINY);
        printf("%c", HLINE);
    }

    // Desenha o canto superior direito
    screenGotoxy(MAXX, MINY);
    printf("%c", CORNER);

    // Desenha as laterais
    for (int i = MINY + 1; i < MAXY; i++) {
        screenGotoxy(MINX, i);
        printf("%c", VLINE);   // Borda esquerda
        screenGotoxy(MAXX, i);
        printf("%c", VLINE);   // Borda direita
    }

    // Desenha o canto inferior esquerdo
    screenGotoxy(MINX, MAXY);
    printf("%c", CORNER);

    // Linha inferior
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MAXY);
        printf("%c", HLINE);
    }

    // Desenha o canto inferior direito
    screenGotoxy(MAXX, MAXY);
    printf("%c", CORNER);
}

void screenInit(int drawBorders)
{
    screenClear();
    if (drawBorders) screenDrawBorders();  // Chama a função para desenhar as bordas, se ativado
    screenHomeCursor();  // Posiciona o cursor no início da tela
    screenHideCursor();  // Oculta o cursor para não interferir na visualização
}

void screenDestroy()
{
    screenClear();        // Limpa a tela ao sair
    screenHomeCursor();   // Reposiciona o cursor no início
    screenShowCursor();   // Exibe o cursor novamente
}

void screenGotoxy(int x, int y)
{
    // Ajusta os valores de x e y para garantir que estão dentro dos limites da tela
    x = ( x < 0 ? 0 : x >= MAXX ? MAXX - 1 : x);
    y = ( y < 0 ? 0 : y > MAXY ? MAXY : y);

    // Move o cursor para a posição especificada
    printf("%s[f%s[%dB%s[%dC", ESC, ESC, y, ESC, x);
}
