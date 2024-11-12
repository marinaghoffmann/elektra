#ifndef NAVE_H
#define NAVE_H

typedef struct {
    int x, y;  // Posições x e y da nave
} Nave;

extern Nave nave;  // Declara a variável nave como extern para ser usada em outros arquivos

void desenharNave(int x, int y); // Função para desenhar a nave na tela
void moverNave();                // Função para mover a nave
void apagaNave(int x, int y);    // Função para apagar a nave
void telainicial();              // Função para a tela inicial do jogo
void desenharAsteroides();


#endif



