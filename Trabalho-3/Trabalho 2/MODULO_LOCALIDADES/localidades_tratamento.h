/*********************************************************************
                Modulo de tratamento de localidades

Esse modulo e responsavel por criar uma lista com as informacoes
das localidades todas tratadas, organizadas e refinadas, assim como
de suas respectivas disponibilidades.

    -------------------------------------------------------------
    Entrada: Saida do modulo localidades_leitura, contendo uma lista
    com todos os locais e suas respectivas informacoes e disponibilidades
    todas em formato ainda bruto.

    Saida: Ponteiro para inicio de uma lista contendo todas as
    informacoes das localidades tratadas e organizadas.

Autor: Michelangelo.
**********************************************************************/

#ifndef LOCALIDADES_TRATAMENTO_H
#define LOCALIDADES_TRATAMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "localidades_leitura.h"


/* Estruturas do modulo */

typedef struct Tipo_Data_Info
{
    int dia; /*dd*/
    int mes; /*mm*/
    int ano; /*aaaa*/

}tipo_data_info;

typedef struct Tipo_Data_Atual
{
    int dia_atual;
    int mes_atual;
    int ano_atual;

}tipo_data_atual;


/* Funcoes do modulo */

/*! \brief Descricao: consome um caractere (' ' no caso.) do arquivo recebido

    \param arq ptr para um arquivo

    \return void
*/
void Pula_Espaco(FILE *arq);

/*! \brief Descricao: recebe um arquivo apontando para: um caractere antes de uma sequencia de numeros que
vao ser processados e retornados como um inteiro, encerra a leitura desses caracteres
identificados como numero quando encontra um caractere terminador:
'/',',',':','-','.',';' ou EOF

    \param arq ptr para um arquivo

    \return retorna conversao da string lida para um inteiro
*/
int pegaValor(FILE *arq);

/*! \brief Descricao: recebe um ano e verifica se esse e bissexto ou nao

    \param ano ano que se deseja verificar se e bissexto

    \return 1 caso o ano seja bissexto ou 0 caso contrario
*/
int Analisa_Bissexto(int ano);

/*! \brief Descricao: recebe um inteiro que representa o mes [1-12] e retorna a quantidade de dias
que aquele mes tem, tratando casos de ano bissexto

    \param mes mes do qual se deseja descobrir total de dias
    \param ano ano para considerar o caso de ser bissexto

    \return quantidade de dias do mes recebido
*/
int Ultimo_Dia_Mes(int mes, int ano);

/*! \brief Descricao: Recebe o ptr contendo o dia o mes e o ano de interesse e calcula
(considerando também os anos bissextos) qual dia do ano esses dados representam

    \param data ptr de struct com campos: dia, mes e ano

    \return o dia do ano
*/
int Formata_Dia(tipo_data_info *data);

/*! \brief Descricao: baseado nas informacoes recebidas, calcula o dia da semana correspondente

    \param data ptr de struct com campos: dia, mes e ano

    \return inteiro representando o dia da semana [0-6]
*/
int Dia_Semana(tipo_data_info *data);

/*! \brief Descricao: le a string do dia da semana e calcula o dia que ela representa [0-6]

    \param dia_semana cadeia de caracteres representando o dia da semana(ex:Seg)

    \return numero que representa o dia da semana lido
*/
int Numero_Semana(char *dia_semana);

/*! \brief Descricao: recebe um no da lista de disponibilidade com o campo data: 00, e expande as
informacoes da disponibilidade para todos os dias da semana informado do mes recebido

    \param dia_semana p1_disp para no da lista de disponibilidade do local analisado
    \param pinicio_disp ptr para o inicio da lista de disponibilidade
    \param data ptr com as informacoes da data

    \return void
*/
void Estende_Disponibilidade(tipo_disponibilidade_local* p1_disp, tipo_disponibilidade_local **pinicio_disp, tipo_data_info *data);

/*! \brief Descricao: Trata as localidades da lista recebida, criando as disponibilidades pertencentes a cada local

    \param pinicio ptr o inicio da lista de localidades ainda nao tratados

    \return void
*/
tipo_local* Trata_Localidade(tipo_local* pinicio);

#endif // LOCALIDADES_TRATAMENTO_H

