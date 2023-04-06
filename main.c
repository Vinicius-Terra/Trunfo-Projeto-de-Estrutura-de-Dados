/* 
========================================================================

  Grupo:
    Matheus Ferreira
    João Mesa
    Vinicius Terra
    Yasmin Rossafa

=========================================================================
*/

#include "cartas.h"
#include "fila.h"
#include "baralho.h"
#include "listaOrdenada.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// lista ordenada para a mesa
// fila para a mao dos jogadores

void mostracartadotopo(carta carta, int quemescolhe);
void inicializaBaralho(carta[]);
void jogo(fila jogadores[], int njogadores);

int maiorPeso(carta p1, carta p2) { // funcao que vai comparar peso
  return p1.peso > p2.peso;
}

int maiorComp(carta p1, carta p2) { // funcao que vai comparar peso
  return p1.alturaOUcomprimento > p2.alturaOUcomprimento;
}

int maiorNota(carta p1, carta p2) { // funcao que vai comparar peso
  return p1.notaArbitrariaEnviesada > p2.notaArbitrariaEnviesada;
}

int main(void) {
  carta baralho[16];
  int njogadores = 0;
  fila jogadores[5]; // cada jogador tem uma fila de cartas
  fila umafila; 
  
  separacao1();
  printf("BEM VINDO AO SUPER TRUNFO");
  separacao1();
  printf("\n\n\nInsira a quantidade de jogadores entre 2 e 4: ");
  scanf("%d", &njogadores);
  while (njogadores > 4 || njogadores < 2){
    printf("\nFavor escolher um valor no intervalo correto, entre 2 e 4: ");
    scanf("%d", &njogadores);
  }
  
  system("clear");
  
  for (int i = 0; i < njogadores; i++) {
    inicializaFila(&jogadores[i]);
  }
  
  inicializaBaralho(baralho);
  distribuicartas(jogadores, baralho, njogadores);

  jogo(jogadores, njogadores);

  for (int i = 0; i < njogadores; i++) {
    destroiFila(&jogadores[i]);
  }
  

  printf("\n\n\nJogo produzido pelas empresas");
  printaterra();//só fiz pela graça,se quiserem podem tirar :), ta no final do baralho

  //Ficou fofo - navesmesa
  printf("\n\n\nSorocaba, Brasil");

  return 0;
}

/**
 * @brief analisa se vai ter mais uma rodada
 *  a função ve se um ou mais jogador perdeu, ou seja, se não tem cartas na fila
 * @param jogadores 
 * @param njogadores 
 * @param cartavazia 
 * @return int 
 */

int jogoValido(fila jogadores[], int njogadores, carta cartavazia) {
  int perdedores = 0;
  for (int i = 0; i < njogadores; i++) {
    if (vaziaFila(&jogadores[i])){
      perdedores++;
      pushFila(&jogadores[i], cartavazia);
    }
  }

  if (njogadores == perdedores + 1)
    return 0; // só sobrou um jogador com cartas
  else
    return 1;
}

/**
 * @brief funcionamento do jogo 
 * 
 * @param jogadores 
 * @param njogadores 
 */
void jogo(fila jogadores[], int njogadores) {

  carta cartavazia;
  
  strcpy(cartavazia.nome, "");
  strcpy(cartavazia.descricao, "");
  cartavazia.peso = -1;
  cartavazia.alturaOUcomprimento = -1;
  cartavazia.notaArbitrariaEnviesada = -1;
  
  int quemEscolhe = 0;
  int atributo = 0;
  int vencedorJogo;
  while (jogoValido(jogadores, njogadores, cartavazia)) {
    atributo = escolheAtributo(jogadores, quemEscolhe);
    // joga as cartas e já decide quem venceu
    vencedorJogo = jogaCartasNaMesa(jogadores, atributo, njogadores);
    quemEscolhe = vencedorJogo;
  }
  printf("\nFim do jogo\n");
  printf("\nO vencedor SUPREMO foi o jogador: %d\n", vencedorJogo+1);
}