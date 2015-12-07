/*          Módulo de leitura
Deve conter todas as funções para a leitura correta do arquivo, separando cada
informação de maneira correta e conveniente.

Entrada: Arquivo com informações das palestras e palestrantes.

Saída: Conjuntos de dados organizados.  
--------------------------------------------------------------------------------


Quando o main chamar a(s) funcao(oes) desse modulo, 
serao passados os ponteiros para os arquivos palestrantes.txt e palestra.txt

O modulo de leitura vai percorrer o arquivo de palestrantes e gerar uma lista e 
retornar um cabecalho para essa lista.

Na lista de palestrantes, os elementos (structs) serao compostos por:
    Palestrante p
    ponteiro p/ next elemento
    ponteiro p/ previous elemento


o campo p eh uma struct Palestrante com os campos:
    nome
    ponteiro para lista de disponibilidades


os elementos da lista de disponibilidades sao compostos dos campos:
    Disponibilidade d
    ponteiro p/ next elemento
    ponteiro p/ previous elemento
    

o campo d eh uma struct Disponibilidade com os campos:

char *dado_bruto (string lida do arquivo contendo uma disponibilidade);
int data (serah preenchido pelo modulo tratadados com a qtde de dias apos 1/jan);
int hora_inicio (serah preenchido pelo modulo tratadados  com a qtde de minutos);
int hora_fim (serah preenchido pelo modulo tratadados  com a qtde de minutos);
campo ponteiro p/ prox disponibilidade daquele mesmo palestrante;




O modulo de leitura tambem vai percorrer o arquivo de palestras. A partir dele, vai
gerar uma lista e um cabecalho para essa lista.

Na lista de palestras, os elementos (structs) serao compostos por:
char *nome_palestra;
char *responsavel;
char *tema;
char *local;
char *duracao_bruta;
int duracao_tratada; (serah preenchido pelo modulo tratadados com a qtde de minutos);
campo ponteiro para prox elemento.

Os 5 primeiros campos sao strings brutas, obtidas do arquivo.
*/
#ifndef LEITURA_H
#define LEITURA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listapalestras.h"



ListaPalestras Le_palestras(FILE *arq_palestras);
/* recebe o ponteiro para o arquivo de palestras, 
cria a lista de palestras e retorna o ponteiro para essa lista.
Em caso de erro, retorna NULL */

/*Vao ser devolvidas ao modulo correto, foram colocadas aqui para correção de erros somente*/




#endif
/*LEITURA_H*/