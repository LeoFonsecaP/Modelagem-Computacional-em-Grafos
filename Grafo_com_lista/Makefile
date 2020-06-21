run: teste
	./teste

teste: all

all: main.o grafo_com_lista.o lista.o fila.o
	gcc main.o grafo_com_lista.o lista.o fila.o -o teste
	
main.o: 
	gcc -c main.c

grafo_com_matriz.o:
	gcc -c grafo_com_lista.c

lista.o:
	gcc -c lista.c

fila.o:
	gcc -c fila.c
clean:
	rm -rf main .o
