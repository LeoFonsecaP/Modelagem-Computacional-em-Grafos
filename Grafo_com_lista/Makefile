run: teste
	./teste

all: main.o grafo_com_lista.o
	gcc main.o grafo_com_lista.o -o teste
	
main.o: 
	gcc -c main.c

grafo_com_matriz.o:
	gcc -c grafo_com_lista.c

clean:
	rm -rf main .o
