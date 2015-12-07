#ifndef LISTA_PALESTRAS
#define LISTA_PALESTRAS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "palestra.h"
typedef struct nodo_palestras
{
    Palestra p;
    struct nodo_palestras *pprev;
    struct nodo_palestras *pnext;
    
}NodoPalestras;

struct lista_palestras
{
    int quant_elementos;
    struct nodo_palestras *first;
    struct nodo_palestras *current;
    struct nodo_palestras *last;
    
};
typedef struct lista_palestras* ListaPalestras;



ListaPalestras Cria_ListaPalestras(void); // const
void Destroi_ListaPalestras(ListaPalestras header);

Palestra Info_Corrente_ListaPalestras(ListaPalestras header);
void Altera_Corrente_ListaPalestras(ListaPalestras header, Palestra p);

void Limpa_ListaPalestras(ListaPalestras header);
int ListaPalestras_Vazia(ListaPalestras header);
int Insere_ListaPalestras_Vazia(ListaPalestras header, Palestra p);
int Insere_Inicio_ListaPalestras(ListaPalestras header,Palestra p);
int Insere_Final_ListaPalestras(ListaPalestras header, Palestra p);
int Insere_Corrente_ListaPalestras(ListaPalestras header,Palestra p);
void Aponta_Proximo_ListaPalestras(ListaPalestras header);
void Aponta_Anterior_ListaPalestras(ListaPalestras header);
void Aponta_Inicio_ListaPalestras(ListaPalestras header);
void Aponta_Final_ListaPalestras(ListaPalestras header);
int Quant_Elementos_ListaPalestras(ListaPalestras header);
Palestra Remove_Inicio_ListaPalestras(ListaPalestras header);
Palestra Remove_Final_ListaPalestras(ListaPalestras header);
Palestra Remove_Corrente_ListaPalestras(ListaPalestras header);
//ListaPalestras *Le_palestras2();//wtf - funcao usada para teste da persistencia enquanto o modulo tratadadaos estiver quebrado.




#endif
//LISTA_PALESTRAS