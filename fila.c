#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicializaFila(fila *fila) {
  fila->inicio = 0;
  fila->fim = 0;
  fila->quantidade = 0;
}

T primeiroFila(fila *fila){
  return fila->vetor[fila->inicio];
}

T ultimoFila(fila *fila){
  return fila->vetor[fila->fim-1];
}

int vaziaFila(fila *fila) {
  if(fila->quantidade == 0)
    return 1;
  else
    return 0;
}

int cheiaFila(fila *fila) {
  if(fila->quantidade == MAXFILA)
    return 1;
  else
    return 0;
}

void pushFila(fila *fila, T data) {
  if(cheiaFila(fila))
    printf("cheia\n");
  else{
    if(fila->fim == MAXFILA)
      fila->fim = 0;
    fila->vetor[fila->fim] = data;
    fila->fim++;
    fila->quantidade++;
  }
}

void popFila(fila *fila) {
  if (vaziaFila(fila))
    printf("vazia\n");
  else{
    fila->inicio++;
    fila->quantidade--;
    if(fila->inicio == MAXFILA)
      fila->inicio = 0;
  }
}

void destroiFila(fila *fila) {
  while (!vaziaFila(fila)) {
    popFila(fila);
  }
}
