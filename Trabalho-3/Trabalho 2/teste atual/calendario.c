#include "calendario.h"

Calendario Cria_Calendario(void)
{
	Calendario c =  malloc(sizeof(struct calendario));
}

void Destroi_Calendario(Calendario c)
{
	free(c);
}