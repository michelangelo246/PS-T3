
/******************************************************************************
                         Interface do  TRANTE_AUXILIAR

        Disponibiliza aos modulos de leitura e de tratamento as funcoes para 
    manipular as listas de palestrantes e de disponibilidades

*******************************************************************************/

#ifndef TRANTE_AUXILIAR

#define TRANTE_AUXILIAR


#include <stdio.h>
#include <stdlib.h>




/* Estruturas do componente palestrante */


typedef struct _disponibilidade{
    /* 
    tipo de dado: disponibilidade
    Estrutura (tipo de dado) para disponibilidade de palestrante, contem os campos:
        data (inteiro de 1 a 366, representando o dia do ano)
        hora_inicio (inteiro contendo a quantidade de minutos desde 00:00 ate a hora de inicio da disponibilidade)
        hora_fim (inteiro contendo a quantidade de minutos desde 00:00 ate a hora de fim da disponibilidade) */

    int data;
    int hora_inicio;
    int hora_fim;
    
    struct _disponibilidade *pnext;
    struct _disponibilidade *pprev;

} disponibilidade;


typedef struct lista_disponibilidade{
    
    /*
    tipo de dado: DISP_cabecalho
    cabecalho para lista de disponibilidade de um palestrante, contem os campos:
        first (ponteiro para o inicio da lista de disponibilidade)
        current (ponteiro para a disponibilidade corrente (utilizado para percorrimento da lista))
        last (ponteiro para o fim da lista de disponibilidade) */

    struct _disponibilidade *first;
    struct _disponibilidade *current;
    struct _disponibilidade *last;    

    int qtde_disponibilidade;

} DISP_cabecalho;


typedef struct _palestrante{
/*
  tipo de dado: palestrante
  Estrutura (tipo de dado) para palestrante, contem os campos:
        nome_pessoa (nome do palestrante)
        disp_bruta (disponibilidade obtida direto do arquivo de palestrantes (antes de ser tratada)))
        lista_disp (cabecalho para lista de disponibilidade do palestrante) */

    char *nome_pessoa;
    char *disp_bruta;

    struct lista_disponibilidade *lista_disp;

    struct _palestrante *pnext;
    struct _palestrante *pprev;

} palestrante;


typedef struct lista_palestrantes{
    
  /* 
  tipo de dado: TRANTE_cabecalho
  Cabecalho para lista de palestrantes, contem os campos:
        first (ponteiro para o inicio da lista de palestrantes)
        current (ponteiro para o palestrante corrente (utilizado para percorrimento da lista))
        last (ponteiro para o fim da lista de palestrantes) */


    struct _palestrante *first;
    struct _palestrante *current;
    struct _palestrante *last;

    int qtde_palestrante;

} TRANTE_cabecalho;






/* Funções para lista de palestrantes */

TRANTE_cabecalho *Cria_ListaPalestrantes( void );
/* Funcao Cria_ListaPalestrantes. 
    Entrada: nenhuma

    Saida: ponteiro cabecalho para lista de palestrantes
    
    Descricao: Essa funcao aloca memoria para uma lista inicialmente vazia, e retorna um ponteiro para o cabecalho,
    que é uma estrutura contendo 3 ponteiros (inicio, corrente e fim) para  a lista.

*/


int ListaPalestrantes_Vazia( TRANTE_cabecalho *header );
/* Funcao ListaPalestrantes_Vazia. 
    Entrada: ponteiro cabecalho para lista de palestrantes

    Saida: inteiro 1 ou 0. 1 significa que a lista está vazia, e 0 significa que a lista nao está vazia.
    Descricao: Essa funcao verifica se existe elemento na lista de palestrantes.

*/


void Insere_Final_ListaPalestrantes( TRANTE_cabecalho **header_pointer, palestrante *point_pessoa );
/* Funcao Insere_Final_ListaPalestrantes. 
    Entrada: ponteiro cabecalho para lista de palestrantes e um ponteiro para nova estrutura palestrante criada

    Saida: Nenhuma
    Descricao: Essa funcao utiliza a referencia para o fim da lista de palestrantes, 
    acessivel pelo ponteiro cabecalho recebido (parametro 1), 
    e insere no final da lista o novo palestrante cuja referencia foi recebida (parametro 2)

*/

int Aponta_Proximo_ListaPalestrantes( TRANTE_cabecalho **header_pointer );
/* Funcao Aponta_Proximo_ListaPalestrantes. 
    Entrada: ponteiro cabecalho para lista de palestrantes

    Saida: inteiro (para verificar se a operacao foi realizada com sucesso)
    Descricao: Essa funcao altera o ponteiro corrente do cabecalho recebido (parametro),
    para que ele passe a apontar para o proximo palestrante da lista.
    Caso a lista já esteja vazia, ou o ponteiro já esteja no final da lista, 
    então nenhuma ação é realizada, e o valor de retorno indica isso.

*/

int Aponta_Anterior_ListaPalestrantes( TRANTE_cabecalho **header_pointer );
/* Funcao Aponta_Anterior_ListaPalestrantes. 
    Entrada: ponteiro cabecalho para lista de palestrantes

    Saida: inteiro (para verificar se a operacao foi realizada com sucesso)
    Descricao: Essa funcao altera o ponteiro corrente do cabecalho recebido (parametro),
    para que ele passe a apontar para o palestrante anterior da lista.
    Caso a lista já esteja vazia, ou o ponteiro já esteja no inicio da lista, 
    então nenhuma ação é realizada, e o valor de retorno indica isso.

*/


int Aponta_Inicio_ListaPalestrantes( TRANTE_cabecalho **header_pointer );
/* Funcao Aponta_Inicio_ListaPalestrantes. 
    Entrada: ponteiro cabecalho para lista de palestrantes

    Saida: inteiro (para verificar se a operacao foi realizada com sucesso)
    Descricao: Essa funcao altera o ponteiro corrente do cabecalho recebido (parametro),
    para que ele passe a apontar para o inicio da lista de palestrante.
    Caso a lista esteja vazia, então nenhuma ação é realizada, 
    e o valor de retorno indica isso.

*/

int Conta_Pessoas_ListaPalestrantes( TRANTE_cabecalho *header );
/* Funcao Conta_Pessoas_ListaPalestrantes. 
    Entrada: ponteiro cabecalho para lista de palestrantes

    Saida: inteiro (quantidade de palestrantes presentes na lista).

*/




/* Funções para lista de DISPONIBILIDADES */



DISP_cabecalho *Cria_ListaDisponibilidades( void );
/* Funcao Cria_ListaDisponibilidades. 
    Entrada: nenhuma

    Saida: ponteiro cabecalho para lista de disponibilidades 
    
    Descricao: Essa funcao aloca memoria para uma lista inicialmente vazia, e retorna um ponteiro para o cabecalho,
    que é uma estrutura contendo 3 ponteiros (inicio, corrente e fim) para  a lista.

*/
    


int ListaDisponibilidades_Vazia( DISP_cabecalho *header );
/* Funcao ListaDisponibilidades_Vazia. 
    Entrada: ponteiro cabecalho para lista de disponibilidades (de um palestrante)

    Saida: inteiro 1 ou 0. 1 significa que a lista está vazia, e 0 significa que a lista nao está vazia.
    Descricao: Essa funcao verifica se existe elemento na lista de disponibilidades de um palestrante.

*/
    

void Insere_Final_ListaDisponibilidades( DISP_cabecalho **header_pointer, disponibilidade *point_disp );
/* Funcao ListaDisponibilidades_Vazia. 
    Entrada: ponteiro cabecalho para lista de disponibilidades (de um palestrante)

    Saida: inteiro 1 ou 0. 1 significa que a lista está vazia, e 0 significa que a lista nao está vazia.
    Descricao: Essa funcao verifica se existe elemento na lista de disponibilidades de um palestrante.

*/



int Aponta_Proximo_ListaDisponibilidades( DISP_cabecalho **header_pointer );

/* Funcao Aponta_Proximo_ListaDisponibilidades. 
    Entrada: ponteiro cabecalho para lista de disponibilidades de um palestrante

    Saida: inteiro (para verificar se a operacao foi realizada com sucesso)
    Descricao: Essa funcao altera o ponteiro corrente do cabecalho recebido (parametro),
    para que ele passe a apontar para a proxima disponibilidade do palestrante.
    Caso a lista já esteja vazia, ou o ponteiro já esteja no final da lista, 
    então nenhuma ação é realizada, e o valor de retorno indica isso.

*/


int Aponta_Anterior_ListaDisponibilidades( DISP_cabecalho **header_pointer );
/* Funcao Aponta_Anterior_ListaDisponibilidades. 
    Entrada: ponteiro cabecalho para lista de disponibilidades de um palestrante

    Saida: inteiro (para verificar se a operacao foi realizada com sucesso)
    Descricao: Essa funcao altera o ponteiro corrente do cabecalho recebido (parametro),
    para que ele passe a apontar para a disponibilidade anterior do palestrante.
    Caso a lista já esteja vazia, ou o ponteiro já esteja no inicio da lista, 
    então nenhuma ação é realizada, e o valor de retorno indica isso.

*/

int Aponta_Inicio_ListaDisponibilidades( DISP_cabecalho **header_pointer );
/* Funcao Aponta_Inicio_ListaDisponibilidades. 
    Entrada: ponteiro cabecalho para lista de disponibilidades de um palestrante

    Saida: inteiro (para verificar se a operacao foi realizada com sucesso)
    Descricao: Essa funcao altera o ponteiro corrente do cabecalho recebido (parametro),
    para que ele passe a apontar para o inicio da lista de disponibilidades do palestrante.
    Caso a lista esteja vazia, então nenhuma ação é realizada, 
    e o valor de retorno indica isso.

*/



int Conta_Disps_ListaDisponibilidades( DISP_cabecalho *header );
/* Funcao Conta_Disps_ListaDisponibilidades. 
    Entrada: ponteiro cabecalho para lista de disponibilidades de um palestrante

    Saida: inteiro (quantidade de disponibilidades do palestrante presentes na lista).

*/



#endif

