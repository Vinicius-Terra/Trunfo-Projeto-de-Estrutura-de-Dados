#include "listaOrdenada.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// codigo baseado no codigo feito em sala pelo professor mario 

void inicializaLista(ListaOrdenada *lista, int (*maior)(T, T)) {
  lista->sentinela = (nodeLista *)malloc(sizeof(nodeLista));
  lista->sentinela->proximo = lista->sentinela->anterior = lista->sentinela;
  lista->quantidade = 0;
  lista->maior = maior;
}

int vaziaLista(ListaOrdenada *lista) {
  return lista->sentinela->proximo == lista->sentinela &&
         lista->quantidade == 0;
}

void pushLista(ListaOrdenada *lista, T data) {
  nodeLista *novo = (nodeLista *)malloc(sizeof(nodeLista));
  novo->data = data;
  nodeLista *elementoAnterior = lista->sentinela;
  nodeLista *elemento = lista->sentinela->proximo;

  while (elemento != lista->sentinela) {
    if (lista->maior(novo->data, elemento->data))
      break;
    else {
      elementoAnterior = elemento;
      elemento = elemento->proximo;
    }
  }
  novo->proximo = elemento;
  novo->anterior = elementoAnterior;
  elementoAnterior->proximo = novo;
  lista->quantidade++;
}

iterador retira(iterador i) {
  if(validoLista(i) && !vaziaLista(i.lista)) {
    nodeLista *aux = i.elemento;
    i.elemento = i.elemento->proximo;
    i.elemento->anterior = aux->anterior;
    aux->anterior->proximo = i.elemento;
    free(aux);
    i.lista->quantidade--;        
  }
  return i;
}

void destroiLista(ListaOrdenada *lista) {
  while(validoLista(retira(primeiroLista(lista))));

  free(lista->sentinela);
  lista->quantidade = 0;
  lista->sentinela = NULL;
}

iterador primeiroLista(ListaOrdenada *lista) {
  iterador i;
  i.lista = lista;
  i.elemento = lista->sentinela->proximo;
  return i;
}
iterador proximoLista(iterador i) {
  i.elemento = i.elemento->proximo;
  return i;
}
T elementoLista(iterador i) { return i.elemento->data; }
int validoLista(iterador i) { return i.elemento != i.lista->sentinela; }