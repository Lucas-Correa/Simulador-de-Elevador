//
//
//
//  Created by Lucas Cavalcante Corrêa on 04/05/2018.
//  Copyright © 2018 Lucas Cavalcante Corrêa. All rights reserved.
//


#include "Estrategias.h"

int main(int argc, char **argv) {
    
    char *ambiente = NULL;
    char *Leventos = NULL;
    char *estrategia = NULL;
    int c;
    
    // serve para pegar as opções do usuário
    while ((c = getopt (argc, argv, "i:e:s:")) != -1)
        switch (c)
    {
        case 'i':
            ambiente = optarg;
            break;
        case 'e':
            Leventos = optarg;
            break;
        case 's':
            estrategia = optarg;
            break;
            
        default:
            abort ();
    }
    
    
    FILE *amb_elevador, *eventos;
    
    //abre os arquivos dado pelo usuário. Se algum não exixtir, da uma mensagem de erro
    if((amb_elevador=fopen(ambiente, "r"))==NULL){
        printf("Arquivo não existe!\n");
        return 0;
    };
    if((eventos=fopen(Leventos,"r"))==NULL){
        printf("Arquivo não existe!\n");
        return 0;
    };
    
    //pega os valores iniciais de tempo das funções gettimeofday e getrusage
    getrusage(RUSAGE_SELF,&usage);
    SistemaIncial=usage.ru_stime;
    UsuarioInicial=usage.ru_utime;
    
    gettimeofday(&TempoIncial, NULL);
    
    //condição que leva em conta a escolha do usuário de que estratégia utilizar
    if(strcmp(estrategia, "fcfs")==0){
       FCFS(amb_elevador, eventos);
        getrusage(RUSAGE_SELF,&usage);
        SistemaFinal=usage.ru_stime;
        UsuarioFinal=usage.ru_utime;
        printf("\nTempo de Usuário: %ldms\n",(UsuarioFinal.tv_usec + UsuarioFinal.tv_sec * 1000000) -(UsuarioInicial.tv_usec + UsuarioInicial.tv_sec * 1000000));
        printf("Tempo de Sistema: %ldms\n", (SistemaFinal.tv_usec + SistemaFinal.tv_sec * 1000000) -(SistemaIncial.tv_usec + SistemaIncial.tv_sec * 1000000));
        
        gettimeofday(&TempoFinal, NULL);
        printf("Tempo do relógio: %ldms\n", (TempoFinal.tv_usec + TempoFinal.tv_sec * 1000000) -(TempoIncial.tv_usec + TempoIncial.tv_sec * 1000000));
        
        printf("Uso da memória = %ld\n\n",usage.ru_maxrss);

    }else{
        SJF(amb_elevador, eventos);
        getrusage(RUSAGE_SELF,&usage);
        SistemaFinal=usage.ru_stime;
        UsuarioFinal=usage.ru_utime;
        printf("\nTempo de Usuário: %ldms\n",(UsuarioFinal.tv_usec + UsuarioFinal.tv_sec * 1000000) -(UsuarioInicial.tv_usec + UsuarioInicial.tv_sec * 1000000));
        printf("Tempo de Sistema: %ldms\n", (SistemaFinal.tv_usec + SistemaFinal.tv_sec * 1000000) -(SistemaIncial.tv_usec + SistemaIncial.tv_sec * 1000000));
        
        gettimeofday(&TempoFinal, NULL);
        printf("Tempo do relógio: %ldms\n", (TempoFinal.tv_usec + TempoFinal.tv_sec * 1000000) -(TempoIncial.tv_usec + TempoIncial.tv_sec * 1000000));
        
        printf("Uso da memória = %ld\n\n",usage.ru_maxrss);
    }
    return 0;
}
