/*          Componente palesTRANTE, módulo de tratamento


Recebe a lista de palestrantes gerada pelo modulo de leitura e faz o tratamento.
Especificamente, esse modulo acessa a disponibilidade bruta do palestrante e faz
a conversao para data, hora de inicio e hora de fim.
--------------------------------------------------------------------------------

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "TRANTE_auxiliar.h"
#include "TRANTE_leitura.h"
#include "TRANTE_tempo.h"


#include "TRANTE_tratamento.h"



int TrataListaPalestrantes(TRANTE_cabecalho **header){
    
    
    /* Recebe ponteiro para cabecalho da lista de palestrantes
        trata os respectivos dados
        retorna 0 em caso de sucesso
        retorna numero negativo em caso de erro */
        
    int resultado;

    resultado = ConverteDisponibilidadeBruta(header);
    
    
    if( resultado < 0){
        return -2;
    }
    
    return 0;
    
    
}
    
int ConverteDisponibilidadeBruta(TRANTE_cabecalho **header){

    if(     ListaPalestrantes_Vazia( (*header) )    ){
        printf("\nRecebida lista de palestrantes vazia para tratamento de disponibilidade bruta\n");
        
        return -1;
    }
    
    struct tm *brokendown;  /* tm eh definida na time.h, incluida pelo modulo controletempo */

    DiaHoje( &brokendown );
    
    
    
    int dia_do_ano_hoje, existe_disponibilidade_futura;
   
    dia_do_ano_hoje = (brokendown->tm_yday);
    existe_disponibilidade_futura = 0; /* serve para testar se o palestrante possui disponibilidade em data futura */


    /*
    printf("\n\nTRANTE_tratamento: Hoje eh dia %d/%d/%d   dia do ano = %d   dia_da_semana = %d (domingo = 0)  \n", brokendown->tm_mday, brokendown->tm_mon, brokendown->tm_year, brokendown->tm_yday, brokendown->tm_wday);
    */

    char buffer_dia_semana[MAX_DIA_SEMANA];
    int pegou_dia_da_semana; /* para verificar se conseguiu esse campo */

    char buffer_data[MAX_DATA];
    
    char buffer_hora_inicio[MAX_HORA_INICIO];
    char buffer_minutos_inicio[MAX_MIN_INICIO];
    
    char buffer_hora_fim[MAX_HORA_FIM];
    char buffer_minutos_fim[MAX_MIN_FIM];
    
    int ind_bruto, limite_bruto;

    int ind_buffer_dia_semana, ind_buffer_data;
    int ind_buffer_hora_inicio, ind_buffer_minutos_inicio;
    int ind_buffer_hora_fim, ind_buffer_minutos_fim;
    
    int erros = 0;
    int continuee = 1; /* se encontrar um erro grave, continuee=0, ignora aquela disp, e entao trata o prox elemento */
    
    int elementos_para_tratar;
    elementos_para_tratar = Conta_Pessoas_ListaPalestrantes( (*header) );

    if( Aponta_Inicio_ListaPalestrantes( header ) == 0){
        printf("\nErro! Nao foi possivel apontar para o inicio da lista de palestrantes\n");

        return -1;
    }
    
    while(elementos_para_tratar > 0){     /* enquanto houver Palestrantes para tratar... */
    
    
        ind_bruto = 0; /* indice para percorrer dado_bruto de cada Palestrante */
        limite_bruto = strlen(  (*header)->current->disp_bruta );

            
            while( ind_bruto < limite_bruto ){
                
                
                 /* enquanto houver caracteres para ler...
                 pega dia da semana, data completa, hora de inicio, hora de fim
                 trata esses dados
                 e volta para o inicio desse laco e verifica se ha mais disponibilidade */
                
                while(      isblank(  ( (*header)->current )->disp_bruta[ind_bruto]  )      ){
                    ind_bruto++;
                }
                 
                continuee = 1 ; /* a cada nova disponibilidade, faco o reset desse flag */
                pegou_dia_da_semana = 1; /* a cada nova disponibilidade, considero que vou conseguir esse campo*/
                     
                     
                /* laco para ler o dia da semana */ 
                ind_buffer_dia_semana = 0;
                while( ind_bruto < limite_bruto ){

                    
                    if(  Eh_delimitador(  ( (*header)->current )->disp_bruta[ind_bruto]  ) ){
                        /* se encontrar um separador de campo,
                        incrementa o indice de dado_bruto (para ler data) e sai do laco */
                        ind_bruto++;
                        break;

                    }else{
                    
                        if( isalpha(  ( (*header)->current )->disp_bruta[ind_bruto]  )  ){
                            /* se encontrar letra: copia para buffer de dia da semana  */
                            buffer_dia_semana[ind_buffer_dia_semana] =  (*header)->current->disp_bruta[ind_bruto];
                            ind_bruto++;
                            ind_buffer_dia_semana++;
                            
                        }else{
                        
                            if( isblank(  ( (*header)->current )->disp_bruta[ind_bruto]  )  ){
                                /* se encontrar espaco, ignora */
                                while( isblank(  ( (*header)->current )->disp_bruta[ind_bruto]  )  ){
                                    ind_bruto++;
                                }
                                
                            }else{
                                /* Se encontrou algo que nao eh delimitador, nem letra, nem espaco em branco, entao e um erro */
                                printf("\n Foi encontrado um caractere invalido dentro do campo dia da semana.\n");
                                printf("Eram esperados letra \"a-z A-Z\"  ou um delimitador: \"; : , .\". Em vez disso foi encontrado \"%c\" \n",
                                                                                                                                    ((*header)->current)->disp_bruta[ind_bruto] );

                                erros++;
                                continuee = 1; /* perder o dia da semana pode nao ser grave */
                                pegou_dia_da_semana = 0;
                                /* se eu pegar uma data do tipo 00/mm/aaaa, entao serah um erro grave */
                                
                                ind_bruto++; /* vou ler o proximo campo (data) */
                                
                                break;
                            }
                        }
                    } 


                }
                /* faco o fechamento do buffer de dia da semana */
                buffer_dia_semana[ind_buffer_dia_semana] = '\0';


                
                /* laco para ler data completa no formato dd/mm/aaaa */
                ind_buffer_data = 0;
                while( (ind_bruto < limite_bruto) && continuee == 1){
                     /* enqto tiver caractere e nenhum erro grave */
                     
                
                    if(  Eh_delimitador(  ( (*header)->current )->disp_bruta[ind_bruto]  )){
                        /* se encontrar um separador de campo,
                        incrementa o indice de dado_bruto (para ler hora inicio) e sai do laco */
                        ind_bruto++;
                        break;

                    }else{
                    
                        if(  isdigit(  ( (*header)->current )->disp_bruta[ind_bruto]  ) ||  ( (*header)->current )->disp_bruta[ind_bruto] == '/' ){
                            /* se encontrar digito ou barra de data: copia para buffer de data  */
                            buffer_data[ind_buffer_data] =  (*header)->current->disp_bruta[ind_bruto];
                            ind_bruto++;
                            ind_buffer_data++;
                        }else{
                        
                            if( isblank(  ( (*header)->current )->disp_bruta[ind_bruto]  )  ){
                                /* se encontrar espaco, ignora */
                                while( isblank(  ( (*header)->current )->disp_bruta[ind_bruto]  )  ){
                                    ind_bruto++;
                                }
                                 
                            }else{

                                /* Se encontrou algo que nao eh dd/dd/dddd, nem delimitador, nem espaco em branco, entao eh um erro */
                                printf("\n Foi encontrado um caractere invalido dentro do campo data.\n");
                                printf("Eram esperados digito ou \" / \" (barra) ou um delimitador: \"; : , .\" Em vez disso foi encontrado \"%c\" \n", ((*header)->current)->disp_bruta[ind_bruto] );

                                /* perder a data eh grave. Nao dah para determinar a disponibilidade */
                                erros++;
                                continuee = 0;
                                
                                ind_bruto++; /* vou ler o proximo campo (data) */
                                
                            }
                        }
                    }

                }
                /* faco o fechamento do buffer de data */
                buffer_data[ind_buffer_data] = '\0';
                
                
                
                /* laco para ler as horas da hora de inicio */
                ind_buffer_hora_inicio = 0;
                while( (ind_bruto < limite_bruto) && continuee == 1){
                     /* enqto tiver caractere e nenhum erro grave */
                    
                    if(   (*header)->current->disp_bruta[ind_bruto] == ':'){
                        /* se encontrar ":"
                        incrementa o indice de dado_bruto (para ler minutos inicio) e sai do laco */
                        ind_bruto++;
                        break;

                    }else{
                    
                        if(  isdigit(  ( (*header)->current )->disp_bruta[ind_bruto]  )){
                            /* se encontrar digito: copia para buffer de hora inicio  */
                            buffer_hora_inicio[ind_buffer_hora_inicio] =  (*header)->current->disp_bruta[ind_bruto];
                            ind_buffer_hora_inicio++;
                            ind_bruto++;

                        }else{
                        
                            if( isblank(  (*header)->current->disp_bruta [ind_bruto] )  ){
                                /* se encontrar espaco, ignora */
                                while( isblank(  (*header)->current->disp_bruta [ind_bruto] )  ){
                                    ind_bruto++;
                                }
                                
                            }else{
                                /* Se encontrou algo que nao eh digito, nem ":" entao eh um erro */
                                printf("\n Foi encontrado um caractere invalido dentro do campo hora de inicio.\n");
                                printf("Eram esperados digito ou o separador \" : \" Em vez disso foi encontrado \"%c\" \n",  (*header)->current->disp_bruta[ind_bruto] );
                                getchar();
                                /* perder a hora eh grave. Nao dah para determinar a disponibilidade */
                                erros++;
                                continuee = 0;
                                
                                ind_bruto++; /* vou ler o proximo campo (data) */
                                
                            }
                        }
                    }


                }
                /* faco o fechamento do buffer de data */
                buffer_hora_inicio[ind_buffer_hora_inicio] = '\0';
                
                
                /* laco para ler os minutos da hora de inicio */
                ind_buffer_minutos_inicio = 0;    /* copiar o "campo minutos" da hora de inicio da disponib */
                while( (ind_bruto < limite_bruto) && continuee == 1){
                     /* enqto tiver caractere e nenhum erro grave */
                    
                    if(   (*header)->current->disp_bruta[ind_bruto] == '-'){
                        /* se encontrar "-"
                        incrementa o indice de dado_bruto (para ler hora fim) e sai do laco */
                        ind_bruto++;
                        break;

                    }else{
                    
                        if(  isdigit(  ( (*header)->current )->disp_bruta[ind_bruto]  )){
                            /* se encontrar digito: copia para buffer de minuto inicio  */
                            buffer_minutos_inicio[ind_buffer_minutos_inicio] =  (*header)->current->disp_bruta[ind_bruto];
                            ind_buffer_minutos_inicio++;
                            ind_bruto++;

                        }else{
                        
                            if( isblank(  (*header)->current->disp_bruta [ind_bruto] )  ){
                                /* se encontrar espaco, ignora */
                                while( isblank(  (*header)->current->disp_bruta [ind_bruto] )  ){
                                    ind_bruto++;
                                }
                                
                            }else{
                                /* Se encontrou algo que nao eh digito, nem "-" entao eh um erro */
                                printf("\n Foi encontrado um caractere invalido dentro do campo minuto de inicio.\n");
                                printf("Eram esperados digito ou o separador \" - \" Em vez disso foi encontrado \"%c\" \n",  (*header)->current->disp_bruta[ind_bruto] );
                                getchar();
                                /* perder os minutos eh grave. Nao dah para determinar a disponibilidade */
                                erros++;
                                continuee = 0;
                                
                                ind_bruto++; /* vou ler o proximo campo (data) */
                                
                            }
                        }
                    }
                }
                /* faco o fechamento do buffer de minuto inicio */
                buffer_minutos_inicio[ind_buffer_minutos_inicio] = '\0';
                
                
                
                /* laco para ler as horas da hora de fim */
                ind_buffer_hora_fim = 0;      /* para copiar hora_fim */
                while( (ind_bruto < limite_bruto) && continuee == 1){
                     /* enqto tiver caractere e nenhum erro grave */
                    
                    if(   (*header)->current->disp_bruta[ind_bruto] == ':'){
                        /* se encontrar ":"
                        incrementa o indice de dado_bruto (para ler minutos inicio) e sai do laco */
                        ind_bruto++;
                        break;

                    }else{
                    
                        if(  isdigit(  ( (*header)->current )->disp_bruta[ind_bruto]  )){
                            /* se encontrar digito: copia para buffer de hora fim  */
                            buffer_hora_fim[ind_buffer_hora_fim] =  (*header)->current->disp_bruta[ind_bruto];
                            ind_buffer_hora_fim++;
                            ind_bruto++;

                        }else{
                        
                            if( isblank(  (*header)->current->disp_bruta [ind_bruto] )  ){
                                /* se encontrar espaco, ignora */
                                while( isblank(  (*header)->current->disp_bruta [ind_bruto] )  ){
                                    ind_bruto++;
                                }
                                
                            }else{
                                /* Se encontrou algo que nao eh digito, nem ":" entao eh um erro */
                                printf("\n Foi encontrado um caractere invalido dentro do campo hora de fim.\n");
                                printf("Eram esperados digito ou o separador \" : \" Em vez disso foi encontrado \"%c\" \n",  (*header)->current->disp_bruta[ind_bruto] );
                                getchar();
                                /* perder a hora eh grave. Nao dah para determinar a disponibilidade */
                                erros++;
                                continuee = 0;
                                
                                ind_bruto++; /* vou ler o proximo campo (data) */
                                
                            }
                        }
                    }
                }
                /* faco o fechamento do buffer de hora fim */
                buffer_hora_fim[ind_buffer_hora_fim] = '\0';
                
                
                /* laco para ler os minutos da hora de fim */
                ind_buffer_minutos_fim = 0;    /* copiar o "campo minutos" da hora de inicio da disponib */
                while( (ind_bruto < limite_bruto) && continuee == 1){
                     /* enqto tiver caractere e nenhum erro grave */
                    
                    if(  Eh_delimitador(  (*header)->current->disp_bruta [ind_bruto] )){
                        /* se encontrar algum delimitador
                        incrementa o indice de dado_bruto (para ler proxima disponib desse Palestrante) e sai do laco */
                        ind_bruto++;
                        break;
                    
                    }else{
                    
                        if(  isdigit(  ( (*header)->current )->disp_bruta[ind_bruto]  )){
                            /* se encontrar digito: copia para buffer de minuto fim  */
                            buffer_minutos_fim[ind_buffer_minutos_fim] =  (*header)->current->disp_bruta[ind_bruto];
                            ind_buffer_minutos_fim++;
                            ind_bruto++;

                        }else{
                        
                            if( isblank(  (*header)->current->disp_bruta [ind_bruto] )  ){
                                /* se encontrar espaco, ignora */
                                while( isblank(  (*header)->current->disp_bruta [ind_bruto] )  ){
                                    ind_bruto++;
                                }
                                
                            }else{
                                /* Se encontrou algo que nao eh digito, nem "-" entao eh um erro */
                                printf("\n Foi encontrado um caractere invalido dentro do campo minuto de fim.\n");
                                printf("Era esperado digito ou o separador \" - \" Em vez disso foi encontrado \"%c\" \n",  (*header)->current->disp_bruta[ind_bruto] );

                                /* perder os minutos eh grave. Nao dah para determinar a disponibilidade */
                                erros++;
                                continuee = 0;
                                
                                ind_bruto++; /* vou ler o proximo campo (data) */
                                
                            }
                        }
                    }
                }
                /* faco o fechamento do buffer de minuto fim */
                buffer_minutos_fim[ind_buffer_minutos_fim] = '\0';
                
                
                
                if( continuee == 1 ){
                    
                    int hora_inicio, hora_fim;
                    
                    hora_inicio = atoi( buffer_minutos_inicio ) + 60*( atoi(buffer_hora_inicio) );
                    hora_fim = atoi( buffer_minutos_fim ) + 60*( atoi(buffer_hora_fim) );

                    /*                    
                    printf("\n\nTRANTE_tratamento: hora inicio = %d  e  hora_fim = %d\n", hora_inicio, hora_fim);
                    */
    

                    
                    if( buffer_data[0] == '0' && buffer_data[1] == '0' ){
                        /* entao essa disponibilidade deve ser expandida, ou seja, 
                        para todos os dias do mes que coincidem com esse dia da semana deve 
                        ser colocada essa mesma hora inicio e hora fim */
                        if( pegou_dia_da_semana == 0 ){
                            /* se nao pegou o dia da semana, entao nao dah pra expandir... essa disponibilidade nao deve ser considerada */
                            ((( (*header)->current)->lista_disp)->current)->data = -1; /* valor negativo indica que essa data nao serve */
                            printf("\n Nao foi possivel determinar adequadamente a disponibilidade para o mes %s.\n", (buffer_data+3));/* pula 3 caracteres e imprime o resto da data */
                            printf("O dia da semana foi informado com erro\n");
                            
                            erros++;
                       
                        }else{
                            
                            /* expandir a disponibilidade */
                            /* vou percorrendo o mes e verificando se o dia da semana 
                            eh igual a buffer_dia_semana*/

                            /*
                            printf("\n\nTRANTE_tratamento: expansao de \"%s\" \n", buffer_data);
                            */


                            buffer_data[0] = '0'; /* primeiro dia do mes */
                            buffer_data[1] = '1'; /* primeiro dia do mes */
                            
                             if( quebra_data( buffer_data, &brokendown ) != 0 ){
                                
                                printf("\n\nErro!\nNao foi possivel quebrar a data!\n\n");
                                erros++;

                            }else{
                                
                                int dia_semana_disponivel, ultimo_dia_do_mes;
                                
                                dia_semana_disponivel = ConverteSemanal(buffer_dia_semana);
                                
                                
                                /*quebra_data ja ajusta o mes para [1-12] e ajusta o ano (soma 1900)*/
                                ultimo_dia_do_mes = Ultimo_dia( brokendown->tm_mon, brokendown->tm_year );
                                
                                while( brokendown->tm_mday <= ultimo_dia_do_mes ){

                                    /*printf("\n\nTRANTE_tratamento: dia a ser testado =  \"%d\" (no ano: %d) \n", brokendown->tm_mday, brokendown->tm_yday);
                                    */  
                                    if( ( (brokendown->tm_wday)%7 ) == dia_semana_disponivel ){
                                        

                                         /* antes de criar, deve verificar se eh data passada
                                        garantir que dia disponivel >= dia de hj!*/
                                         if( brokendown->tm_yday >= dia_do_ano_hoje ){

                                            existe_disponibilidade_futura = 1;
                                             
                                        
                                            disponibilidade *nova_disp;
                                            nova_disp = (disponibilidade *)malloc( sizeof(disponibilidade) );
                                            
                                            if( nova_disp == NULL ){
                                                printf("\n\nTRANTE_tratamento: Nao foi possivel alocar mais memoria. \n\t\tPressione qualquer tecla... \n\n");
                                                getchar();
                                            }else{
                                            
                                                nova_disp->data = brokendown->tm_yday;
                                                nova_disp->hora_inicio = hora_inicio;
                                                nova_disp->hora_fim = hora_fim;

                                                Insere_Final_ListaDisponibilidades( &(( (*header)->current)->lista_disp), nova_disp );

                                                
                                                /*
                                                printf("TRANTE_tratamento: Inserida a disponibilidade no dia %d hora_inicio = %d hora_fim = %d",
                                                                                                                                                 nova_disp->data,
                                                                                                                                                 nova_disp->hora_inicio,
                                                                                                                                                 nova_disp->hora_fim  );

                                                printf("\nTRANTE_tratamento: Na lista ficou assim: dia %d hora_inicio = %d hora_fim = %d\n\n",
                                                                                                                                                 ((( (*header)->current)->lista_disp)->last)->data,
                                                                                                                                                 ((( (*header)->current)->lista_disp)->last)->hora_inicio,
                                                                                                                                                 ((( (*header)->current)->lista_disp)->last)->hora_fim  );
                                                */                                                                                                                                                 
                                                

                                            }
                                                
                                        }
                                        
                                    }
                                    /* ja analisou esse dia do mes disponivel, vai para o proximo dia
                                        e no while testa se o proximo dia ainda esta contido no mes */
                                        
                                    brokendown->tm_mday++;
                                    brokendown->tm_wday++;
                                    brokendown->tm_yday++;
                                
                                }
                                
                                /* se nao eh mais um dia do mes disponivel, volta para o inicio do laco
                                para tratar outro trecho da disponibilidade (se houver) */
                            }
                            
                        }
                                limite_bruto = strlen(  (*header)->current->disp_bruta );

                    }else{
                        /* eh uma disponibilidade de um dia soh (nao um mes inteiro para analisar) */
                        
                        if(quebra_data(buffer_data, &brokendown)){
                            erros++;
                            printf("\nNaofoi possivel quebrar a data: \" %s \" \n", buffer_data);


                        }else{
                            
                            
                            if( brokendown->tm_yday >= dia_do_ano_hoje ){      /*se for data passada, ignora */

                                existe_disponibilidade_futura = 1;
                            
                                disponibilidade *nova_disp;
                                nova_disp = (disponibilidade *)malloc( sizeof(disponibilidade) );

                                if( nova_disp == NULL ){
                                    printf("\n\n Nao foi possivel alocar mais memoria. \n\t\tPressione qualquer tecla... \n\n");
                                    getchar();

                                }else{
                                
                                    nova_disp->data = brokendown->tm_yday;
                                    nova_disp->hora_inicio = hora_inicio;
                                    nova_disp->hora_fim = hora_fim;
                                    
                                    Insere_Final_ListaDisponibilidades( &(( (*header)->current)->lista_disp), nova_disp );

                                    /*
                                    printf("TRANTE_tratamento: Inserida a disponibilidade no dia %d hora_inicio = %d hora_fim = %d",
                                                                                                                                     nova_disp->data,
                                                                                                                                     nova_disp->hora_inicio,
                                                                                                                                     nova_disp->hora_fim  );

                                    printf("\nTRANTE_tratamento: Na lista ficou assim: dia %d hora_inicio = %d hora_fim = %d\n\n",
                                                                                                                                     ((( (*header)->current)->lista_disp)->last)->data,
                                                                                                                                     ((( (*header)->current)->lista_disp)->last)->hora_inicio,
                                                                                                                                     ((( (*header)->current)->lista_disp)->last)->hora_fim  ); 

                                    */
                                }

                                    
                            }else{
                                /*
                                printf("\ndata passada... %d\n", brokendown->tm_yday);
                                */
                            }

                            
                        }
                        
                        
                    }
                    
                    /* ja analisou esse dia de disponibilidade. volta para o inicio do laco
                    para tratar outro trecho da disponibilidade (se houver) */
                    
                   
                    
                }
                
            }
            
            
            /* Ja tratou a disponibilidade desse palestrante.*/
            
            elementos_para_tratar--;

            if( existe_disponibilidade_futura == 0){
                printf("\nAtencao! O palestrante %s nao possui disponibilidade em data futura!\n",( (*header)->current)->nome_pessoa );
            }


            /* Pode ir para o proximo palestrante (se houver) */
            /* Se chegou no fim da lista, deve ir para o inicio...*/

        if( elementos_para_tratar > 0){

            existe_disponibilidade_futura = 0; /* reset do flag para verificar a disponibilidade do proximo palestrante */

            
            if(  (*header)->current ==  (*header)->last ){
                
                if( Aponta_Inicio_ListaPalestrantes( header ) == 0 ){
                    printf("\nErro! Nao foi possivel apontar para o inicio da lista de palestrantes\n");

                    return -1;
                }
                    
            }else{
                    
                    if( Aponta_Proximo_ListaPalestrantes( header ) == 0){
                        printf("\nNao ha proximo palestrante a ser tratado\n");

                        return 0; /* nao eh um erro */

                    }

                }
        }
        



        }/* fim do while(elementos--) */
        
        if(erros){
            return -erros;
        }
        
        return 0;
    
}


int Eh_delimitador(char incognita){
    
 
    switch(incognita)
    {
        
        case ',':
        case '.':
        case ';':
        case ':':
    
            return 1;
            break;  

        default: 
            return 0;
    }
    
    return 0;
 
}
