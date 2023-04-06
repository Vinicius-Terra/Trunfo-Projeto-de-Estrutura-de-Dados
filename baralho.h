#include "fila.h"
#include "listaOrdenada.h"
#include "cartas.h"

#ifndef BARALHO
#define BARALHO

void distribuicartas(fila jogadores[], carta baralho[], int njogadores);
void mostracartadotopo(carta carta, int quemescolhe);
void inicializaBaralho(carta[]);
void shuffle(carta baralho[], int tamanho);
int maiorPeso(carta p1, carta p2);
int maiorComp(carta p1, carta p2);
int escolheAtributo(fila jogadores[], int quemEscolhe);
int maiorNota(carta p1, carta p2);
int jogaCartasNaMesa(fila jogadores[], int atributo, int njogadores);
void distribuicartas(fila jogadores[], carta baralho[], int njogadores);
void separacao1();
void separacao2();
void printaterra();

#endif
