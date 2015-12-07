#ifndef EVENTO_H
#define EVENTO_H
#include <stdlib.h>

struct evento
{
	char* nome_palestra;
	char* nome_palestrante;
	char* nome_local;
	int comeco;
	int duracao;

};

typedef struct evento* Evento;

Evento Cria_Evento();

void Destroi_Evento(Evento e);


#endif