/*          Módulo de tratamento de dados
Com os dados lidos, faz manipulações necessárias (p.e Tratamento de
maiúsculas e minúsculas, conversão da hora lida para um tipo mais fácil para
manipulação, etc.). Aloca e preenche as estruturas com essas informações.

Entrada: Saída do módulo de leitura.

Saída: Dados prontos para serem alocados nas estruturas.
-------------------------------------------------------------------------------


A(s) funcao(oes) desse modulo sera(o) chamada(s) pela main somente apos ter sido
feita toda a leitura dos arquivos de entrada. 

Portanto, ja existira a lista e o cabecalho da lista referente aos palestrantes
e tambem referente aas palestras.

A funcao(oes) do modulo tratadados recebe(m) como parametro o cabecalho para a
lista que sera tratada.



No caso do tratamento da lista de palestrante:
Acessa o campo campo dado_bruto, verifica se contem algo do tipo:
dia_semana, 00/mm/aaaa, hora_inicio-hora_fim.

    1) se for esse o caso, o modulo acrescenta elementos de disponibilidade
para aquele palestrante. O modulo devera chamar alguma funcao do modulo 
controletempo para obter todas as datas dentro de mes "mm"/"aaaa" que sao 
dia_semana. (exemplo: todas as quartas do mes de julho de 2016). Alem disso,
esses novos elemento deverao ser preenchidos no campo data com essas datas 
obtidas, e no campo hora_inicio com a correspondente hora de inicio (convertida 
a partir da string (dado_bruto) e analogamente para o campo hora_fim

    2) se nao for esse o caso, basta realizar a conversao da string (dado_bruto)
para obter a data, a hora de inicio e a hora de fim no formato adequado para
preencher os campos data, hora_inicio e hora_fim respectivamente.




No caso do tratamento da lista de palestra:
Ele soh precisa acessar o campo duracao_bruta (string) fazer a conversao para  
int que eh a quantidade total de minutos.


*/
#ifndef TRATADADOS_H
#define TRATADADOS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "listapalestras.h"
#include "palestras_leitura.h"


#define MAX_DIA_SEMANA 100

#define MAX_DATA 100
#define MAX_MIN_INICIO 100
#define MAX_MIN_FIM 100
#define MAX_HORA_INICIO 100
#define MAX_HORA_FIM 100


int LidarMaiusculas(ListaPalestras header);


/* Recebe ponteiro para cabecalho da lista de palestrantes
    trata os respectivos dados
    retorna 0 em caso de sucesso
    retorna numero negativo em caso de erro */




int TrataListaPalestras(ListaPalestras header);
/* Recebe ponteiro para cabecalho da lista de palestras
    trata os respectivos dados
    retorna 0 em caso de sucesso
    retorna numero negativo em caso de erro */
    

int ConverteDuracaoBruta(ListaPalestras header);

#endif
/*TRATADADOS_H*/
