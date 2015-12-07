/*          Módulo de controle de tempo
Realiza consultas, conversao de estruturas e dados para que sejam manipulados
de acordo com a semantica de tempo.

*/

#ifndef TRANTE_TEMPO

#define TRANTE_TEMPO

#define _XOPEN_SOURCE
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/* Simulando um tipo booleano...
enum bool {
    true = 1, false = 0
};
*/

int quebra_data(char *data_completa, struct tm **data_quebrada);

int DiaHoje(struct tm **hoje);

int ConverteSemanal(char *dia);

int Ultimo_dia(int mes, int ano);


#endif
