


#define _XOPEN_SOURCE
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#include "TRANTE_tempo.h"



int quebra_data( char *data_completa, struct tm **data_quebrada ){
    
    /* inicializacao da variavel */
    time_t rawtime;
    time( &rawtime );
    (*data_quebrada) = localtime( &rawtime );
    
    if( strptime( data_completa, " %d / %m / %Y ", (*data_quebrada) ) == NULL ){
        printf("\n\nErro na strptime!\n\n" );
        return -1;
    }
    /* no 2o argumento: espaco em branco coincide com ZERO ou mais espacos em branco */
       

    if( data_quebrada != NULL ){

        ((*data_quebrada)->tm_yday)++; /* strptime considera o ano de 0 a 365. agora temos de 1 a 366 */
        ((*data_quebrada)->tm_mon)++; /* strptime considera o mes de 0 a 11. agora temmos de 1 a 12  */
        ((*data_quebrada)->tm_year) += 1900; /* strptime considera 1900 como ano 0. Por isso somo 1900 */
          
        
        /* Se deu certo...
        Os campos de data_quebrada foram atualizados.
        Os seguintes campos podem ser utilizados: 

        data_quebrada->tm_mday  = dia do mes
        data_quebrada->tm_mon   = mes
        data_quebrada->tm_year  = qtde de anos apos 1900. Ex: 2015 = 115
        data_quebrada->tm_wday  = dia da semana (domingo = 0..sabado = 6)
        data_quebrada->tm_yday  = dia do ano (1o de jan = 0, 2/1 = 1, ... 31/12 = 364)
        
        os demais campos podem ser ignorados...
        */
        
        return 0;

    }else{
        printf("\n\nNao foi possivel converter a data %s para o formato struct tm (time.h)\n\n",data_completa);
        return -1;
    }

}



int DiaHoje(struct tm **hoje){
    
    time_t Segundos;
    time(&Segundos); /*<! Passa para a variável a hora atual em segundos. */
    (*hoje) = localtime(&Segundos); /*!< Converte os segundos para o formato de horas. */

    
    if( (*hoje) == NULL ){
        printf("\n\n Erro! Nao foi possivel obter data atual do sistema \n\n");
        return -1;
    }
    
    (*hoje)->tm_yday++;
    (*hoje)->tm_mon++;
    (*hoje)->tm_year += 1900;

    return 0;
    
}



int ConverteSemanal(char *dia){
    
    if(dia[0]=='\0')
        return -1;
    
    /* possibilidades: domingo, segunda, terca, quarta, quinta, sexta, sabado
        conversao respectiva: 0,   1,     2,      3,      4,      5,     6
        OBS: esse eh o padrao da time.h NAO PODE SER MUDADO */
    
    switch( tolower(dia[0]) ){
        case 'd':
            return 0;
            break;
        
        case 't':
            return 2;
            break;
        
        case 'q':
        
            switch( tolower(dia[2]) ){
                case 'a':
                    return 3;
                    break;
                
                case 'i':
                    return 4;
                    break;
                
                default:
                    printf("\n\nErro! Dia da semana iniciado com \"q\", mas nao eh qua/qui!\n");
                    printf("Em vez disso, encontrado %c%c%c\n\n", dia[0], dia[1], dia[2]);
                    break;
            }
            break;
        
        case 's':
        
            switch( tolower(dia[2]) ){
                case 'g':
                    return 1;
                    break;
                
                case 'x':
                    return 5;
                    break;
                
                case 'b':
                    return 6;
                    break;
                
                default:
                    printf("\n\nErro! Dia da semana iniciado com \"s\", mas nao eh seg/sex/sab!\n");
                    printf("Em vez disso, encontrado %c%c%c\n\n", dia[0], dia[1], dia[2]);
                    break;
            }
            break;
            
            default:
                printf("\n\nErro! Dia da semana com caractere inicial inesperado!\n");
                printf("Esperado \" d, s, t, q\". Em vez disso, encontrado %c\n\n", dia[0]);
                break;
    }
    
    return -1; /* return para o caso de erro... */
    
    
}


int Ultimo_dia(int mes, int ano){
    
    if(mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12)
        return 31;
            
    if( mes==4 || mes==6 || mes==9 || mes==11)
        return 30;
    
    /* se nao deu return, estamos em fevereiro */
    if( ano % 4 == 0 && (ano % 400 == 0  || ano % 100 != 0) )
        return 29; /*ano bissexto*/
        
    return 28;
        
}
