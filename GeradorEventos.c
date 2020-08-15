//
//  GeradorEventos.c
//  Simulador de Elevador
//
//  Created by Lucas Cavalcante Corrêa on 04/05/2018.
//  Copyright © 2018 Lucas Cavalcante Corrêa. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int n, m, freq[9], i, max,a=1, b, c;
    FILE *fp, *fa;
    
    printf("Escreva o número de eventos que você deseja criar: \n");
    scanf("%d",&n);
    
    printf("Escreva o número de andares do seu prédio: \n");
    scanf("%d",&m);
    
    printf("Escreva a capacidade máxima de pessoas: \n");
    scanf("%d", &max);
    
    //esse for serve para criar um vetor para servir de probabilidade de um evento não ser chamado em determinado momento
    for(i=0;i<9;i++){
        if(i<6){
            freq[i]=0;
        }else{
            freq[i]=1;
        }
    }
    
    
    fp=fopen("Lista_Eventos.txt","w");
    
    srand(time(NULL));
    for(i=0;i<n;i++){
        a=a+freq[rand() % 9]+1;
        b=rand() % m;
        c=rand() % m;
        while(c==b){
            c=rand() % m;
        }
        fprintf(fp,"%d %d %d\n", a,b,c);
    }
    rewind(fp);
    fprintf(fp,"%d", 1);
    fclose(fp);
    
    fa=fopen("Ambiente_Elevador.txt","w");
    
    fprintf(fa,"%d %d", m, max);
    fclose(fa);
    
}
