#include "persistencia.h"

int main()
{
	FILE* fp = fopen("saida.txt", "w");
	if(fp)
	{

		Calendario c = Monta_Calendario();
		for(int i = 1; i < 367; i++)
		{
			fprintf(fp,"Dia %d\n",i);
			Aponta_Inicio_ListaEventos(c->dias[i]->encaixadas);
			do
			{
				Evento eaux = Cria_Evento();

				int j = 1;
				if(!ListaEventos_Vazia(c->dias[i]->encaixadas))
				{
						
					eaux = Remove_Inicio_ListaEventos(c->dias[i]->encaixadas);
						
					fprintf(fp, "\t Evento %d",j);
					fprintf(fp, "\tPalestra: %s\n",eaux->nome_palestra);
					fprintf(fp, "\tPalestrante: %s\n",eaux->nome_palestrante);
					fprintf(fp, "\tLocal: %s\n",eaux->nome_local);
					fprintf(fp, "\tComeço: %d:%d Término: %d:%d\n",eaux->comeco/60,
					 eaux->comeco%60,
					 (eaux->comeco + eaux->duracao)/60, (eaux->comeco + eaux->duracao)%60);

					j++;
					Aponta_Proximo_ListaEventos(c->dias[i]->encaixadas);
				}
			}
			while(c->dias[i]->encaixadas->current != c->dias[i]->encaixadas->last);
			
		}
	}
	return 0;
}