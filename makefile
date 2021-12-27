.PHONY: all
CC = gcc
AR = ar
FLAGS= -Wall -g

all: graph 
graph: main.o graph.a
	$(CC) $(FLAGS) -o graph main.o graph.a
graph.a: graph.o
	$(AR) -rcs graph.a graph.o
main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c
graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c