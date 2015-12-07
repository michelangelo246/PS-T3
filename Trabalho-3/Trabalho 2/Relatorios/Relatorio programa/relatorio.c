#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limpatela()
{
	#ifdef __linux__ 
    system("clear");
	#elif _WIN32
	system("cls");
	#else
	printf("SO nao reconhecido, mudar codigo fonte da system");
	#endif
}

char *inputString(FILE* arq, size_t tam)
{
    char *str;
    int ch;
    size_t comprimento = 0;
    str = realloc(NULL, sizeof(char)*tam);
    if(!str)
    {
    	return str;
    }
    while(EOF!=(ch=fgetc(arq)) && ch != '\n')
    {
        str[comprimento++] = ch;
        if(comprimento == tam)
        {
            str = realloc(str, sizeof(char)*(tam+=16));
            if(!str)
            {
            	return str;
            }
        }
    }
    str[comprimento++]='\0';

    return realloc(str, sizeof(char)*comprimento);
}
void pega_data(FILE* arq)
{
	int dia,mes;
	limpatela();
	printf("Informe o dia (ex:07): ");
	scanf("%d",&dia);getchar();
	printf("Informe o mes (ex:09): ");
	scanf("%d",&mes);getchar();
	fprintf(arq, "| %d/", dia);
	fprintf(arq, "%d |", mes);
}
void pega_horas(FILE* arq)
{
	int horas;
	limpatela();
	printf("Informe as horas trabalhadas: ");
	scanf("%d",&horas);getchar();
	fprintf(arq, "        ~%d          |", horas);
}
void pega_tarefa(FILE* arq)
{
	char *tarefa;
	limpatela();
	printf("Informe o tipo da tarefa: ");
	tarefa = inputString(stdin, 10);
	fprintf(arq, "  %s\n", tarefa);
}
void pega_descricao(FILE* arq)
{
	char *descricao;
	limpatela();
	printf("Informe a descricao da tarefa realizada: \n");
	descricao = inputString(stdin, 10);
	fprintf(arq, "|               Descricao da tarefa                      |\n");
	fprintf(arq, ">%s\n", descricao);
	fprintf(arq, "----------------------------------------------------------\n");
}

int main()
{
	FILE *arq;

	arq = fopen("relatorio.txt","a+");
	if(!arq)
	{
		printf("erro ao abrir o arquivo");
		return -1;
	}

	fprintf(arq, "\n| Data	|  Horas Trabalhadas |	       Tipo Tarefa       |\n");
	pega_data(arq);
	pega_horas(arq);
	pega_tarefa(arq);
	pega_descricao(arq);

	fclose(arq);
	return 0;	
}