#include "MODULO_PALESTRAS/persistencia_palestras.h"

int main()
{
	ListaPalestras header_palestras = obter_ListaPalestras();

	int i = Quant_Elementos_ListaPalestras(header_palestras);
	while(i--)
	{
		Palestra paux = Remove_Inicio_ListaPalestras(header_palestras);
		printf("%d\n",paux->duracao_tratada );
	}
}