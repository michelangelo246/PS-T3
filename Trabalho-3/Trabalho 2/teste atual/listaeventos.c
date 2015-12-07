#include "listaeventos.h"

    
ListaEventos Cria_ListaEventos(void)
{
    ListaEventos header = malloc(sizeof(struct lista_eventos));
    header->first = header->last = NULL;
    header->quant_elementos = 0;
    return header;
}

void Limpa_ListaEventos(ListaEventos header)
{
    while(!ListaEventos_Vazia(header))
    {
        Evento e =  Remove_Inicio_ListaEventos(header);
        Destroi_Evento(e);
    }
}

void Destroi_ListaEventos(ListaEventos header)
{
    Limpa_ListaEventos(header);
    free(header);
}

int ListaEventos_Vazia(ListaEventos header)
{
    return !(header->quant_elementos);
}

int Insere_ListaEventos_Vazia(ListaEventos header, Evento e)
{
    if(ListaEventos_Vazia(header))
    {
        NodoEventos* novo = malloc(sizeof(NodoEventos));
        novo->e = e;
        novo->pnext = novo->pprev = NULL;
        header->last = header->first = header->current = novo;// quando a lista estiver vazia, é necessário que o current seja null de novo;
        header->quant_elementos++;
        return 1;
    }
    else
        return 0;
}


int Insere_Inicio_ListaEventos(ListaEventos header,Evento e)// retorno indica se a função teve sucesso.
{
    if(!Insere_ListaEventos_Vazia(header,e))// se não entrar nessa condicional, é porque já foi inserido.
    {
        NodoEventos* novo =  malloc(sizeof(NodoEventos));
        if(!novo)
            return 1;
        novo->e = e;
        novo->pnext = header->first;
        novo->pprev = NULL;
        header->first->pprev = novo;
        header->first = novo;
        header->quant_elementos++;
    }
    return 0;
}

int Insere_Final_ListaEventos(ListaEventos header, Evento e)
{
    if(!Insere_ListaEventos_Vazia(header,e))
    {
        NodoEventos* novo = malloc(sizeof(NodoEventos));
        if(!novo)
            return 1;
        novo->e = e;
        novo->pnext = NULL;
        novo->pprev = header->last; 
        header->last->pnext = novo;
        header->last = novo;
        header->quant_elementos++;
    }
    return 0;
}

Evento Info_Corrente_ListaEventos(ListaEventos header)
{
    return header->current->e;
}

void Altera_Corrente_ListaEventos(ListaEventos header, Evento e)
{
    header->current->e = e;
}

void Aponta_Inicio_ListaEventos(ListaEventos header)
{
    header->current = header->first;
}

void Aponta_Final_ListaEventos(ListaEventos header)
{
    header->current = header->last;
}


int Insere_Corrente_ListaEventos(ListaEventos header,Evento e)
{
    if(!Insere_ListaEventos_Vazia(header,e))
    {
        NodoEventos* novo = malloc(sizeof(NodoEventos));
        if(!novo)
            return 1;
        novo->e = e;
        novo->pnext = header->current;
        novo->pprev = header->current->pprev;
        header->current->pprev->pnext = novo;
        header->current->pprev = novo;
        header->quant_elementos++;
    }
    return 0;
}

void Aponta_Proximo_ListaEventos(ListaEventos header)
{
    if(header->current != header->last)// caso contrário, apontaria para null
        header->current = header->current->pnext;
}

void Aponta_Anterior_ListaEventos(ListaEventos header)
{
    if(header->current != header->first)
        header->current = header->current->pprev;
}

int Quant_Elementos_ListaEventos(ListaEventos header)
{
    return header->quant_elementos;
}

Evento Remove_Inicio_ListaEventos(ListaEventos header)
{
    if(ListaEventos_Vazia(header))
    {
        printf("A lista já está vazia, não há nada para ser removido\n");
        exit(1);
    }
    NodoEventos* nodoaux = header->first;//salvar ref
    if(Quant_Elementos_ListaEventos(header) == 1)
    {
        header->first = header->last = header->current = NULL;
    }
    else
    {
        header->first = header->first->pnext;
        printf("%d\n",Quant_Elementos_ListaEventos(header) );
        header->first->pprev = NULL;
    }
    Evento eaux = nodoaux->e;
    free(nodoaux);
    header->quant_elementos--;

    return eaux;
}

Evento Remove_Final_ListaEventos(ListaEventos header)
{    if(ListaEventos_Vazia(header))
    {
        printf("A lista já está vazia, não há nada para ser removido\n");
        exit(1);
    }
    NodoEventos* nodoaux = header->last;//salvar ref
    if(Quant_Elementos_ListaEventos(header) == 1)
    {
        header->first = header->last = header->current = NULL;
    }
    else
    {
        header->last = header->last->pprev;
        header->last->pnext = NULL;
    }
    Evento eaux = nodoaux->e;
    free(nodoaux);
    header->quant_elementos--;
    return eaux;
}

Evento Remove_Corrente_ListaEventos(ListaEventos header)
{
    if(ListaEventos_Vazia(header))
    {
       printf("A lista já está vazia, não há nada para ser removido\n");
       exit(1);
    }
    NodoEventos* nodoaux = header->current;
    if(Quant_Elementos_ListaEventos(header) == 1)
    {
        header->first = header->last = header->current = NULL;
    }
    else
    {
        header->current->pnext->pprev = header->current->pprev;
        header->current->pprev->pnext = header->current->pnext;
        header->current = header->current->pnext;
    }
    Evento eaux = nodoaux->e;
    free(nodoaux);
    header->quant_elementos--;
    return eaux;
}
