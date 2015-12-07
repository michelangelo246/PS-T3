#include "persistencia.h"

int main()
{
	FILE* fp = fopen("saida.txt", "w");
	if(fp)
	{

		Calendario c = Monta_Calendario();
		for(int i = 1; i < 367; i++)
		{
			printf("Dia %d\n",i);
			while(!ListaEventos_Vazia(c->dias[i]->encaixadas))
			{
				int j = 1;
				Evento eaux = Remove_Inicio_ListaEventos(c->dias[i]->encaixadas);
				fprintf(fp, "\t Evento %d",j);
				fprintf(fp, "\tPalestra: %s\n",eaux->nome_palestra);
				fprintf(fp, "\tPalestrante: %s\n",eaux->nome_palestrante);
				fprintf(fp, "\tLocal: %s\n",eaux->nome_local);
				fprintf(fp, "\tComeço: %d:%d Término: %d:%d\n",eaux->comeco/60,
				 eaux->comeco%60,
				 (eaux->comeco + eaux->duracao)/60, (eaux->comeco + eaux->duracao)%60);

				j++;

			}
			
		}
	}
	return 0;	
}