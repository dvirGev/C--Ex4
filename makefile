.PHONY: all clean
CC = gcc
AR = ar
FLAGS= -Wall -Werror -g
all: graph 
graph: main.o graph.a
	$(CC) $(FLAGS) -o graph main.o graph.a
graph.a: graph.o Dijkstra.o TSP.o
	$(AR) -rcs graph.a graph.o Dijkstra.o TSP.o
main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c
graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c
Dijkstra.o: Dijkstra.c graph.h
	$(CC) $(FLAGS) -c Dijkstra.c
TSP.o: TSP.c graph.h
	$(CC) $(FLAGS) -c TSP.c
clean:
	rm -f *.o *.a graph