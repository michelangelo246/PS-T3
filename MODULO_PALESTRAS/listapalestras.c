#include "listapalestras.h"
/*
ListaPalestras Le_palestras2()
{
    ListaPalestras p1;
    NodoPalestras *n1_palestras,*n2_palestras;
    Palestra *n1_palestras_p,*n2_palestras_p;

    p1=(ListaPalestras )malloc(sizeof(ListaPalestras));
    n1_palestras = (NodoPalestras *)malloc(sizeof(NodoPalestras));
    n2_palestras = (NodoPalestras *)malloc(sizeof(NodoPalestras));
    n1_palestras_p = (Palestra *)malloc(sizeof(Palestra));
    n2_palestras_p = (Palestra *)malloc(sizeof(Palestra));

    n1_palestras->pprev = NULL;
    n1_palestras->pnext = n2_palestras;
    n1_palestras->p = n1_palestras_p;

    n2_palestras->pnext = NULL;
    n2_palestras->pprev = n1_palestras;
    n2_palestras->p = n2_palestras_p;

    strcpy(n1_palestras_p->nome_palestra,"Palestra1");
    strcpy(n2_palestras_p->nome_palestra,"Palestra2");
    strcpy(n1_palestras_p->responsavel,"Palestrante1");
    strcpy(n2_palestras_p->responsavel,"Palestrante2");


    n1_palestras_p->duracao_tratada = 60;
    n2_palestras_p->duracao_tratada = 60;

    p1->first = p1->current = n1_palestras;
    p1->last = n2_palestras;

    return p1;
}
*/
    
ListaPalestras Cria_ListaPalestras(void)
{
    ListaPalestras header = malloc(sizeof(struct lista_palestras));
    header->first = header->last = NULL;
    header->quant_elementos = 0;
    return header;
}

void Limpa_ListaPalestras(ListaPalestras header)
{
    while(!ListaPalestras_Vazia(header))
        Remove_Inicio_ListaPalestras(header);
}

void Destroi_ListaPalestras(ListaPalestras header)
{
    Limpa_ListaPalestras(header);
    free(header);
}

int ListaPalestras_Vazia(ListaPalestras header)
{
    return !(header->quant_elementos);
}

int Insere_ListaPalestras_Vazia(ListaPalestras header, Palestra p)
{
    if(ListaPalestras_Vazia(header))
    {
        NodoPalestras* novo = malloc(sizeof(NodoPalestras));
        novo->p = p;
        novo->pnext = novo->pprev = NULL;
        header->last = header->first = header->current = novo;// quando a lista estiver vazia, é necessário que o current seja null de novo;
        header->quant_elementos++;
        return 1;
    }
    else
        return 0;
}


int Insere_Inicio_ListaPalestras(ListaPalestras header,Palestra p)// retorno indica se a função teve sucesso.
{
    if(!Insere_ListaPalestras_Vazia(header,p))// se não entrar nessa condicional, é porque já foi inserido.
    {
        NodoPalestras* novo =  malloc(sizeof(NodoPalestras));
        if(!novo)
            return 1;
        novo->p = p;
        novo->pnext = header->first;
        novo->pprev = NULL;
        header->first->pprev = novo;
        header->first = novo;
        header->quant_elementos++;
    }
    return 0;
}

int Insere_Final_ListaPalestras(ListaPalestras header, Palestra p)
{
    if(!Insere_ListaPalestras_Vazia(header,p))
    {
        NodoPalestras* novo = malloc(sizeof(NodoPalestras));
        if(!novo)
            return 1;
        novo->p = p;
        novo->pnext = NULL;
        novo->pprev = header->last;
        header->last->pnext = novo;
        header->last = novo;
        header->quant_elementos++;
    }
    return 0;
}

Palestra Info_Corrente_ListaPalestras(ListaPalestras header)
{
    return header->current->p;
}

void Altera_Corrente_ListaPalestras(ListaPalestras header, Palestra p)
{
    header->current->p = p;
}

void Aponta_Inicio_ListaPalestras(ListaPalestras header)
{
    header->current = header->first;
}

void Aponta_Final_ListaPalestras(ListaPalestras header)
{
    header->current = header->last;
}


int Insere_Corrente_ListaPalestras(ListaPalestras header,Palestra p)
{
    if(!Insere_ListaPalestras_Vazia(header,p))
    {
        NodoPalestras* novo = malloc(sizeof(NodoPalestras));
        if(!novo)
            return 1;
        novo->p = p;
        novo->pnext = header->current;
        novo->pprev = header->current->pprev;
        header->current->pprev->pnext = novo;
        header->current->pprev = novo;
        header->quant_elementos++;
    }
    return 0;
}

void Aponta_Proximo_ListaPalestras(ListaPalestras header)
{
    if(header->current != header->last)// caso contrário, apontaria para null
        header->current = header->current->pnext;
}

void Aponta_Anterior_ListaPalestras(ListaPalestras header)
{
    if(header->current != header->first)
        header->current = header->current->pprev;
}

int Quant_Elementos_ListaPalestras(ListaPalestras header)
{
    return header->quant_elementos;
}

Palestra Remove_Inicio_ListaPalestras(ListaPalestras header)
{
    if(ListaPalestras_Vazia(header))
    {
        printf("A lista já está vazia, não há nada para ser removido\n");
        exit(1);
    }
    NodoPalestras* nodoaux = header->first;//salvar ref
    if(Quant_Elementos_ListaPalestras(header) == 1)
    {
        header->first = header->last = header->current = NULL;
    }
    else
    {
        header->first = header->first->pnext;
        header->first->pprev = NULL;
    }
    Palestra paux = nodoaux->p;
    free(nodoaux);
    header->quant_elementos--;

    return paux;
}

Palestra Remove_Final_ListaPalestras(ListaPalestras header)
{    if(ListaPalestras_Vazia(header))
    {
        printf("A lista já está vazia, não há nada para ser removido\n");
        exit(1);
    }
    NodoPalestras* nodoaux = header->last;//salvar ref
    if(Quant_Elementos_ListaPalestras(header) == 1)
    {
        header->first = header->last = header->current = NULL;
    }
    else
    {
        header->last = header->last->pprev;
        header->last->pnext = NULL;
    }
    Palestra paux = nodoaux->p;
    free(nodoaux);
    header->quant_elementos--;
    return paux;
}

Palestra Remove_Corrente_ListaPalestras(ListaPalestras header)
{
    if(ListaPalestras_Vazia(header))
    {
       printf("A lista já está vazia, não há nada para ser removido\n");
       exit(1);
    }
    NodoPalestras* nodoaux = header->current;
    if(Quant_Elementos_ListaPalestras(header) == 1)
    {
        header->first = header->last = header->current = NULL;
    }
    else
    {
        header->current->pnext->pprev = header->current->pprev;
        header->current->pprev->pnext = header->current->pnext;
        header->current = header->current->pnext;
    }
    Palestra paux = nodoaux->p;
    free(nodoaux);
    header->quant_elementos--;
    return paux;
}
