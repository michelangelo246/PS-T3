/*********************************************************************
                Modulo de persistencia de localidades

Esse modulo e responsavel por retornar uma lista com as informacoes
das localidades lidas e tratadas para o modulo calendario

    -------------------------------------------------------------
    Entrada: Saida dos modulos leitura e tramento das localidades

    Saida: Lista com informacoes lidas e tratadas.

Autor: Michelangelo.
**********************************************************************/

#ifndef LOCALIDADES_PERSISTENCIA_H
#define LOCALIDADES_PERSISTENCIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "localidades_leitura.h"
#include "localidades_tratamento.h"


/* Funcoes do modulo */

/*! \brief Descricao: imprime no arquivo: arquivo_teste_locais.txt
as informacoes contidas na lista de localidades

    \param p1 ptr para o inicio da lista de localidades

    \return void
*/
void Imprime_Localidades(tipo_local* p1);

/*! \brief Descricao: aciona os modulos de leitura e tratamento para produzir a lista
com os dados prontos para serem encaminhados ao modulo calendario

    \param void

    \return ptr para o inicio da lista de localidades preenchidas e tratadas
*/
tipo_local* Pega_Localidade();


#endif // LOCALIDADES_PERSISTENCIA_H
