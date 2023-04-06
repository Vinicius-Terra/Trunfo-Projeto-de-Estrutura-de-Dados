#include "cartas.h"

#ifndef FILA
#define FILA
#define MAXFILA 100

typedef carta T;

typedef struct{
  unsigned quantidade, fim, inicio;
  T vetor[MAXFILA];
} fila;


void inicializaFila (fila *);
T primeiroFila (fila *);
T ultimoFila (fila *);
int cheiaFila (fila *);
int vaziaFila (fila *);
void pushFila (fila *, T);   // insere no final
void popFila (fila *);       // remove no início
void destroiFila (fila *); 


#endif

