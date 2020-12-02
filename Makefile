CC=gcc
CFLAGS=-c -Wall
all:wordfreak

wordfreak: wordfreak.o tree.o
	$(CC) wordfreak.o tree.o -o wordfreak

wordfreak.o: wordfreak.c
	$(CC) $(CFLAGS) -c wordfreak.c

tree.o: tree.c
	$(CC) $(CFLAGS) -c tree.c
