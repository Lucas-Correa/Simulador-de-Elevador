//
//  Funcoes.c
//  Simulador de Elevador
//
//  Created by Lucas Cavalcante Corrêa on 05/05/2018.
//  Copyright © 2018 Lucas Cavalcante Corrêa. All rights reserved.
//

#include "Funcoes.h"

//Esvizar as Listas
void FLVazia(TipoLista *Lista) {
    Lista->Primeiro = (Apontador) malloc(sizeof(Celula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->prox = NULL;
}

//Esvaziar as Filas
void FFVazia(TipoFila *Fila)
{
    Fila->Frente = (Apontador3) malloc(sizeof(CelulaF));
    Fila->Tras = Fila->Frente;
    Fila->Frente->prox = NULL;
}

//Esvizar as Listas de Andares
void FLVaziaA(TipoListaAndares *Lista) {
    Lista->Primeiro = (Apontador2) malloc(sizeof(CelulaFila));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->prox = NULL;
    FFVazia(&Lista->Primeiro->Fila);
}

//Insere na listar
void Insere(tipo_evento x,TipoLista *Lista)
{
    Lista->Ultimo->prox = (Apontador) malloc(sizeof(Celula));
    Lista->Ultimo = Lista->Ultimo->prox;
    Lista->Ultimo->item = x;
    Lista->Ultimo->prox = NULL;
}

//Insere na listar de Andares
void InsereAndar(TipoFila x,TipoListaAndares *Lista)
{
    Lista->Ultimo->prox = (Apontador2) malloc(sizeof(CelulaFila));
    Lista->Ultimo = Lista->Ultimo->prox;
    Lista->Ultimo->Fila = x;
    Lista->Ultimo->prox = NULL;
}

//coloca um item na fila pelo andar
void Enfileira(tipo_evento x,TipoFila *Fila )
{
    Fila->Tras->prox = (Apontador3) malloc(sizeof(Celula));
    Fila->Tras = Fila->Tras->prox;
    Fila->Tras->item = x;
    Fila->Tras->prox = NULL;
}

//Desenfileira
void Desenfileira(TipoFila *Fila)
{
    Apontador3 q;
    q = Fila->Frente;
    Fila->Frente = Fila->Frente->prox;
    free(q);
}

// adiciona um evento na fila se o contador concidir com o momento do proximo evento
int Adiciona_Eventos(tipo_evento *evento, int contador, TipoLista *Lista, FILE *eventos, TipoListaAndares *Andar, long *posicao){
    
    //se não houverem mais eventos a serem lidos, essa função retorna 0, o que será importante para a função da estratégia terminar o primeiro while.
    if(fscanf(eventos,"%d %d %d",&evento->momento,&evento->andarPassageiro,&evento->destinoPassageiro)==EOF){
        return 0;
    };
    
    //após ler o próximo evento, é verificado se esse evento aconteceu ou está acontecendo, comparando com o "contador" se ele passar no teste, esse evento será acrescido na fila do andar de origem. Se ele não passar, o ponteiro na leitura do arquivo volta pro início desse evento testado para que ele possa ser lido e checado novamente quando a função for chamada
    if(evento->momento<=contador){
        int i=0;
        Apontador2 aux;
        
        aux=Andar->Primeiro->prox;
        
        // esse while serve para buscar a fila na lista de andares que é a fila do andar do novo evento
        while(aux!=NULL){
            if(aux->Fila.Frente->prox->item.andarPassageiro==evento->andarPassageiro){
                Enfileira(*evento, &aux->Fila);
                i=1;
            }
            aux=aux->prox;
        }
        
        //caso não seja encontrado uma fila desse andar, é porque não têm ninguem esperando o elevador nesse andar. Nesse caso, precisa-se criar uma nova fila para esse andar.
        if(i==0){
            TipoFila Fila;
            FFVazia(&Fila);
            Enfileira(*evento,&Fila);
            InsereAndar(Fila,Andar);
        }
        
        //marca a posição da leitura do último evento no contador certo
        *posicao = ftell(eventos);
        
    }else{
        //se o evento não estiver no tempo certo, o próximo comando vai levar o ponteiro de leitura do arquivo de volta para o início do evento que ainda não aconteceu para que ele posa ser lido depois pelo fscanf no iniício dessa função
        fseek (eventos,*posicao, 0);
    }
    
    return 1;
}

//só sai alguém do elevador, se o elevador estiver no destino do primeiro pedido ou se alguém no meo do caminho chamou o elevador e ele possui espaço. Dessa forma, a função verifica na lista do elevador se é o andar destino do primeiro pedido ou se o elevador parou para um pedido no meio e por concequencia os passageiros com destino no andar em questão vão poder descer.
int SaidaElevadorFCFS(int *Zepslon, int *contador, int *lotacao, int *andar, TipoLista *Lista, TipoListaAndares *Andar, int max_pessoas){
    int aux1=0, check=0;
    Apontador j, elAnterior;
    Apontador2 aux;
    j=Lista->Primeiro->prox;
    aux=Andar->Primeiro->prox;
    
    //verifica se têm algum passageiro que pediu o elevador nesse andar e o elevador tiver que parar porque têm espaço
    if(*lotacao<max_pessoas){
        while(aux!=NULL){
            if(aux->Fila.Frente->prox->item.andarPassageiro == *andar){
                check=1;
            }
            aux=aux->prox;
        }
    }
    
    //verifica se o elevador precisa parar porque é o destino do primeiro passageiro a pedir ou porque o elevador tem espaço e alguém desse andar pediu para entrar
    if(check==1 || (j!=NULL && j->item.destinoPassageiro == *andar)){
        //esse while procura na lista do elevador os elementos que são daquele andar. Quando ele acha, o elemento é retirado da lista de andares.
        elAnterior=Lista->Primeiro;
        while (j!=NULL) {
            if(j->item.destinoPassageiro == *andar){
                printf("\n\nSai passageiro com: momento %d, origem %d e destino %d\n Lotacao: %d\n Zepslon: %d\n Andar: %d\n Tempo de espera: %d\n Tempo de espera dentro do elevador: %d", j->item.momento, j->item.andarPassageiro, j->item.destinoPassageiro, *lotacao-1, *Zepslon+1,j->item.destinoPassageiro, j->item.tempoEspera, *Zepslon - j->item.momento_elevador );
                Apontador q;
                q=j;
                elAnterior->prox=j->prox;
                j=elAnterior->prox;
                free(q);
                *lotacao=*lotacao-1;
                aux1=1;
            }else{
                elAnterior=elAnterior->prox;
                j = j->prox;
            }
        }
        Lista->Ultimo=elAnterior;
    }
    
    if(aux1==1){
        return 1;
    }else{
        return 0;
    }
}

int SaidaElevadorSJF(int *Zepslon, int *contador, int *lotacao, int *andar, TipoLista *Lista, TipoListaAndares *Andar, int max_pessoas){
    int aux1=0, check=0, check2=0;
    Apontador j, elAnterior;
    Apontador2 aux;
    j=Lista->Primeiro->prox;
    aux=Andar->Primeiro->prox;
    
    //verifica se têm algum passageiro que pediu o elevador nesse andar e o elevador tiver que parar porque têm espaço
    if(*lotacao<max_pessoas){
        while(aux!=NULL){
            if(aux->Fila.Frente->prox->item.andarPassageiro == *andar){
                check=1;
            }
            aux=aux->prox;
        }
    }
    
    //verifica se é o andar do andar destino mais perto
    while(j!=NULL && check2==0){
        if( (*andar - j->item.destinoPassageiro) == 0 ){
            check2=1;
        }else{
            j=j->prox;
        }
    }
    
    //verifica se o elevador precisa parar porque é o destino do passageiro com andar final mais próximo ou porque o elevador tem espaço e alguém desse andar pediu para entrar
    if(check==1 || check2==1){
        //esse while procura na lista do elevador os elementos que são daquele andar. Quando ele acha, o elemento é retirado da lista de andares.
        elAnterior=Lista->Primeiro;
        j=Lista->Primeiro->prox;
        while (j!=NULL) {
            if(j->item.destinoPassageiro == *andar){
                printf("\n\nSai passageiro com: momento %d, origem %d e destino %d\n Lotacao: %d\n Zepslon: %d\n Andar: %d\n Tempo de espera: %d\n Tempo de espera dentro do elevador: %d", j->item.momento, j->item.andarPassageiro, j->item.destinoPassageiro, *lotacao-1, *Zepslon+1,j->item.destinoPassageiro, j->item.tempoEspera, *Zepslon - j->item.momento_elevador );
                Apontador q;
                q=j;
                elAnterior->prox=j->prox;
                j=elAnterior->prox;
                free(q);
                *lotacao=*lotacao-1;
                aux1=1;
            }else{
                elAnterior=elAnterior->prox;
                j = j->prox;
            }
        }
        Lista->Ultimo=elAnterior;
    }
    
    if(aux1==1){
        return 1;
    }else{
        return 0;
    }
}

//verifica se tem alguem para entrar no elavador olhando a fila de espera de cada andar
int EntraElevador(int Zepslon, int andar, int lotacao, int max_pessoas, TipoListaAndares *Andar, TipoLista *Lista){
    int aux1=0, check=0;
    Apontador2 aux, elAnterior;
    aux=Andar->Primeiro->prox;
    elAnterior=Andar->Primeiro;
    //checa se tem alguma pessoa fora do elevador que pediu para entrar e o elevador tem espaço. Nessa situação o elevador é obrigado a parar parar para a pessoa entrar.
    if(lotacao<max_pessoas){
        while(aux!=NULL && check==0){
            if(aux->Fila.Frente->prox->item.andarPassageiro == andar){
                check=1;
            }else{
                elAnterior=elAnterior->prox;
                aux=aux->prox;
            }
        }
    }
    
    //o while vai rodar até o elevador encher ou não haverem mais pessoas para entrar no elevador
    while(lotacao<max_pessoas && check==1 && aux->Fila.Frente!=aux->Fila.Tras){
        printf("\n\nEntra passageiro com: momento %d, origem %d e destino %d Tempo de espera: %d\n Andar: %d\n Lotacao: %d\n Zepslon: %d", aux->Fila.Frente->prox->item.momento, aux->Fila.Frente->prox->item.andarPassageiro, aux->Fila.Frente->prox->item.destinoPassageiro, Zepslon - aux->Fila.Frente->prox->item.momento,andar,lotacao+1,Zepslon+1);
        
        aux->Fila.Frente->prox->item.tempoEspera = Zepslon+1 - aux->Fila.Frente->prox->item.momento;
        aux->Fila.Frente->prox->item.momento_elevador=Zepslon;
        Insere(aux->Fila.Frente->prox->item,Lista);
        Desenfileira(&aux->Fila);
        
        lotacao++;
        aux1=1;
    }
    
    //esse if serve para apagar na lista de Andares o andar que ficou vazio
    if(aux1==1 && aux->Fila.Frente==aux->Fila.Tras){
        if(aux->prox!=NULL){
            Apontador2 q;
            q=aux;
            elAnterior->prox=aux->prox;
            aux=elAnterior->prox;
            free(q);
        }else{
            Apontador2 q;
            q=aux;
            elAnterior->prox=aux->prox;
            aux=elAnterior->prox;
            free(q);
            Andar->Ultimo=elAnterior;
        }
    }
    
    if(aux1==1){
        return lotacao;
    }else{
        return 0;
    }
    
}

//decide em que sentido o elevador vai ir
int SentidoFCFS(int andar, TipoLista *Lista, TipoListaAndares *Andar, int max_andares, int contador){
    int aux1=0, menor=contador, menorAndar;
    Apontador2 aux;
    
    //verifica se tem alguém no elevador. Se sim, o programa dará preferência para o destiono do primeiro passageiro que solicitou ir para um destino.
    if (Lista->Primeiro==Lista->Ultimo){
        
        aux=Andar->Primeiro->prox;
        
        //esse while procura nas filas dos andares com filas a pessoa que acionou o botão primeiro
        while(aux!=NULL){
            if(aux->Fila.Frente->prox->item.momento <= menor){
                menor = aux->Fila.Frente->prox->item.momento;
                menorAndar = aux->Fila.Frente->prox->item.andarPassageiro;
                aux1=1;
            }
            aux=aux->prox;
        }
        
        if(aux1==0){
            printf("\n\nSEM REQUISAO: Elevador não desce nem sobe");
            return 0;
        }else{
            
            if(andar-menorAndar<=0){
                andar++;
                printf("\n\nElevador sobe sentido-requisitado de %d para %d", andar-1, andar);
            }else{
                andar--;
                printf("\n\nElevador desce sentido-requisitado de %d para %d", andar+1, andar);
            }
        }
    }else{
        if(andar-Lista->Primeiro->prox->item.destinoPassageiro<0){
            andar++;
            printf("\n\nElevador sobe sentido-passageiro de %d para %d", andar-1, andar);
        }else{
            andar--;
            printf("\n\nElevador desce sentido-passageiro de %d para %d", andar+1, andar);
        }
    }
    return andar;
}

//decide em que sentido o elevador vai ir
int SentidoSJF(int andar, TipoLista *Lista, TipoListaAndares *Andar, int max_andares, int contador){
    int aux1=0, menor=2*max_andares;
    
    //verifica se tem alguém no elevador. Se sim, o programa dará preferência para o destiono do primeiro passageiro que solicitou ir para um destino.
    if (Lista->Primeiro==Lista->Ultimo){
        Apontador2 aux;
        aux=Andar->Primeiro->prox;
        
        //esse while procura nas filas dos andares com filas a pessoa mais perto vendo o valor absoluto da diferença do andar com o andar do passageiro, ou seja, vendo a distancia entre eles
        while(aux!=NULL){
            if( abs(andar - aux->Fila.Frente->prox->item.andarPassageiro) <= abs(andar - menor) ){
                menor = aux->Fila.Frente->prox->item.andarPassageiro;
                aux1=1;
            }
            aux=aux->prox;
        }
        
        if(aux1==0){
            printf("\n\nSEM REQUISAO: Elevador não desce nem sobe");
            return 0;
        }else{
            
            if(andar-menor<=0){
                andar++;
                printf("\n\nElevador sobe sentido-requisitado de %d para %d", andar-1, andar);
            }else{
                andar--;
                printf("\n\nElevador desce sentido-requisitado de %d para %d", andar+1, andar);
            }
        }
    }else{
        Apontador aux2;
        aux2=Lista->Primeiro->prox;
        //esse while vai olhar todos os elementos dentro da lista do elevador e dizer qual tem a menor distancia em relação ao andar atual
        while(aux2!=NULL){
            if( abs(andar - aux2->item.destinoPassageiro) <= abs(andar - menor) ){
                menor = aux2->item.destinoPassageiro;
            }
            aux2=aux2->prox;
        }
        
        if(andar-menor<0){
            andar++;
            printf("\n\nElevador sobe sentido-passageiro de %d para %d", andar-1, andar);
        }else{
            andar--;
            printf("\n\nElevador desce sentido-passageiro de %d para %d", andar+1, andar);
        }
    }
    return andar;
}
