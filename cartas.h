#ifndef CARTA
#define CARTA
//tamanho baralho
#define TAMBARALHO 50


typedef struct{
  char nome[150];
  char descricao[150];
  int peso;
  double alturaOUcomprimento;
  int notaArbitrariaEnviesada;
  int jogador;
} carta;


#endif

