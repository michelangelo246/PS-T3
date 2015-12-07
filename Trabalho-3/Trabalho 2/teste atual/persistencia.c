#include "persistencia.h"
#include "string.h"


#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


Calendario Monta_Calendario(void)
{	

	FILE* filepalestras = fopen("palestras.txt", "r");
	tipo_disponibilidade_local* d_aux = NULL;
	int inicio;
	int final;
	int i;

	ListaPalestras header_palestras = obter_ListaPalestras(filepalestras);
	TRANTE_cabecalho* header_palestrantes = obter_palestrantes( "palestrantes.txt" );
	tipo_local* header_locais = Le_Localidade();
	header_locais = Trata_Localidade(header_locais);
	tipo_local* localaux = header_locais;
	
		// INICIALIZA CALENDARIO
	Calendario c = Cria_Calendario();
	for(i = 1; i < 367; i++)
	{
		c->dias[i] = Cria_Data();
		c->dias[i]->encaixadas = Cria_ListaEventos();
	}

	Aponta_Inicio_ListaPalestras(header_palestras);
	do
	{
		Aponta_Inicio_ListaPalestrantes(&header_palestrantes);
		do
		{
			if(strcmp(header_palestras->current->p->responsavel, header_palestrantes->current->nome_pessoa ) == 0)
			{

				DISP_cabecalho* header_disp = header_palestrantes->current->lista_disp;
				if(!ListaDisponibilidades_Vazia(header_disp))
				{

					Aponta_Inicio_ListaDisponibilidades(&header_disp);
					do
					{	
						if(header_palestras->current->p->duracao_tratada <= (header_disp->current->hora_fim - header_disp->current->hora_inicio) )
						{
							while(header_locais)
							{
								d_aux = header_locais->disponibilidade;
								tipo_disponibilidade_local* aux = d_aux; //retornar ao começo da lista
								while(d_aux)
								{
									if(d_aux->duracao >= header_palestras->current->p->duracao_tratada)
									{	
										if(d_aux->dia == header_disp->current->data)
										{
											inicio = MAX(d_aux->inicio, header_disp->current->hora_inicio);
											final = MIN(d_aux->fim, header_disp->current->hora_fim);
											if((final - inicio) >= header_palestras->current->p->duracao_tratada)
											{

												Evento eaux = Cria_Evento();
												eaux->nome_palestra = 	strdup(header_palestras->current->p->nome_palestra);
												eaux->nome_palestrante = strdup(header_palestrantes->current->nome_pessoa);
												eaux->nome_local = strdup(header_locais->nome);
												eaux->comeco = inicio;
												eaux->duracao = final - inicio;
												Insere_Inicio_ListaEventos(c->dias[d_aux->dia]->encaixadas, eaux);
												if(!ListaPalestras_Vazia(header_palestras))	
													Remove_Corrente_ListaPalestras(header_palestras);
											}
										}
									}
									d_aux = d_aux->prox;
								}
								d_aux = aux;
								header_locais = header_locais->prox;
							}
						}
						header_locais = localaux;
						Aponta_Proximo_ListaDisponibilidades(&header_disp);
					}while(header_disp->current != header_disp->last);
				}

			}
			Aponta_Proximo_ListaPalestrantes(&header_palestrantes);
		}while(header_palestrantes->current != header_palestrantes->last);
		Aponta_Proximo_ListaPalestras(header_palestras);
	}
	while( header_palestras->current != header_palestras->last && !ListaPalestras_Vazia(header_palestras));

	return c;

}
