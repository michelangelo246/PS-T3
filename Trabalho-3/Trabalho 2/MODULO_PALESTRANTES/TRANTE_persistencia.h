
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TRANTE_auxiliar.h"
#include "TRANTE_leitura.h"
#include "TRANTE_tempo.h"
#include "TRANTE_tratamento.h"


TRANTE_cabecalho *obter_palestrantes( char *nome_arq_palestrantes );
/*
funcao obter_palestrantes
    Entrada: nome do arquivo contendo as informacoes sobre os palestrantes. O arquivo deve estar na pasta corrente.
    Saida: ponteiro para o cabecalho da lista de palestrantes ja tratada.
    Em caso de erro, retorna NULL.
    
    Descricao: faz chamada das funcoes dos modulo de leitura e de tratamento,
    e disponibiliza a lista de palestrantes, já tratada, para o componente calendario.
    
*/
