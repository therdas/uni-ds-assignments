CC = gcc
CPPFLAGS = -Wall -I include
VPATH = src include

all: graph.o dgraph.o

graph.o: graph.c graph.h list.o

dgraph.o: dgraph.c dgraph.h list.o
	$(CC) -c $< $(CPPFLAGS)

list.o: list.c list.h

.PHONY: clean
clean:
	rm -f *.o