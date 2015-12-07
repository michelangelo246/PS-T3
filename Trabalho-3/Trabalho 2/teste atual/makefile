all: programa limpa

programa: main.o evento.o listaeventos.o persistencia.o calendario.o data.o localidades_tratamento.o localidades_leitura.o localidades_persistencia.o TRANTE_auxiliar.o TRANTE_leitura.o TRANTE_persistencia.o TRANTE_tempo.o TRANTE_tratamento.o listapalestras.o palestra.o palestras_leitura.o persistencia_palestras.o tratapalestras.o
	gcc -g main.o evento.o listaeventos.o persistencia.o calendario.o data.o localidades_tratamento.o localidades_leitura.o localidades_persistencia.o TRANTE_auxiliar.o TRANTE_leitura.o TRANTE_persistencia.o TRANTE_tempo.o TRANTE_tratamento.o listapalestras.o palestra.o palestras_leitura.o persistencia_palestras.o tratapalestras.o -o programa.exe -std=c99
evento.o: evento.c
	gcc -c -g  evento.c
listaeventos.o: listaeventos.c
	gcc -c -g listaeventos.c listaeventos.h
persistencia.o: persistencia.c
	gcc -c -g persistencia.c -std=c99 persistencia.h
calendario.o: calendario.c
	gcc -c -g calendario.c calendario.h
data.o: data.c
	gcc -c -g data.c data.h
lista_palestras.o: lista_palestras.c
	gcc -c -g lista_palestras.c lista_palestras.h
localidades_leitura.o: localidades_leitura.c
	gcc -c -g localidades_leitura.c localidades_leitura.h
localidades_persistencia.o: localidades_persistencia.c
	gcc -c -g localidades_persistencia.c localidades_tratamento.h
localidades_tratamento.o: localidades_tratamento.c
	gcc -c -g localidades_tratamento.c localidades_tratamento.h
palestra.o: palestra.c
	gcc -c -g palestra.c palestra.h
palestras_leitura.o: palestras_leitura.c
	gcc -c -g palestras_leitura.c palestras_leitura.h
persistencia_palestras.o: persistencia_palestras.c
	gcc -c -g persistencia_palestras.c persistencia_palestras.h
TRANTE_auxiliar.o: TRANTE_auxiliar.c
	gcc -c -g TRANTE_auxiliar.c TRANTE_auxiliar.h
TRANTE_leitura.o: TRANTE_leitura.c
	gcc -c -g TRANTE_leitura.c TRANTE_leitura.h
TRANTE_persistencia.o: TRANTE_persistencia.c
	gcc -c -g TRANTE_persistencia.c TRANTE_persistencia.h
TRANTE_tempo.o: TRANTE_tempo.c
	gcc -c -g TRANTE_tempo.c TRANTE_tempo.h
TRANTE_tratamento.o: TRANTE_tratamento.c
	gcc -c -g TRANTE_tratamento.c TRANTE_tratamento.h
main.o: main.c
	gcc -c -g main.c -std=c99
limpa:
	rm *.o
	rm *.gch
