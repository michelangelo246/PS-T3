/*          Componente palesTRANTE, módulo de leitura


Realiza a leitura dos dados do arquivo de palestrante. Ou seja, torna disponivel na RAM 
o que esta no arquivo (nao faz tratamento)
--------------------------------------------------------------------------------

*/

#ifndef TRANTE_LEITURA

#define TRANTE_LEITURA

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "TRANTE_auxiliar.h"



TRANTE_cabecalho *Le_palestrantes( FILE *arq_palestrantes );
/*
funcao Le_palestrantes
    Entrada: ponteiro de arquivo referente ao arquivo contendo as informacoes de palestrantes, 
    Saida: ponteiro para o cabecalho da lista de palestrantes criada com as informacoes
    contidas no arquivo.
    Em caso de erro, retorna NULL.
    
    Descricao: faz a leitura do arquivo, cria as estrutras de dados preenchendo com os dados lidos, 
    porem sem fazer tratamento (copia simples). Ela tambem organiza as estrutras criadas em uma lista
    e retorna o ponteiro (endereco) do cabecalho dessa lista. 

*/



#endif
