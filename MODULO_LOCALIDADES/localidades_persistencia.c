#include "localidades_persistencia.h"

void Imprime_Localidades(tipo_local* p1)
{
    FILE *arq = fopen("arquivo_teste_locais.txt","w");
    tipo_disponibilidade_local *paux;
    
    while(p1)
    {
        fprintf(arq,"\n-----------------------------------------------");
        fprintf(arq,"\nLocal: %s", p1->nome);
        fprintf(arq,"\nEndereco: %s", p1->endereco);
        fprintf(arq,"\nDisponibilidade Bruta: %s",p1->disponibilidade_bruta);
        fprintf(arq,"\nDisponibilidade tratada:\n");
        
        paux = p1->disponibilidade;
        while(paux)
        {
            fprintf(arq,"\n\tDia da semana: %s", paux->dia_semana);
            fprintf(arq,"\n\tDia do ano: %d", paux->dia);
            fprintf(arq,"\n\tInicio: %d", paux->inicio);
            fprintf(arq,"\n\tFim: %d", paux->fim);
            fprintf(arq,"\n\tDuracao: %d\n", paux->duracao);
            paux = paux->prox;
        }
        p1 = p1->prox;
    }
    fprintf(arq,"----------------------------------------------\n");
    
    fclose(arq);
}

tipo_local* Pega_Localidade()
{
    tipo_local* p1;
    
    p1 = Le_Localidade();
    p1 = Trata_Localidade(p1);
    Imprime_Localidades(p1);
    
    return p1;
}