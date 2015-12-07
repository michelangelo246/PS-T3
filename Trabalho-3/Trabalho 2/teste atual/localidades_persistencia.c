#include "localidades_persistencia.h"

void Imprime_Localidades(tipo_local* p2)
{
    //FILE *arq = fopen("arquivo_teste_locais.txt","w");
    tipo_disponibilidade_local *paux;
    tipo_local *p1;
    
    p1= p2;
    printf("\nACESSO E IMPRESSÃO DE TODOS OS CAMPOS DAS LOCALIDADES E SUAS DISPONIBILIDADES:\n");
    while(p1)
    {
        printf("\n-----------------------------------------------");
        printf("\nLocal: %s", p1->nome);
        printf("\nEndereco: %s", p1->endereco);
        printf("\nDisponibilidade Bruta: %s",p1->disponibilidade_bruta);
        printf("\nDisponibilidade tratada:\n");
        
        paux = p1->disponibilidade;
        while(paux)
        {
            printf("\n\tDia da semana: %s", paux->dia_semana);
            printf("\n\tDia do ano: %d", paux->dia);
            printf("\n\tInicio: %d", paux->inicio);
            printf("\n\tFim: %d", paux->fim);
            printf("\n\tDuracao: %d\n", paux->duracao);
            paux = paux->prox;
        }
        p1 = p1->prox;
    }
    printf("----------------------------------------------\n");
    
}

tipo_local* Pega_Localidade()
{
    tipo_local* p1;
    
    p1 = Le_Localidade();
    p1 = Trata_Localidade(p1);
    Imprime_Localidades(p1);
    
    return p1;
}