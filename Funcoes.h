//
//  Funcoes.h
//  Simulador de Elevador
//
//  Created by Lucas Cavalcante Corrêa on 05/05/2018.
//  Copyright © 2018 Lucas Cavalcante Corrêa. All rights reserved.
//

#ifndef Funcoes_h
#define Funcoes_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>

struct rusage usage;
struct timeval UsuarioInicial,UsuarioFinal, SistemaIncial, SistemaFinal, TempoIncial, TempoFinal;

typedef struct {
    int momento,andarPassageiro,destinoPassageiro,tempoEspera, momento_elevador;
}tipo_evento ;

//para lista do elevador
typedef struct Celula_str *Apontador;
typedef struct Celula_str {
    tipo_evento item;
    Apontador prox;
} Celula;
typedef struct {
    Apontador Primeiro, Ultimo;
} TipoLista;

//para cada fila na lista de andares
typedef struct Celula_str3 *Apontador3;
typedef struct Celula_str3 {
    tipo_evento item;
    Apontador3 prox;
} CelulaF;

typedef struct  {
    Apontador3 Frente, Tras;
} TipoFila;

//para a lista de andares (de filas)
typedef struct Celula_str2 *Apontador2;
typedef struct Celula_str2 {
    TipoFila Fila;
    Apontador2 prox;
} CelulaFila;

typedef struct  {
    Apontador2 Primeiro, Ultimo;
} TipoListaAndares;


///////////////////////////////////////////
/////////////////FUNÇÕES///////////////////
///////////////////////////////////////////


void FLVazia(TipoLista *Lista);

void FFVazia(TipoFila *Fila);

void FLVaziaA(TipoListaAndares *Lista);

void Insere(tipo_evento x,TipoLista *Lista);

void InsereAndar(TipoFila x,TipoListaAndares *Lista);

void Enfileira(tipo_evento x,TipoFila *Fila );

void Desenfileira(TipoFila *Fila);

int Adiciona_Eventos(tipo_evento *evento, int contador, TipoLista *Lista, FILE *eventos, TipoListaAndares *Andar, long *posicao);

int SaidaElevadorFCFS(int *Zepslon, int *contador, int *lotacao, int *andar, TipoLista *Lista, TipoListaAndares *Andar, int max_pessoas);

int SaidaElevadorSJF(int *Zepslon, int *contador, int *lotacao, int *andar, TipoLista *Lista, TipoListaAndares *Andar, int max_pessoas);

int EntraElevador(int Zepslon, int andar, int lotacao, int max_pessoas, TipoListaAndares *Andar, TipoLista *Lista);

int SentidoFCFS(int andar, TipoLista *Lista, TipoListaAndares *Andar, int max_andares, int contador);

int SentidoSJF(int andar, TipoLista *Lista, TipoListaAndares *Andar, int max_andares, int contador);

#endif /* Funcoes_h */
