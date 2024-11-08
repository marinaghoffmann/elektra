/**
 * screen.c
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
 */

#include "screen.h"

void screenDrawBorders() 
{
    char hbc = '=';  // Novo caractere para linha horizontal
    char vbc = '|';  // Novo caractere para linha vertical
    
    screenClear();
    screenBoxEnable();  // Ativa modo de desenho de caixa, se implementado

    // Canto superior esquerdo
    screenGotoxy(MINX, MINY);
    printf("+");

    // Linha superior
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MINY);
        printf("%c", hbc);
    }

    // Canto superior direito
    screenGotoxy(MAXX, MINY);
    printf("+");

    // Laterais
    for (int i = MINY + 1; i < MAXY; i++) {
        screenGotoxy(MINX, i);
        printf("%c", vbc);   // Borda esquerda
        screenGotoxy(MAXX, i);
        printf("%c", vbc);   // Borda direita
    }

    // Canto inferior esquerdo
    screenGotoxy(MINX, MAXY);
    printf("+");

    // Linha inferior
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MAXY);
        printf("%c", hbc);
    }

    // Canto inferior direito
    screenGotoxy(MAXX, MAXY);
    printf("+");

    screenBoxDisable();  // Desativa modo de desenho de caixa, se implementado
}

void screenInit(int drawBorders)
{
    screenClear();
    if (drawBorders) screenDrawBorders();
    screenHomeCursor();
    screenHideCursor();
}

void screenDestroy()
{
    printf("%s[0;39;49m", ESC); // Reset colors
    screenSetNormal();
    screenClear();
    screenHomeCursor();
    screenShowCursor();
}

void screenGotoxy(int x, int y)
{
    x = ( x<0 ? 0 : x>=MAXX ? MAXX-1 : x);
    y = ( y<0 ? 0 : y>MAXY ? MAXY : y);
    
    printf("%s[f%s[%dB%s[%dC", ESC, ESC, y, ESC, x);
}
