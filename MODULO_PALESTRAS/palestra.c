#include "palestra.h"

Palestra Cria_Palestra(void)
{
    return malloc(sizeof(struct palestra));
}

void Destroi_Palestra(Palestra p)
{
    free(p);
}