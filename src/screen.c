#include "screen.h"

/**
 * Função para limpar a tela e mover o cursor para a posição inicial.
 */
void screenClear() {
    printf("%s%s", ESC, CLEARSCREEN);  // Limpa a tela
    screenHomeCursor();                // Move o cursor para a posição inicial
}

/**
 * Função para mover o cursor para a posição (x, y).
 */
void screenGotoxy(int x, int y) {
    x = (x < MINX ? MINX : x >= MAXX ? MAXX - 1 : x);
    y = (y < MINY ? MINY : y > MAXY ? MAXY : y);
    printf("%s[%d;%dH", ESC, y, x); // Move o cursor para a posição (x, y)
}

/**
 * Função para definir as cores de texto e fundo na tela.
 */
void screenSetColor(screenColor fg, screenColor bg) {
    char atr[] = "[0;";
    if (fg > LIGHTGRAY) {
        atr[1] = '1';
        fg -= 8;
    }
    printf("%s%s%d;%dm", ESC, atr, fg + 30, bg + 40); // Configura cores
}

/**
 * Função para desenhar as bordas da tela.
 */
void screenDrawBorders() {
    screenClear();
    screenBoxEnable();  // Ativa caracteres de borda

    // Canto superior esquerdo
    screenGotoxy(SCRSTARTX, SCRSTARTY);
    printf("%c", BOX_UPLEFT);

    // Linha horizontal superior
    for (int i = SCRSTARTX + 1; i < SCRENDX; i++) {
        screenGotoxy(i, SCRSTARTY);
        printf("%c", BOX_HLINE);
    }

    // Canto superior direito
    screenGotoxy(SCRENDX, SCRSTARTY);
    printf("%c", BOX_UPRIGHT);

    // Linhas verticais laterais
    for (int i = SCRSTARTY + 1; i < SCRENDY; i++) {
        screenGotoxy(SCRSTARTX, i);
        printf("%c", BOX_VLINE);
        screenGotoxy(SCRENDX, i);
        printf("%c", BOX_VLINE);
    }

    // Canto inferior esquerdo
    screenGotoxy(SCRSTARTX, SCRENDY);
    printf("%c", BOX_DWNLEFT);

    // Linha horizontal inferior
    for (int i = SCRSTARTX + 1; i < SCRENDX; i++) {
        screenGotoxy(i, SCRENDY);
        printf("%c", BOX_HLINE);
    }

    // Canto inferior direito
    screenGotoxy(SCRENDX, SCRENDY);
    printf("%c", BOX_DWNRIGHT);

    screenBoxDisable(); // Desativa caracteres de borda
}

/**
 * Inicializa a tela, limpando e desenhando bordas se especificado.
 */
void screenInit(int drawBorders) {
    screenClear();
    if (drawBorders) screenDrawBorders();
    screenHomeCursor();
    screenHideCursor();
}

/**
 * Restaura a tela para o estado normal e exibe o cursor.
 */
void screenDestroy() {
    screenSetNormal();
    screenClear();
    screenHomeCursor();
    screenShowCursor();
}
