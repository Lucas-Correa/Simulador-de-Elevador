//
//  Estrategias.c
//  Simulador de Elevador
//
//  Created by Lucas Cavalcante Corrêa on 04/05/2018.
//  Copyright © 2018 Lucas Cavalcante Corrêa. All rights reserved.
//

#include "Estrategias.h"

///////////////////////////////////////////
/////////////////FCFS//////////////////////
///////////////////////////////////////////

//essa estratégia considera o passageiro que pediu primeiro o elevador. Se houver algum passageiro no elevador, ele dará preferências para o seu pedido. Dentro da função, existem 2 (dois) whiles, o primeiro vai rodar as funções da estratégia até todos os eventos na lista de evento serem lidos. Após esse while, o while 2 vai fazer a estratégia rodar as suas funções até não existir ninguém mais no elevador nem nos andares, ou seja, até as listas do elevador e dos andares estiverem vazias. Após esses dois whiles, estará garantido que todas as pessoas na lista de eventos foram atendidas.
void FCFS(FILE *amb_elevador, FILE *eventos){
    int max_pessoas,max_andares,lotacao=0, andar=0, contador=1, Zepslon=0, d=0,check=0, saiu;
    tipo_evento evento;
    TipoLista *Lista;
    TipoListaAndares *Andar;
    long posicao;
    
    // pegar as informaçoes
    fscanf(amb_elevador,"%d%d", &max_andares, &max_pessoas);
    
    // Alocando espaço e inicializando a lista do elevador (Lista) e a lista de andares (Andar)
    Andar = (TipoListaAndares*) malloc(sizeof(TipoListaAndares)*max_andares);
    Lista = (TipoLista*) malloc(sizeof(TipoLista));
    FLVaziaA(Andar);
    FLVazia(Lista);
    
    // o primeiro while
    while (Adiciona_Eventos(&evento, contador, Lista, eventos, Andar,&posicao)==1){
        
        //essa variável é para eveitar dupla contagem de Zepslon caso o elevador deixou pessoas sairem e etrarem em determinado andar
        saiu=0;
        //*****************CHECANDO A SAIDA*****************//
        if(!(Lista->Primeiro==Lista->Ultimo)){
            if(SaidaElevadorFCFS(&Zepslon, &contador,&lotacao, &andar, Lista, Andar, max_pessoas)==1){
                Zepslon++;
                contador++;
                Adiciona_Eventos(&evento, contador, Lista, eventos, Andar,&posicao);
                saiu=1;
            }
        }
        
        //*****************CHECANDO A ENTRADA*****************//
        d=EntraElevador(Zepslon, andar, lotacao, max_pessoas, Andar, Lista);
        
        if(d!=0){
            if(saiu==0){
                Zepslon++;
            }
            contador++;
            lotacao=d;
            Adiciona_Eventos(&evento, contador, Lista, eventos, Andar,&posicao);
        }
        
        //*****************CHECANDO O SENTIDO*****************//
        d=SentidoFCFS(andar, Lista,Andar, max_andares, contador);
        if(d!=-1){
            Zepslon++;
            contador++;
            andar=d;
            Adiciona_Eventos(&evento, contador, Lista, eventos, Andar,&posicao);
        }
    }
    
    check=0;
    if(check==0 && Andar->Primeiro!=Andar->Ultimo){
        check=1;
    }
    
    
    
    while(Lista->Primeiro!=Lista->Ultimo || check==1){
        
        saiu=0;
        //*****************CHECANDO A SAIDA*****************//
        if(!(Lista->Primeiro->prox==NULL)){
            if(SaidaElevadorFCFS(&Zepslon, &contador,&lotacao, &andar, Lista, Andar, max_pessoas)==1){
                Zepslon++;
                contador++;
                saiu=1;
            }
        }
        
        
        //*****************CHECANDO A ENTRADA*****************//
        d=EntraElevador(Zepslon, andar, lotacao, max_pessoas, Andar, Lista);
        
        if(d!=0){
            if(saiu==0){
                Zepslon++;
            }
            contador++;
            lotacao=d;
        }
        //*****************CHECANDO O SENTIDO*****************//
        d=SentidoFCFS(andar, Lista,Andar, max_andares, contador);
        if(d!=-1){
            Zepslon++;
            contador++;
            andar=d;
        }
        
        
        check=0;
        if(check==0 && Andar->Primeiro!=Andar->Ultimo){
            check=1;
        }
    }
    
    printf("\n\nZepslon: %d\nContador: %d\n", Zepslon, contador);
}

///////////////////////////////////////////
/////////////////SJF//////////////////////
///////////////////////////////////////////

//essa estratégia considera o pedido mais perto. Se houver algum passageiro no elevador, ele dará preferências para a distancia seu pedido. Dentro da função, existem 2 (dois) whiles, o primeiro vai rodar as funções da estratégia até todos os eventos na lista de evento serem lidos. Após esse while, o while 2 vai fazer a estratégia rodar as suas funções até não existir ninguém mais no elevador nem nos andares, ou seja, até as listas do elevador e dos andares estiverem vazias. Após esses dois whiles, estará garantido que todas as pessoas na lista de eventos foram atendidas.
void SJF(FILE *amb_elevador, FILE *eventos){
    int max_pessoas,max_andares,lotacao=0, andar=0, contador=1, Zepslon=0, d=0,check=0, saiu;
    tipo_evento evento;
    TipoLista *Lista;
    TipoListaAndares *Andar;
    long posicao;
    
    //pega as informações do ambiente do predio
    fscanf(amb_elevador,"%d%d", &max_andares, &max_pessoas);
    
    // Alocando espaço e inicializando a lista do elevador (Lista) e a lista de andares (Andar)
    Andar = (TipoListaAndares*) malloc(sizeof(TipoListaAndares)*max_andares);
    Lista = (TipoLista*) malloc(sizeof(TipoLista));
    FLVaziaA(Andar);
    FLVazia(Lista);
    
    
    while (Adiciona_Eventos(&evento, contador, Lista, eventos, Andar,&posicao)==1){
        
        //essa variável é para eveitar dupla contagem de Zepslon caso o elevador deixou pessoas sairem e etrarem em determinado andar
        saiu=0;
        //*****************CHECANDO A SAIDA*****************//
        if(!(Lista->Primeiro==Lista->Ultimo)){
            if(SaidaElevadorSJF(&Zepslon, &contador,&lotacao, &andar, Lista, Andar, max_pessoas)==1){
                Zepslon++;
                contador++;
                Adiciona_Eventos(&evento, contador, Lista, eventos, Andar,&posicao);
                saiu=1;
            }
        }
        
        //*****************CHECANDO A ENTRADA*****************//
        d=EntraElevador(Zepslon, andar, lotacao, max_pessoas, Andar, Lista);
        
        if(d!=0){
            if(saiu==0){
            Zepslon++;
            }
            contador++;
            lotacao=d;
            Adiciona_Eventos(&evento, contador, Lista, eventos, Andar,&posicao);
        }
        
        //*****************CHECANDO O SENTIDO*****************//
        d=SentidoSJF(andar, Lista,Andar, max_andares, contador);
        if(d!=-1){
            Zepslon++;
            contador++;
            andar=d;
            Adiciona_Eventos(&evento, contador, Lista, eventos, Andar,&posicao);
        }
        
        
    }
    
    check=0;
    if(check==0 && Andar->Primeiro!=Andar->Ultimo){
        check=1;
    }
    
    
    
    while(Lista->Primeiro!=Lista->Ultimo || check==1){
        
        saiu=0;
        //*****************CHECANDO A SAIDA*****************//
        if(!(Lista->Primeiro->prox==NULL)){
            if(SaidaElevadorSJF(&Zepslon, &contador,&lotacao, &andar, Lista, Andar, max_pessoas)==1){
                Zepslon++;
                contador++;
                saiu=1;
            }
        }
        
        
        //*****************CHECANDO A ENTRADA*****************//
        d=EntraElevador(Zepslon, andar, lotacao, max_pessoas, Andar, Lista);
        
        if(d!=0){
            if(saiu==0){
                Zepslon++;
            }
            contador++;
            lotacao=d;
        }
        //*****************CHECANDO O SENTIDO*****************//
        d=SentidoSJF(andar, Lista,Andar, max_andares, contador);
        if(d!=-1){
            Zepslon++;
            contador++;
            andar=d;
        }
        
        
        check=0;
        if(check==0 && Andar->Primeiro!=Andar->Ultimo){
            check=1;
        }
    }
    
    printf("\n\nZepslon: %d\nContador: %d\n", Zepslon, contador);
}
