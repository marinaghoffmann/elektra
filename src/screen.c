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
    
    // Configuração de cor opcional para a borda, se suportado pelo terminal
    screenSetColor(LIGHTBLUE, BLACK);

    screenClear();
    screenBoxEnable();
    
    screenGotoxy(MINX, MINY);
    printf("#");  // Canto superior esquerdo

    // Linha superior
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MINY);
        printf("%c", hbc);
    }
    screenGotoxy(MAXX, MINY);
    printf("#");  // Canto superior direito

    // Linhas laterais
    for (int i = MINY + 1; i < MAXY; i++) {
        screenGotoxy(MINX, i);
        printf("%c", vbc);
        screenGotoxy(MAXX, i);
        printf("%c", vbc);
    }

    screenGotoxy(MINX, MAXY);
    printf("#");  // Canto inferior esquerdo

    // Linha inferior
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MAXY);
        printf("%c", hbc);
    }
    screenGotoxy(MAXX, MAXY);
    printf("#");  // Canto inferior direito

    screenBoxDisable();

    // Restaura a cor normal da tela após desenhar a borda
    screenSetNormal();
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

void screenSetColor(screenColor fg, screenColor bg)
{
    char atr[] = "[0;";

    if ( fg > LIGHTGRAY )
    {
        atr[1] = '1';
        fg -= 8;
    }

    printf("%s%s%d;%dm", ESC, atr, fg+30, bg+40);
}
