#include <stdio.h>

#include "TRANTE_auxiliar.h"
#include "TRANTE_leitura.h"
#include "TRANTE_tempo.h"
#include "TRANTE_tratamento.h"
#include "TRANTE_persistencia.h"

int main( int argc, char *argv[] ){



	if(argc < 2){
		printf("\nErro!\n Nome do arquivo de entrada, contendo os palestrantes, nao foi informado. Tente novamente.\n");
		exit(EXIT_FAILURE);
	}	


	int teste, i, qtde_pessoas, k, qtde_disp;
	TRANTE_cabecalho *lista_palestrante = NULL;
	


	lista_palestrante = obter_palestrantes( argv[1] );
	if( lista_palestrante == NULL ){
		printf("\n\nErro! Lista de palestrantes nao foi obtida.\n");
		exit(EXIT_FAILURE);
	}

    teste = Aponta_Inicio_ListaPalestrantes( &lista_palestrante );	    
    if( teste == 0 ){
        printf("\nErro!\n  nao conseguiu apontar para o inicio da lista tratada");
        return teste;
    }


	qtde_pessoas = Conta_Pessoas_ListaPalestrantes( lista_palestrante );
	i = 1;


	while( i <= qtde_pessoas ){

        printf( "\n\nPalestrante[%d] = \"%s\"", i, (lista_palestrante->current)->nome_pessoa );


	    teste = Aponta_Inicio_ListaDisponibilidades( &( (lista_palestrante->current)->lista_disp ) );			    
	    if( teste == 0 ){
	        printf("\n\nAtencao!\n O palestrante[%d] nao possui disponibilidade em data futura", i);
	        printf("\n\n");
	        
	    }else{

			qtde_disp = Conta_Disps_ListaDisponibilidades( (lista_palestrante->current)->lista_disp );
	        k = 1;

	        while( k <= qtde_disp ){

		        printf(		"\n\tDisponibilidade[%d] =\tdia %d horario:  de %d ate %d", k,  
		        																		  (((lista_palestrante->current)->lista_disp)->current)->data,
		        																		  (((lista_palestrante->current)->lista_disp)->current)->hora_inicio,
		        																		  (((lista_palestrante->current)->lista_disp)->current)->hora_fim  	);



		        teste = Aponta_Proximo_ListaDisponibilidades( &( (lista_palestrante->current)->lista_disp ) );
		        if( teste == 0 && k != qtde_disp ){
		            printf("\n\nErro!\n  nao conseguiu apontar para a proxima disponibilidade do palestrante[%d]", i);
		            break;
		        }

		        k++;
	        }

	    }


        teste = Aponta_Proximo_ListaPalestrantes( &lista_palestrante );
        if( teste == 0 && i != qtde_pessoas ){
            printf("\nErro!\n  nao conseguiu apontar para o proximo palestrante");
            break;
        }


		i++;
	}


    printf("\n\n");


	return 0;
}
