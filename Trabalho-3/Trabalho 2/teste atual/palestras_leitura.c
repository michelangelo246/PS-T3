
#include "palestras_leitura.h"



/* A funcao le_palestrantes recebe o ponteiro para o arquivo de palestrantes, 
cria a lista dea palestrantes e retorna o ponteiro para essa lista.
Em caso de erro, retorna NULL */


/*  ---------------------------------------------------------------------------------------------------- */





ListaPalestras Le_palestras(FILE *arq_palestras){
    
    /* recebe o ponteiro para o arquivo de palestras, 
    cria a lista de palestras, 
    preenche a lista com os dados brutos
    e retorna o ponteiro para essa lista.
    Em caso de erro, retorna NULL */
        
    char buffer_nome[MAX_NOME_PALESTRA];
    char buffer_responsavel[MAX_NOME_RESPONSAVEL];
    char buffer_tema[MAX_TEMA];
    char buffer_local[MAX_LOCAL];
    char buffer_duracao[MAX_DUR_BRUTA];
   
    
    ListaPalestras header = Cria_ListaPalestras();

    
    while(!feof(arq_palestras)){
        
        
        fscanf(arq_palestras, "%*s "); /*ignora inicio da linha "Nome: "*/
        fscanf (arq_palestras,"%[^\n]", buffer_nome); 
         //copia o restante da linha do nome da palestra
        buffer_nome[strlen(buffer_nome)-1] = '\0'; /*apaga o ENTER (final da linha)*/
        
        
        fscanf(arq_palestras, "%*s "); /*ignora inicio da linha "Palestrante: "*/
        fscanf(arq_palestras,"%[^\n]", buffer_responsavel);
        //copia o restante da linha (nome do responsavel)
        buffer_responsavel[strlen(buffer_responsavel)-1] = '\0'; /*apaga o ENTER (final da linha)*/        
        
        fscanf(arq_palestras, "%*s "); /*ignora "Tema: "*/
        fscanf(arq_palestras,"%[^\n]", buffer_tema);
        //copia o restante da linha (tema da palestra)
        buffer_tema[strlen(buffer_tema)-1] = '\0'; /*apaga o ENTER (final da linha)*/         



        fscanf(arq_palestras, "%*s "); /*ignora"Duracao: "*/
        fscanf(arq_palestras,"%[^\n]", buffer_duracao);
        //copia o restante da linha (duracao da palestra)
        buffer_duracao[strlen(buffer_duracao)-1] = '\0'; /*apaga o ENTER (final da linha)*/  
            
        
        Palestra nova = Cria_Palestra();
        nova->nome_palestra = strdup(buffer_nome);
        nova->responsavel = strdup(buffer_responsavel);
        nova->tema = strdup(buffer_tema);
        nova->local = strdup(buffer_local);
        nova->duracao_bruta = strdup(buffer_duracao);
        nova->duracao_tratada = 0;
        
        
        Insere_Final_ListaPalestras(header, nova);
        
        /*(nova); /* Dou esse free porque esse endereco nao serah mais utilizado
                        note que a funcao de insercao faz um outro malloc, e nao dah 
                        free no endereco recebido como parametro */
    }
    
    
    return header;
    
}
