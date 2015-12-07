#include "evento.h"

Evento Cria_Evento(void)
{
	return malloc(sizeof(struct evento));
}

void Destroi_Evento(Evento e)
{
	free(e);
}