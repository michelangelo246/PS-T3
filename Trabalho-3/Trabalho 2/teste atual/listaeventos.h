#ifndef LISTA_EVENTOS
#define LISTA_EVENTOS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "evento.h"

typedef struct nodo_eventos
{
    Evento e;
    struct nodo_eventos *pprev;
    struct nodo_eventos *pnext;
    
}NodoEventos;

struct lista_eventos
{
    int quant_elementos;
    struct nodo_eventos *first;
    struct nodo_eventos *current;
    struct nodo_eventos *last;
    
};

typedef struct lista_eventos* ListaEventos;



ListaEventos Cria_ListaEventos(void); // const
void Destroi_ListaEventos(ListaEventos header);

Evento Info_Corrente_ListaEventos(ListaEventos header);
void Altera_Corrente_ListaEventos(ListaEventos header, Evento e);

void Limpa_ListaEventos(ListaEventos header);
int ListaEventos_Vazia(ListaEventos header);
int Insere_ListaEventos_Vazia(ListaEventos header, Evento e);
int Insere_Inicio_ListaEventos(ListaEventos header,Evento e);
int Insere_Final_ListaEventos(ListaEventos header, Evento e);
int Insere_Corrente_ListaEventos(ListaEventos header,Evento e);
void Aponta_Proximo_ListaEventos(ListaEventos header);
void Aponta_Anterior_ListaEventos(ListaEventos header);
void Aponta_Inicio_ListaEventos(ListaEventos header);
void Aponta_Final_ListaEventos(ListaEventos header);
int Quant_Elementos_ListaEventos(ListaEventos header);
Evento Remove_Inicio_ListaEventos(ListaEventos header);
Evento Remove_Final_ListaEventos(ListaEventos header);
Evento Remove_Corrente_ListaEventos(ListaEventos header);




#endif
//LISTA_EventoS