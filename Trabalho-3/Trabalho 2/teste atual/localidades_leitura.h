/*********************************************************************
                Modulo de leitura de localidades

Esse modulo e responsavel por criar uma lista com as informacoes
das localidades ainda nao tratadas, prontos para ser enviadas ao
modulo localidades_tratamento.

    -------------------------------------------------------------
    Entrada: Arquivo de texto com as localidades.

    Saida: Lista com informacoes brutas das localidades.

Autor: Michelangelo.
**********************************************************************/

#ifndef LOCALIDADES_LEITURA_H
#define LOCALIDADES_LEITURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Estruturas do modulo */

typedef struct Tipo_Local
{
    char nome[50];
    char endereco[50];
    char disponibilidade_bruta[300];
    struct Tipo_Disponibilidade_Local *disponibilidade;
    struct Tipo_Local *prox;

}tipo_local;

typedef struct Tipo_Disponibilidade_Local
{
    char dia_semana[4];
    int dia;        /*em dia do ano*/
    int duracao;    /*em minutos*/
    int inicio;     /*em minutos*/
    int fim;        /*em minutos*/
    struct Tipo_Disponibilidade_Local *prox;

}tipo_disponibilidade_local;


/* Funcoes do modulo */

/*! \brief Descricao: retorna um ponteiro inicializado para o inicio da lista de localidades

    \param void

    \return ponteiro de local com campos iniciados
*/
tipo_local* Inicia_Ponteiro(void);

/*! \brief Descricao: baseado nas informacoes recebidas faz a leitura da linha do arquivo
que contem o nome do local passando a informacao para o respectivo campo do no sendo preenchido

    \param arq ptr para o arquivo de localidades
    \param p1 ptr para o no sendo preenchido na lista

    \return void
*/
void Le_Nome(FILE *arq, tipo_local **p1);

/*! \brief Descricao: baseado nas informacoes recebidas faz a leitura da linha do arquivo que contem
o endereco do local passando a informacao para o respectivo campo do no sendo preenchido

    \param arq ptr para o arquivo de localidades
    \param p1 ptr para o no sendo preenchido na lista

    \return void
*/
void Le_Endereco(FILE *arq, tipo_local **p1);

/*! \brief Descricao: baseado nas informacoes recebidas faz a leitura do arquivo que contem a
disponibilidade do local passando a informacao para o respectivo campo do no sendo preenchido

    \param arq ptr para o arquivo de localidades
    \param p1 ptr para o no sendo preenchido na lista
    \param sair ptr para o controlador do loop principal da funcao Le_Localidade

    \return void
*/
void Le_Disponibilidade_Bruta(FILE *arq, tipo_local **p1, int *sair);

/*! \brief Descricao: Cria uma lista com as informacoes das localidades ainda nao tratadas

    \param void

    \return ptr para o inicio da lista de localidades com informacoes brutas
*/
tipo_local* Le_Localidade(void);


#endif // LOCALIDADES_LEITURA_H
