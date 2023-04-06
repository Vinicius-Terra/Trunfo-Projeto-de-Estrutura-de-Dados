#include "cartas.h"
#include "fila.h"
#include "baralho.h"
#include "listaOrdenada.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief manda as cartas para cada jogador.
 * É embaralhado as cartas, e cada jogador recebe uma quantia igual de cartas
 * A quantia de cartas varia com a quantidade de jogadores
 * @param jogadores 
 * @param baralho 
 * @param njogadores 
 */
void distribuicartas(fila jogadores[], carta baralho[], int njogadores) {
  int jogador = 0;
  int sobraCartas = 16 % njogadores;
  shuffle(baralho, 16-sobraCartas);
  for (int i = 0; i < (16 - sobraCartas); i++) {
    baralho[i].jogador = jogador;
    pushFila(&jogadores[jogador], baralho[i]);
    jogador++;
    if (jogador == njogadores) {
      jogador = 0;
    }
  }
}

void separacao1() {
  printf("\n\n==========================================\n\n");
}

void separacao2() { 
  printf("\n_________________________________________\n\n");
}
/**
 * @brief mostra a carta na tela
 * @param carta 
 * @param quemescolhe 
 */
void mostracartadotopo(carta carta, int quemescolhe){ 
  printf("\nEssa eh sua carta, Jogador %d", quemescolhe+1);
  separacao1();
  printf("Nome da carta: %s, %s\n", carta.nome, carta.descricao);
  separacao2();
  printf("Peso: %d", carta.peso);
  separacao2();
  printf("Altura ou Comprimento: %.1f", carta.alturaOUcomprimento);
  separacao2();
  printf("Nota: %d", carta.notaArbitrariaEnviesada);
  separacao1();
}

/**
 * @brief Embaralha as cartas.
 * serve para embaralhar as cartas do vetor baralho
 * @param baralho 
 * @param tamanho 
 */
void shuffle(carta baralho[], int tamanho){
  srand(time(NULL));
  for(int i = 0 ; i < tamanho; i++){
    int troca = rand() % tamanho;
    carta aux = baralho[i];
    baralho[i] = baralho[troca];
    baralho[troca] = aux;
    // Retirada de: https://www.youtube.com/watch?v=7OIZ_W75lAM
  }
}

/**
 * @brief mostra as cartas em jogo, decide que foi o vencedor da rodada,
 * atribui as cartas que foram jogadas na mesa ao vencedor e mostra o atual
 * numero de cartas de cada jogador
 * @param jogadores 
 * @param atributo 
 * @param njogadores 
 * @return int 
 */
int jogaCartasNaMesa(fila jogadores[], int atributo, int njogadores) {
  int vencedor;
  carta carta;
  ListaOrdenada mesa; // a mesa é uma lista ordenada
  switch (atributo) {
  case 1:
    inicializaLista(&mesa, maiorPeso);
    break;

  case 2:
    inicializaLista(&mesa, maiorComp);
    break;

  case 3:
    inicializaLista(&mesa, maiorNota);
    break;

  default:
    printf("Erro brutal!\n");
  }

  printf("Cartas em jogo:\n");
  for (int i = 0; i < njogadores; i++) {
    if (vaziaFila(&jogadores[i])){
      break;
    }
    else{
      carta = primeiroFila(&jogadores[i]);
    }
    switch (atributo) {
    case 1:
      if(carta.peso > -1)
        printf("===== Jogador %d - %s, Peso = %d ====\n", i+1, carta.nome, carta.peso);
      break;
    case 2:
      if(carta.alturaOUcomprimento > -1)
        printf("===== Jogador %d - %s, Altura ou Comprimento = %.1f ====\n", i+1, carta.nome, carta.alturaOUcomprimento);
      break;
    case 3:
      if(carta.notaArbitrariaEnviesada > -1)
        printf("===== Jogador %d - %s, Nota = %d ====\n", i+1, carta.nome, carta.notaArbitrariaEnviesada);
      break;
    default:
      printf("Erro brutal!\n");
  }
    if (!vaziaFila(&jogadores[i])){
      pushLista(&mesa, carta);
      popFila(&jogadores[i]);
    }
  }

  iterador i;
  i = primeiroLista(&mesa);
  carta = elementoLista(i);
  vencedor = carta.jogador;

  printf("\nJogador %d venceu a rodada com sua carta: %s\n", carta.jogador + 1, carta.nome);
  separacao2();
  printf("\nQUANTIDADE DE CARTAS\n\n");

  while (validoLista(i)) {
    carta = elementoLista(i);
    carta.jogador = vencedor;
    if(carta.peso > 0)
      pushFila(&jogadores[vencedor], carta);
    i = proximoLista(i);
  }

  for(int cont = 0; cont<njogadores;cont++){
    if (jogadores[cont].quantidade == 0){
      printf("=== Jogador %d foi eliminado! ===\n\n", cont+1);
    }else{
    printf("=== Jogador %d esta com %d cartas! ===\n\n", cont+1, jogadores[cont].quantidade);
      }
  }
  
  destroiLista(&mesa);
  return vencedor;
}

/**
 * @brief o jogador escolhe o atributo da carta.
 * O jogador escolhe entre: peso, tamanho e nota. 
 * @param jogadores 
 * @param quemEscolhe 
 * @return int 
 */
int escolheAtributo(fila jogadores[], int quemEscolhe) {
  int escolha = 0;
  carta carta;
  carta = primeiroFila(&jogadores[quemEscolhe]);

  mostracartadotopo(carta, quemEscolhe);

  printf("\nQual atributo voce vai escolher?");
  printf("\n1 - Peso \n2 - Altura OU Comprimento \n3 - Nota Arbitraria "
         "Enviesada\n");
  scanf("%d", &escolha);
  while (0 > escolha || escolha > 3) {
    printf("\n Escolha um numero entre 1 e 3\n");
    scanf("%d", &escolha);
  }
  system("clear");
  return escolha;
}
/**
 * @brief função que armazena as cartas.
 * Onde está armazenado o conteúdo das cartas, e será repassado para o vetor baralho
 * @param baralho 
 */
void inicializaBaralho(carta baralho[16]) {
  carta baralhoPadrao[16];
  
  strcpy(baralhoPadrao[0].nome, "Dire wolf");
  strcpy(baralhoPadrao[0].descricao, "O Lobo Terrível");
  baralhoPadrao[0].peso = 80;
  baralhoPadrao[0].alturaOUcomprimento = 2;
  baralhoPadrao[0].notaArbitrariaEnviesada = 7;

  strcpy(baralhoPadrao[1].nome, "Deinosuchus");
  strcpy(baralhoPadrao[1].descricao, "O Crocodilo Gigante");
  baralhoPadrao[1].peso = 2500;
  baralhoPadrao[1].alturaOUcomprimento = 10;
  baralhoPadrao[1].notaArbitrariaEnviesada = 2;

  strcpy(baralhoPadrao[2].nome, "Gliptodontes");
  strcpy(baralhoPadrao[2].descricao, "Tatu-gigante");
  baralhoPadrao[2].peso = 1500;
  baralhoPadrao[2].alturaOUcomprimento = 2;
  baralhoPadrao[2].notaArbitrariaEnviesada = 4;//rabo roubado, mas locomoçao limitada :)

  strcpy(baralhoPadrao[3].nome, "Quetzalcoatlus");
  strcpy(baralhoPadrao[3].descricao, "O Maior Pterossauro");
  baralhoPadrao[3].peso = 70;
  baralhoPadrao[3].alturaOUcomprimento = 10;
  baralhoPadrao[3].notaArbitrariaEnviesada = 12;

  strcpy(baralhoPadrao[4].nome, "Paraphysornis brasiliensis");
  strcpy(baralhoPadrao[4].descricao, "Ave do Terror");
  baralhoPadrao[4].peso = 200;
  baralhoPadrao[4].alturaOUcomprimento = 2;
  baralhoPadrao[4].notaArbitrariaEnviesada = 11;//praticamente um galo gigante, tem asa mas não voa

  strcpy(baralhoPadrao[5].nome, "Elasmotherium");
  strcpy(baralhoPadrao[5].descricao,"Um Rinoceronte Com 2 Metros Só de Chifre"); 
  baralhoPadrao[5].peso = 4000;
  baralhoPadrao[5].alturaOUcomprimento = 6;
  baralhoPadrao[5].notaArbitrariaEnviesada = 6;

  strcpy(baralhoPadrao[6].nome, "Gigantopithechus");
  strcpy(baralhoPadrao[6].descricao, "O Maior dos Primatas");
  baralhoPadrao[6].peso = 270;    
  baralhoPadrao[6].alturaOUcomprimento = 3.7;
  baralhoPadrao[6].notaArbitrariaEnviesada = 14;

  strcpy(baralhoPadrao[7].nome, "Titanoboa");
  strcpy(baralhoPadrao[7].descricao, "A Maior das Serpentes");
  baralhoPadrao[7].peso = 1135;
  baralhoPadrao[7].alturaOUcomprimento = 13;
  baralhoPadrao[7].notaArbitrariaEnviesada = 8;

  strcpy(baralhoPadrao[8].nome, "Pacarana-gigante");
  strcpy(baralhoPadrao[8].descricao, "A Capivara Gigante");
  baralhoPadrao[8].peso = 1000;
  baralhoPadrao[8].alturaOUcomprimento = 3 ;//comprimento
  baralhoPadrao[8].notaArbitrariaEnviesada = 16;//capivara ja é braba, gigante então...

  strcpy(baralhoPadrao[9].nome, "Argentavis");
  strcpy(baralhoPadrao[9].descricao, "A Maior Ave Voadora");
  baralhoPadrao[9].peso = 90;
  baralhoPadrao[9].alturaOUcomprimento = 6.5;
  baralhoPadrao[9].notaArbitrariaEnviesada = 10;

  strcpy(baralhoPadrao[10].nome, "Brontossauros");
  strcpy(baralhoPadrao[10].descricao, "O Maior Dinossauro");
  baralhoPadrao[10].peso = 40000;
  baralhoPadrao[10].alturaOUcomprimento = 22;
  baralhoPadrao[10].notaArbitrariaEnviesada = 3;

  strcpy(baralhoPadrao[11].nome, "Paraceratherium");
  strcpy(baralhoPadrao[11].descricao, "O Rinoceronte Pescoçudo");
  baralhoPadrao[11].peso = 20000; baralhoPadrao[11].alturaOUcomprimento = 7.4 ;
  //comprimento 
baralhoPadrao[11].notaArbitrariaEnviesada = 4;//gigante mas é herbivoro, potencial desperdiçado, praticamente é o nando vegano


  strcpy(baralhoPadrao[12].nome, "Smilodon"); //repetido
  strcpy(baralhoPadrao[12].descricao, "Tigre Dentes-de-Sabre");
  baralhoPadrao[12].peso = 900 ;
  baralhoPadrao[12].alturaOUcomprimento = 3 ;//comprimento
  baralhoPadrao[12].notaArbitrariaEnviesada = 13;//é um tigre de 3 metros dentuço, náo preciso falar mais nd

  strcpy(baralhoPadrao[13].nome, "Meganeura");
  strcpy(baralhoPadrao[13].descricao, "A Libelula gigante");
  baralhoPadrao[13].peso = 1 ;//0.07 mas precisa de um int
  baralhoPadrao[13].alturaOUcomprimento = 0.75 ;//comprimento
  baralhoPadrao[13].notaArbitrariaEnviesada = 1;//bicho sem graça, se botar na churrasqueira não mata a fome de uma criança

  strcpy(baralhoPadrao[14].nome, "Mammuthus columbi");
  strcpy( baralhoPadrao[14].descricao, "O Mamute");
  baralhoPadrao[14].peso = 9000 ;
  baralhoPadrao[14].alturaOUcomprimento = 4 ;
  baralhoPadrao[14].notaArbitrariaEnviesada = 15;//elefante peludo

  strcpy(baralhoPadrao[15].nome, "Spinosaurus");
  strcpy(baralhoPadrao[15].descricao, "Espinossauro: T-Rex Aquatico");
  baralhoPadrao[15].peso = 20000 ;
  baralhoPadrao[15].alturaOUcomprimento = 18 ;
  baralhoPadrao[15].notaArbitrariaEnviesada = 9;//na agua ganha de qualquer um

  for (int i = 0; i < 16; i++) {
    baralho[i] = baralhoPadrao[i];
  }
}

/**
 * @brief Print do final do jogo.
 * 
 */
void printaterra(){
   printf("\n\n\n");
   printf(" __    __    ______   _        _         ________   \n");
    printf("|  |  |  |  |  ____| | |      | |       |  ____  |  \n");
    printf("|  |__|  |  | |__    | |      | |       | |    | |  \n");
    printf("|   __   |  |  __|   | |      | |       | |    | |  \n");
    printf("|  |  |  |  | |____  | |____  | |____   | |____| |  \n");
    printf("|__|  |__|  |______| |______| |______|  |________|   \n");
        

    printf("\n");
    printf("   _______                             \n");
    printf("  |__   __|                        \n");
    printf("     | |   ____   _ __  _ __   __ _       \n");
    printf("     | |  / _  | | '__|| '__| / _` |\n");
    printf("     | | |  __/  | |   | |   | (_| |   \n");
    printf("     |_| |___|   |_|   |_|   |__,__|  \n");
   

  
}
