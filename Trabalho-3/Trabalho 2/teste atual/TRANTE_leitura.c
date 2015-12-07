/*          Componente palesTRANTE, módulo de leitura


Realiza a leitura dos dados do arquivo de palestrante. Ou seja, torna disponivel na RAM 
o que esta no arquivo (nao faz tratamento)
--------------------------------------------------------------------------------

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "TRANTE_auxiliar.h"


#include "TRANTE_leitura.h"



/* A funcao le_palestrantes recebe o ponteiro para o arquivo de palestrantes, 
cria a lista dea palestrantes e retorna o ponteiro para essa lista.
Em caso de erro, retorna NULL */



TRANTE_cabecalho *Le_palestrantes( FILE *arq_palestrantes ){
    
    
    TRANTE_cabecalho *header = NULL;

    char buffer_nome[101];
    char buffer_disp[101];    
    
    int teste;
    
    
    header = Cria_ListaPalestrantes();
    teste = 0;
    


    while( !feof(arq_palestrantes) ){
        

/*        printf("\nvou ler o nome");*/

        fscanf( arq_palestrantes, "%*s " ); /*ignora inicio da linha "Nome: "*/
        fscanf( arq_palestrantes, "%[^\n]", buffer_nome ); /*copia o restante da linha do nome*/
        
        
        /*printf("\nleitura:\t\t\tFOI LIDO: \"%s\" ", buffer_nome);
*/


 /*       printf("\nvou ler a disponibilidade");
 */

        fscanf( arq_palestrantes, "%*s " ); /*ignora inicio "Disponibilidade: "*/
        fscanf( arq_palestrantes, "%[^\n]", buffer_disp );
    
    /*    printf("\nleitura:\t\t\tFOI LIDA: \"%s\" ", buffer_disp);
*/

        if( buffer_nome[0] != '\0'  &&  buffer_disp[0] != '\0'){




            palestrante *novo_palestrante;
            novo_palestrante = (palestrante *)malloc( sizeof(palestrante) );

            if( novo_palestrante == NULL ){
                printf("\n\n Nao foi possivel alocar mais memoria. \n\t\tPressione qualquer tecla... \n\n");
                getchar();
                return NULL;

            }else{

                novo_palestrante->nome_pessoa = strdup(buffer_nome);
                novo_palestrante->disp_bruta = strdup(buffer_disp);
                novo_palestrante->lista_disp = Cria_ListaDisponibilidades();
                               
                Insere_Final_ListaPalestrantes(  &header, novo_palestrante);
            }

  /*          printf( "\nleitura:\tPalestrante[%d] = \"%s\" , \"%s\" \n\n",   header->qtde_palestrante,
                                                        (header->last)->nome_pessoa,
                                                        (header->last)->disp_bruta );
*/
            buffer_nome[0] = '\0'; 
            buffer_disp[0] = '\0';
        }

    }

    
    teste = Aponta_Inicio_ListaPalestrantes( &header );
    
    if( teste == 0 )
        printf("Erro.   Ja leu, ja criou a lista de palestrantes, porem nao conseguiu apontar para o inicio");

    return header;
}



/* strlen funciona assim: 

seja char palavra[4]

palavra = "abc\0" 
strlen(palavra) retorna 3 (ela conta a qtde de bytes (IGNORA \0)
palavra[0] = a
palavra[1] = b
palavra[2] = palavra[strlen(palavra)-1] = c
palavra[3] = palavra[strlen(palavra)] = \0


*/ 