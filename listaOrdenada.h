#include "cartas.h"

#ifndef LISTAORDENADA
#define LISTAORDENADA

typedef carta T;

struct nodeLista{
	T data;
  struct nodeLista *proximo;
  struct nodeLista *anterior;
};

typedef struct nodeLista nodeLista;

typedef struct {
    nodeLista *sentinela;
    unsigned quantidade;
    int (*maior)(T,T);    //funcao que compara T com T e retorna
} ListaOrdenada;          // qual 1 se o primeiro for o maior
                          // e 0 caso seja falso
typedef struct {
    nodeLista *elemento;
    ListaOrdenada *lista;
} iterador;

void inicializaLista(ListaOrdenada *, int (*)(T,T) );
void destroiLista(ListaOrdenada *);
void pushLista(ListaOrdenada *, T );
void removePrimeiroLista(ListaOrdenada *);
int vaziaLista(ListaOrdenada*);
iterador primeiroLista(ListaOrdenada*);
iterador proximoLista(iterador);
T elementoLista(iterador);
int validoLista(iterador);

#endif

