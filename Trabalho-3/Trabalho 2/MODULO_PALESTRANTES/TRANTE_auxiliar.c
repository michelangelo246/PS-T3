/******************************************************************************
                         Módulo TRANTE_AUXILIAR

        Esse modulo implementa funcoes para manipular
    as listas de palestrantes e de disponibilidades

*******************************************************************************/


#include <stdio.h>
#include <stdlib.h>


#include "TRANTE_auxiliar.h"


/*  funcoes para lista de palestrantes */


TRANTE_cabecalho *Cria_ListaPalestrantes( void ){


    TRANTE_cabecalho *header = NULL; 
    header = (TRANTE_cabecalho *)malloc( sizeof(TRANTE_cabecalho) );

    if(header == NULL){

        printf("\n\nNao foi possivel alocar memoria para lista de palestrante\n");

        exit(EXIT_FAILURE);
    }

    header->first = NULL;
    header->last = NULL;
    header->current = NULL;

    header->qtde_palestrante = 0;

    return header;
}



int ListaPalestrantes_Vazia( TRANTE_cabecalho *header ){

    if(header->qtde_palestrante > 0){
        return 0;
    }

    return 1;
}


void Insere_Final_ListaPalestrantes( TRANTE_cabecalho **header_pointer, palestrante *point_pessoa ){

    if( ListaPalestrantes_Vazia(*header_pointer) )
    {

        point_pessoa->pnext = NULL;
        point_pessoa->pprev = NULL;

        (*header_pointer)->first = point_pessoa; 
        (*header_pointer)->last =  point_pessoa;
        (*header_pointer)->current = point_pessoa;

        (*header_pointer)->qtde_palestrante++;
    }
    else
    {
        
        point_pessoa->pnext = NULL;
        point_pessoa->pprev = (*header_pointer)->last;
        
        ( (*header_pointer)->last )->pnext = point_pessoa;
        (*header_pointer)->last = point_pessoa;
        (*header_pointer)->qtde_palestrante++;

    }

    return;
}


int Aponta_Proximo_ListaPalestrantes( TRANTE_cabecalho **header_pointer ){

    if( (*header_pointer)->current != (*header_pointer)->last){
        (*header_pointer)->current = ( (*header_pointer)->current )->pnext;
        return 1;
    }

    return 0; 
    /* retorno nulo significa que nao existe proximo.
    Chegou no fim da lista */
}


int Aponta_Anterior_ListaPalestrantes( TRANTE_cabecalho **header_pointer ){

    if( (*header_pointer)->current != (*header_pointer)->first){
        (*header_pointer)->current = ((*header_pointer)->current)->pprev;
        return 1;
    }

    return 0;
    /* retorno nulo significa que nao existe anterior.
    Chegou no inicio da lista */
}




int Aponta_Inicio_ListaPalestrantes( TRANTE_cabecalho **header_pointer ){

    if( ListaPalestrantes_Vazia( (*header_pointer) ) ){
        return 0;
    /* retorno nulo significa que nao existe inicio.
    A lista estah vazia */
    }

    (*header_pointer)->current = (*header_pointer)->first;
    return 1;
}


int Conta_Pessoas_ListaPalestrantes( TRANTE_cabecalho *header ){

    return header->qtde_palestrante;
}




/* ================================    Funções para lista de disponibilidades    ======================================================*/




DISP_cabecalho *Cria_ListaDisponibilidades( void ){

    DISP_cabecalho *header = (DISP_cabecalho *)malloc( sizeof(DISP_cabecalho) );
    if(header == NULL){

        printf("\n\nNao foi possivel alocar memoria para lista de disponibilidades\n");

        exit(EXIT_FAILURE);
    }

    header->first = NULL;
    header->last = NULL;
    header->current = NULL;

    header->qtde_disponibilidade = 0;
    
    return header;
}



int ListaDisponibilidades_Vazia( DISP_cabecalho *header ){

    if(header->qtde_disponibilidade > 0){
        return 0;
    }

    return 1;
}


void Insere_Final_ListaDisponibilidades( DISP_cabecalho **header_pointer, disponibilidade *point_disp ){

    int erro = 0;

    if( header_pointer == NULL ){
        printf("\n\nErro!\nRecebido endereco nulo de lista de disponibilidades. \nLocal para inserir nova disponibilidade invalido! \n\n");
        erro = 1;
    }

    if( point_disp == NULL ){
        printf("\n\nErro!\nRecebido endereco nulo da nova disponibilidade\n\n");
        erro = 1;
    }

    if(erro == 1){
        return;
    }


    if( ListaDisponibilidades_Vazia(*header_pointer) )
    {

        point_disp->pnext = NULL;
        point_disp->pprev = NULL;

        (*header_pointer)->first = point_disp;
        (*header_pointer)->last = point_disp;
        (*header_pointer)->current = point_disp;

        (*header_pointer)->qtde_disponibilidade++;
    }
    else{
        
        point_disp->pnext = NULL;
        point_disp->pprev = (*header_pointer)->last;

        ((*header_pointer)->last)->pnext = point_disp;
        (*header_pointer)->last = point_disp;
        (*header_pointer)->qtde_disponibilidade++;

    }

    return;
}


int Aponta_Proximo_ListaDisponibilidades( DISP_cabecalho **header_pointer ){

    if( (*header_pointer)->current != (*header_pointer)->last){
        (*header_pointer)->current = ( (*header_pointer)->current)->pnext;
        return 1;
    }

    return 0; 
    /* retorno nulo significa que nao existe proximo.
    Chegou no fim da lista */
    
}


int Aponta_Anterior_ListaDisponibilidades( DISP_cabecalho **header_pointer ){

    if( (*header_pointer)->current != (*header_pointer)->first){
        (*header_pointer)->current = ( (*header_pointer)->current )->pprev;
        return 1;
    }

    return 0;
    /* retorno nulo significa que nao existe anterior.
    Chegou no inicio da lista */
}




int Aponta_Inicio_ListaDisponibilidades( DISP_cabecalho **header_pointer ){

    if( ListaDisponibilidades_Vazia( (*header_pointer) ) ){
        return 0;
    /* retorno nulo significa que nao existe inicio.
    A lista estah vazia */
    }

    (*header_pointer)->current = (*header_pointer)->first;
    return 1;
}


int Conta_Disps_ListaDisponibilidades( DISP_cabecalho *header ){

    return header->qtde_disponibilidade;

}












/*



int Insere_ListaPalestrantes_Vazia(TRANTE_cabecalho header, palestrante *point_pessoa)
{
    if( ListaPalestrantes_Vazia(header) )
    {
        header->last = header->first = header->current = point_pessoa;
        header->qtde_palestrante++;
        return 1;
    }
    else
        return 0;
}






int Insere_Inicio_ListaPalestrantes(TRANTE_cabecalho header,Palestrante *p)// retorno indica se a função teve sucesso.
{
    if(!Insere_ListaPalestrantes_Vazia(header,p))// se não entrar nessa condicional, é porque já foi inserido.
    {
        palestrante *novo =  malloc(sizeof(NodoPalestrantes));
        if(!novo)
            return 1;
        novo->p = p;
        novo->pnext = header->first;
        novo->pprev = NULL;
        header->first->pprev = novo;
        header->first = novo;
        header->qtde_palestrante++;
    }
    return 0;
}



void Aponta_Final_ListaPalestrantes(TRANTE_cabecalho header)
{
    header->current = header->last;
}



int Insere_Corrente_ListaPalestrantes(TRANTE_cabecalho header,Palestrante *p)
{
    if(!Insere_ListaPalestrantes_Vazia(header,p))
    {
        palestrante *novo = malloc(sizeof(NodoPalestrantes));
        if(!novo)
            return 1;
        novo->p = p;
        novo->pnext = header->current;
        novo->pprev = header->current->pprev;
        header->current->pprev->pnext = novo;
        header->current->pprev = novo;
        header->qtde_palestrante++;
    }
    return 0;
}



Palestrante* Info_Corrente_ListaPalestrantes(TRANTE_cabecalho header)
{
    return header->current->p;
}


void Altera_Corrente_ListaPalestrantes(TRANTE_cabecalho header, palestrante *point_pessoa)
{
    header->current->p = p;
}



Palestrante* Remove_Final_ListaPalestrantes(TRANTE_cabecalho header)
{
    if(ListaPalestrantes_Vazia(header))
    {
        printf("A lista já está vazia, não há nada para ser removido\n");
        exit(1);
    }
    NodoPalestrantes* nodoaux = header->last;//salvar ref
    if(Quant_Elementos_ListaPalestrantes(header) == 1)
    {
        header->first = header->last = header->current = NULL;
    }
    else
    {
        header->last = header->last->pprev;
        header->last->pnext = NULL;
    }
    Palestrante *paux = nodoaux->p;
    free(nodoaux);
    header->qtde_palestrante--;
    return paux;
}

Palestrante* Remove_Corrente_ListaPalestrantes(TRANTE_cabecalho header)
{
    if(ListaPalestrantes_Vazia(header))
    {
       printf("A lista já está vazia, não há nada para ser removido\n");
       exit(1);
    }
    NodoPalestrantes* nodoaux = header->current;
    if(Quant_Elementos_ListaPalestrantes(header) == 1)
    {
        header->first = NULL;
        header->last = NULL;
        header->current = NULL;
    }
    else
    {
        header->current->pnext->pprev = header->current->pprev;
        header->current->pprev->pnext = header->current->pnext;
        header->current = header->current->pnext;
    }
    Palestrante *paux = nodoaux->p;
    free(nodoaux);
    header->qtde_palestrante--;
    return paux;
}



void Destroi_ListaPalestrantes( TRANTE_cabecalho **header_pointer ){

    palestrante *aux;
    
    while( (*header_pointer)->qtde_palestrante > 1 ){

        aux = (*header_pointer)->first;
        
        (*header_pointer)->first = ((*header_pointer)->first)->pnext;
        ((*header_pointer)->first)->pprev = NULL;
                
        free(aux);
        
        (*header_pointer)->qtde_palestrante--;
    }

    free( (*header_pointer)->first );
    free( (*header_pointer) );

    return;
}





*/