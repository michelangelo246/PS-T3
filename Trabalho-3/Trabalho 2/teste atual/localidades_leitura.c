#include "localidades_leitura.h"

tipo_local* Inicia_Ponteiro(void)
{
    tipo_local* p1;
    
    p1 = (tipo_local*)malloc(sizeof(tipo_local));
    p1->nome[0] = '\0';
    p1->endereco[0] = '\0';
    p1->disponibilidade_bruta[0] = '\0';
    p1->disponibilidade = NULL;
    p1->prox = NULL;
    
    return p1;
}

void Le_Nome(FILE *arq,tipo_local **p1)
{
    char c; /*Caractere auxiliar para leitura do arquivo de localidades*/
    int i; /*auxiliar de contagem*/

    fseek(arq,(long int)(6*sizeof(char)),SEEK_CUR);
    for(i=0;((c = fgetc(arq))!='\n');i++)
    {
        (*p1)->nome[i] = c;
    }
    (*p1)->nome[i] = '\0';
}

void Le_Endereco(FILE *arq,tipo_local **p1)
{
    char c; /*Caractere auxiliar para leitura do arquivo de localidades*/
    int i; /*auxiliar de contagem*/

    fseek(arq,(long int)(10*sizeof(char)),SEEK_CUR);
    for(i=0;((c = fgetc(arq))!='\n');i++)
    {
        (*p1)->endereco[i] = c;
    }
    (*p1)->endereco[i] = '\0';
}

void Le_Disponibilidade_Bruta(FILE *arq,tipo_local **p1,int *sair)
{
    char c; /*Caractere auxiliar para leitura do arquivo de localidades*/
    int i; /*auxiliar de contagem*/

    fseek(arq,(long int)(17*sizeof(char)),SEEK_CUR);
    for(i=0;(((c = fgetc(arq))!='\n')&&(c != '\0')&&(c != EOF));i++)
    {
        (*p1)->disponibilidade_bruta[i] = c;
    }
    (*p1)->disponibilidade_bruta[i] = '\0';

    if((c == '\0')||(c == EOF))
    {
        (*sair) = 1;
    }

    (*p1)->disponibilidade = NULL;
}   


tipo_local* Le_Localidade(void)
{

    FILE *arq; /*Ponteiro para o arquivo de localidades*/
    tipo_local *pinicio; /*ponteiro para o inicio da lista de localidades*/
    tipo_local *p1; /*ponteiro auxiliar para alocacao da lista de localidades*/
    int sair; /*controle do loop de aloca��o principal*/
    sair = 0;
    pinicio = NULL;
    arq = fopen("arquivo_local.txt","r");
    if(!arq)
    {
        printf("erro ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }

    while(!sair)
    {
        p1 = Inicia_Ponteiro();
        Le_Nome(arq,&p1);
        Le_Endereco(arq,&p1);
        Le_Disponibilidade_Bruta(arq,&p1,&sair);

        p1->prox = pinicio;
        pinicio = p1;
    }
    return pinicio;
}
