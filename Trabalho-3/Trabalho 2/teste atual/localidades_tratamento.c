#include "localidades_tratamento.h"

void Pula_Espaco(FILE *arq)
{
    fseek(arq,(long int)(sizeof(char)),SEEK_CUR);
}

int pegaValor(FILE *arq)
{
	int i,j,retorno=0,multiplicando=1,aux=0,*valor;
	char c;

	for(i=0;((c = fgetc(arq))!='/')&&(c!=',')&&(c!=':')&&(c!='-')&&(c!='.')&&(c!=';')&&(c!=EOF);i++)
    {}
	fseek(arq,(long int)(-i-1)*sizeof(char),SEEK_CUR);
	valor=(int*)malloc(i+1*sizeof(int));

	for(j=0;j<i;j++)
	{
		valor[j]=fgetc(arq)-48;
	}
	for(j=i;j>0;j--)
	{
		aux=valor[j-1]*multiplicando;
		retorno+=aux;
		multiplicando*=10;
	}
	Pula_Espaco(arq);
	return retorno;
}

int Analisa_Bissexto(int ano)
{
    if ((ano%4 == 0 && ano%100 != 0)|| (ano%400 == 0))
    {
        return 1;
    }
    else
        return 0;
}

int Ultimo_Dia_Mes(int mes, int ano)
{
    switch(mes) /*calcula qual o ultimo dia do mes em questão*/
    {
    case 4:case 6:case 9:case 11:
        return 30;
        break;
        
    case 1:case 3:case 5:case 7:case 8:case 10:case 12:
        return 31;
        break;
        
    case 2:
        if(Analisa_Bissexto(ano) == 1)
        {
            return 29;
        }
        else
        {
            return 28;
        }
        break;
    }
    printf("\nInformacao nao esperada em Ultimo_Dia_Mes!\n");
    return -1;
}

int Formata_Dia(tipo_data_info *data)
{
    int aux;
    int bissexto;
    int dia;
    int mes;
    int ano;

    aux = 0;
    dia = data->dia;
    mes = data->mes;
    ano = data->ano;
    
    bissexto = Analisa_Bissexto(ano);
    switch(mes)
    {
    case 1:
        aux = 0;
        return (aux + dia);
    case 2:
        aux = 31;
        return (aux + dia);
    case 3:
        bissexto == 1 ? (aux = 60) : (aux = 59);
        return (aux + dia);
    case 4:
        bissexto == 1 ? (aux = 91) : (aux = 90);
        return (aux + dia);
    case 5:
        bissexto == 1 ? (aux = 121) : (aux = 120);
        return (aux + dia);
    case 6:
        bissexto == 1 ? (aux = 152) : (aux = 151);
        return (aux + dia);
    case 7:
        bissexto == 1 ? (aux = 182) : (aux = 181);
        return (aux + dia);
    case 8:
        bissexto == 1 ? (aux = 213) : (aux = 212);
        return (aux + dia);
    case 9:
        bissexto == 1 ? (aux = 244) : (aux = 243);
        return (aux + dia);
    case 10:
        bissexto == 1 ? (aux = 274) : (aux = 273);
        return (aux + dia);
    case 11:
        bissexto == 1 ? (aux = 305) : (aux = 304);
        return (aux + dia);
    case 12:
        bissexto == 1 ? (aux = 335) : (aux = 334);
        return (aux + dia);
    }
    return -1;
}

int Dia_Semana(tipo_data_info *data)
{
    int a;
    int b;
    int c;
    int d;
    int x;
    int ano;
    
    c = data->mes;
    x = data->dia;
    ano = data->ano;
    a = ano - 1900;
    b = a/4;
    d = x-1;
    
    if ((Analisa_Bissexto(ano) == 1)&&(x <= 60))
    {
        b--;
    }
    switch(c)
    {
    case 1:case 10:
        c = 0;
        break;
    case 2:case 3:case 11:
        c = 3;
        break;
    case 4:case 7:
        c = 6;
        break;
    case 5:
        c = 1;
        break;
    case 6:
        c = 4;
        break;
    case 8:
        c = 2;
        break;
    case 9:case 12:
        c = 5;
        break;
    }
    
    return ((a + b + c + d)%7);
}

int Numero_Semana(char *dia_semana)
{
    switch(dia_semana[0])  /*pega o numero correspondente ao dia */
    {                               /*da semana para comparacao na hora de expandir*/
    case 'S':case 's':
        if(dia_semana[2] == 'g')
        {
            return 0;
        }
        else 
        {
            if(dia_semana[2] == 'x')
            {
                return 4;
            }
            else
            {
                return 5;
            }
        }
        break;
    case 'T':case 't':
        return 1;
        break;
    case 'Q':case 'q':
        if(dia_semana[2] == 'a')
        {
            return 2;
        }
        else
        {
            return 3;
        }
        break;
    case 'D':case 'd':
        return 6;
        break;
    }
    printf("\nInformacao nao esperada em Numero_Semana!\n");
    return -1;
}

void Estende_Disponibilidade(tipo_disponibilidade_local* p1_disp, tipo_disponibilidade_local **pinicio_disp, tipo_data_info *data)
{
    int i; /*controla laco que um por um analisa quais dias sao iguais aos que devem ser expandidos*/
    int ano; /*recebe o ano da data analisado*/
    int aux_disp_semana; /*Ponteiro para auxiliar comparacao do dia a ser expandido, contem o dia da disp.*/
    int aux_dia_semana; /*Ponteiro para auxiliar comparacao do dia a ser expandido, contem o dia do mes analisado*/
    tipo_data_info *aux_data; /*copia as informacoes do no disp recebido para ser reproduzido pelos outros dias a serem expandidos*/
    tipo_disponibilidade_local *p1; /*ptr auxiliar para encadear a lista de disponibilidades*/
    
    
    aux_data = (tipo_data_info *)malloc(sizeof(tipo_data_info));
    ano = data->ano;
    
    aux_data->mes = data->mes;
    aux_data->ano = data->ano;
    aux_data->dia = 1;
    
    aux_disp_semana = Numero_Semana(p1_disp->dia_semana);
    
    
    i = Ultimo_Dia_Mes(data->mes,ano);
    while(aux_data->dia < i) /*caminha todos os dias do mes a partir do dia 0 expandindo para o dia da semana escolhido*/
    {
        aux_dia_semana = Dia_Semana(aux_data);
        
        if( aux_dia_semana == aux_disp_semana )
        {
            p1 = (tipo_disponibilidade_local*)malloc(sizeof(tipo_disponibilidade_local));
            strcpy(p1->dia_semana,p1_disp->dia_semana);
            p1->dia = Formata_Dia(aux_data);
            p1->inicio = p1_disp->inicio;
            p1->fim = p1_disp->fim;
            p1->duracao = p1_disp->duracao;
            p1->prox = (*pinicio_disp);
            (*pinicio_disp) = p1;
        }
        (aux_data->dia)++;
    }
}

tipo_local* Trata_Localidade(tipo_local *pinicio)
{
    char c;
    int i;
    int sair;
    tipo_data_info *data;
    FILE *arq;
    tipo_local *p1_local;
    tipo_disponibilidade_local *pinicio_disp;
    tipo_disponibilidade_local *p1_disp;

    p1_local = pinicio;

    while(p1_local)/*Enquanto houver local*/
    {
        pinicio_disp = NULL;
        sair = 0;
        arq = fopen("temp.txt","w+");

        (void) fwrite(p1_local->disponibilidade_bruta,1,strlen(p1_local->disponibilidade_bruta),arq);
        fputc('.',arq);
        fputc(EOF,arq);
        rewind(arq);

        while(!sair)/*Enquanto nao quebrar toda a disponibilidade bruta*/
        {
            p1_disp = (tipo_disponibilidade_local*)malloc(sizeof(tipo_disponibilidade_local));
            data = (tipo_data_info*)malloc(sizeof(tipo_data_info));
            
            for(i=0;(c = fgetc(arq))!=',';i++)
            {
                p1_disp->dia_semana[i] = c;
            }
            p1_disp->dia_semana[i] = '\0';
            Pula_Espaco(arq);

            data->dia = pegaValor(arq);
            data->mes = pegaValor(arq);
            data->ano = pegaValor(arq);
            p1_disp->dia = Formata_Dia(data);

            Pula_Espaco(arq);
            p1_disp->inicio = pegaValor(arq)*60;
            p1_disp->inicio += pegaValor(arq);
            p1_disp->fim = pegaValor(arq)*60;
            p1_disp->fim += pegaValor(arq);
            p1_disp->duracao = p1_disp->fim - p1_disp->inicio;

            
            if(data->dia == 0) /*se tiver que expandir*/
            {
                p1_disp->prox = NULL;
                Estende_Disponibilidade(p1_disp,&pinicio_disp,data);
                free(p1_disp);
            }
            else /*se nao tiver que expandir*/
            {
                p1_disp->prox = pinicio_disp;
                pinicio_disp = p1_disp;
            }
            if((c = fgetc(arq)) == EOF)
            {
                sair = 1;
            }
        }
        fclose(arq);
        p1_local->disponibilidade = pinicio_disp;
        p1_local = p1_local->prox;
    }
    return pinicio;
}