
#include "tratapalestras.h"
#include "TRANTE_tratamento.h"








/* ================================================================================================================ */



int TrataListaPalestras(ListaPalestras header){
    
    
    /* Recebe ponteiro para cabecalho da lista de palestras
        trata os respectivos dados
        retorna 0 em caso de sucesso
        retorna numero negativo em caso de erro */
    printf("1\n");
    if(ListaPalestras_Vazia(header)){
        printf("\nRecebida lista de paletras vazia para tratamento de disponibilidade bruta\n");
        getchar();
        return -1;
    }
    int elementos = Quant_Elementos_ListaPalestras(header);
    
    /* Lidar com maiusuculas e minusculas */
    if( LidarMaiusculas(header) < 0 ){
        return -1;
    }
    
    /* Lidar com duracao bruta */
    if( ConverteDuracaoBruta(header) < 0 ){
        return -2;
    }
    
    return 0;
    
    
}




int LidarMaiusculas(ListaPalestras header){
    
    /* Nessa primeira especificacao, nada foi definido para o tratamento de 
    maiusculas/minusculas. Entao, por enquanto, essa funcao nao faz nada... */
    
    
    return 0;
    
}





int ConverteDuracaoBruta(ListaPalestras header){
    
    int elementos = Quant_Elementos_ListaPalestras(header);

    if(ListaPalestras_Vazia(header)){
        printf("\nRecebida lista de paletras vazia para tratamento de duracao bruta\n");
        getchar();
        return -1;
        
    }   

    
    char buffer_horas[MAX_DUR_BRUTA];
    char buffer_minutos[MAX_DUR_BRUTA];
    int ind_bruta, ind_buffer_hora, ind_buffer_minuto;
    
    int erros=0;
    
    while(elementos--){ /* enquanto houver elemento para tratar... */
        
        
        ind_bruta=0; /* indice para percorrer  campo de duracao bruta */
        
        
        ind_buffer_hora = 0; /* indice para o buffer de horas */
        while( header->current->p->duracao_bruta[ind_bruta] ){ /* enquanto houver caractere para ler... */
            
            if(  !isdigit( header->current->p->duracao_bruta[ind_bruta] ) ){
                /* se encontrar algo que nao seja digito: 
                    incrementa o indice de nome (para ler minutos) e sai do laco */
                ind_bruta++;
                break;
                
            }else{
                /* se encontrar digito: copia para buffer de horas  */
                buffer_horas[ind_buffer_hora] = header->current->p->duracao_bruta[ind_bruta];
                ind_bruta++;
                ind_buffer_hora++;
            }
            
        }
        /* faco o fechamento do buffer de horas */
        buffer_horas[ind_buffer_hora] = '\0';
        
        ind_buffer_minuto=0; /* indice para o buffer de minutos*/
        while( header->current->p->duracao_bruta[ind_bruta] ){
            
            if(  !isdigit( header->current->p->duracao_bruta[ind_bruta] ) ){
                /* se encontrar algo que nao seja digito, nao ha mais nada para ler: sai do laco */
                break;
                
            }else{
                /* se encontrar digito: copia para buffer de minutos  */
                buffer_minutos[ind_buffer_minuto] = header->current->p->duracao_bruta[ind_bruta];
                ind_bruta++;
                ind_buffer_minuto++;
                
            }
        }
        /* faco o fechamento do buffer de minutos */
        buffer_minutos[ind_buffer_minuto] = '\0';
        
        header->current->p->duracao_tratada = atoi(buffer_minutos) + 60*(atoi(buffer_horas));   
        
        if( !(header->current->p->duracao_tratada) ){
            /* se a duracao for nula, temos um erro... */
            printf("\nERRO! No tratamento da duracao da palestra %s retornou: %d minutos\n", header->current->p->nome_palestra, header->current->p->duracao_tratada );
            getchar();
            erros++; /* registra o erro e continua o tratamento.. */
            
        }
        
        /* Ja tratou esse elemento. Entao pode ir para o proximo elemento */
        /* Se chegou no fim, deve ir para o inicio...*/
        if( header->current == header->last ){
            header->current = header->first; 
            
        }else{
            Aponta_Proximo_ListaPalestras(header)   ;
        }
        
    }
    
    if(erros){
        return -erros;
    }
    
    return 0;
}