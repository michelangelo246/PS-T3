all: palestrante limpa executa

palestrante: auxiliar.o leitura.o tempo.o tratamento.o persistencia.o main.o
	gcc -Wall auxiliar.o leitura.o tempo.o tratamento.o persistencia.o main.o -o PESSOA

auxiliar.o: TRANTE_auxiliar.c TRANTE_auxiliar.h
	gcc -Wall  -c TRANTE_auxiliar.c -o auxiliar.o

leitura.o: TRANTE_leitura.c TRANTE_leitura.h
	gcc -Wall  -c TRANTE_leitura.c -o leitura.o

tempo.o:  TRANTE_tempo.c TRANTE_tempo.h
	gcc -Wall  -c TRANTE_tempo.c -o tempo.o

tratamento.o: TRANTE_tratamento.c TRANTE_tratamento.h
	gcc -Wall  -c TRANTE_tratamento.c -o tratamento.o

persistencia.o: TRANTE_persistencia.c TRANTE_persistencia.h
	gcc -Wall  -c TRANTE_persistencia.c -o persistencia.o

main.o: teste_TRANTE.c
	gcc -Wall -c teste_TRANTE.c -o main.o


limpa:
	rm *.o

executa:
	./PESSOA palestrantes.txt

