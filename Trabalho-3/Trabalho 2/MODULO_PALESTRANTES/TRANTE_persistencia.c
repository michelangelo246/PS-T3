
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TRANTE_auxiliar.h"
#include "TRANTE_leitura.h"
#include "TRANTE_tempo.h"
#include "TRANTE_tratamento.h"

#include "TRANTE_persistencia.h"


TRANTE_cabecalho *obter_palestrantes( char *nome_arq_palestrantes ){

	FILE *arquivo;
	int teste;
	TRANTE_cabecalho *lista_palestrante = NULL;



	arquivo = fopen	( nome_arq_palestrantes, "r" );
	if(arquivo == NULL){
		printf("\nErro!\n Nao foi possivel abrir o arquivo \"%s\" Verifique se ele esta salvo na pasta corrente e tente outra vez.\n", nome_arq_palestrantes);
		return NULL;
	}	


	lista_palestrante = Le_palestrantes( arquivo );
	if( lista_palestrante == NULL ){
		printf("\nErro!\n O arquivo foi aberto, mas nao foi possivel ler as informacoes dos palestrantes");;
		fclose(arquivo);
		return NULL;
	}
	

    teste = TrataListaPalestrantes( &lista_palestrante );
    if( teste != 0 ){

        printf("\nErro!\n  nao conseguiu tratar a lista de palestrante\n\n");
    	return NULL;
    }

	return lista_palestrante;
}
