/*          Componente palesTRANTE, módulo de tratamento


Recebe a lista de palestrantes gerada pelo modulo de leitura e faz o tratamento.
Especificamente, esse modulo acessa a disponibilidade bruta do palestrante e faz
a conversao para data, hora de inicio e hora de fim.
--------------------------------------------------------------------------------

*/


#ifndef TRANTE_TRATAMENTO

#define TRANTE_TRATAMENTO

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "TRANTE_auxiliar.h"
#include "TRANTE_leitura.h"
#include "TRANTE_tempo.h"


#define MAX_DIA_SEMANA 100
#define MAX_DATA 100
#define MAX_MIN_INICIO 100
#define MAX_MIN_FIM 100
#define MAX_HORA_INICIO 100
#define MAX_HORA_FIM 100



int ConverteDisponibilidadeBruta(TRANTE_cabecalho **header);
/*
funcao ConverteDisponibilidadeBruta
    Entrada: ponteiro para o cabecalho da lista de palestrantes criada pelo modulo de leitura. 
    Saida: inteiro (0 indicando sucesso ou valor negativo em caso de erro)
    
    Descricao: acessa  o campo disp_bruta de cada palestrante e cria uma estrutura de dados para cada disponibilidade,
    ou seja, cada período de disponibilidade dentro de um dia. 
    Isso é feito apenas para datas futuras (dias que ocorrem após a data atual do sistema).
    As estruturas sao criadas com datas e horários convertidos.
    As datas são convertidas em um inteiro de 1 a 366 representando o dia do ano,
    e as horas (de inicio e fim) sao convertidas em um inteiro (quantidade de minutos desde 00:00)
    Essa funcao organiza tais estruturas em uma lista de disponibilidades e 
    atualiza o campo lista_disp de cada palestrante com o endereco do 
    cabecalho da lista de disponibilidades criada.
    
*/


int TrataListaPalestrantes(TRANTE_cabecalho **header);
/*
funcao TrataListaPalestrantes
    Entrada: ponteiro para o cabecalho da lista de palestrantes criada pelo modulo de leitura. 
    Saida: inteiro (0 indicando sucesso ou valor negativo em caso de erro)
    
    Descricao: faz chamada das funcoes de tratamento e verifica se todas ocorreram com sucesso.
    Atualmente, dada as especificações, existe apenas uma funcao a ser chamada, qual seja a
    funcao ConverteDisponibilidadeBruta.
    
*/

    

int Eh_delimitador(char incognita);
/*
funcao Eh_delimitador
    Entrada: um caractere. 
    Saida: um inteiro (0 indicando que o caractere nao é um delimitador, ou 1 indicando que o caractere é um delimitador)sucesso ou valor negativo em caso de erro)
    
    Descricao: Verifica se o caracatere recebido é um delimitador dos campos de disponibilidade. Funcao auxiliar para tratamento 
    da dsiponibilidade dos palestrantes.
    
*/


#endif
