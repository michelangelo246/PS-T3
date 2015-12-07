#ifndef PALESTRA_H
#define PALESTRA_H

#define MAX_NOME_PALESTRA 200
#define MAX_NOME_RESPONSAVEL 50
#define MAX_TEMA 50
#define MAX_LOCAL 50
#define MAX_DUR_BRUTA 50
#include <stdlib.h>
struct palestra
{
    char *nome_palestra; 
    char *responsavel;
    char *tema;
    char *local;
    char *duracao_bruta;
    int duracao_tratada; /* duracao em minutos (quantidade total de minutos que dura a palestra */
    int t1; /*Campo usado no calendario*/
    int t2;
    
};

typedef struct palestra* Palestra;

Palestra Cria_Palestra();
void Destroi_Palestra(Palestra p);

#endif
//PALESTRA_H