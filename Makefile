CC=g++
CFLAGS=-c -Wall

main.exe: main.o diff.o
	$(CC) main.o diff.o -o main.exe

main.o: main.cpp Makefile
	$(CC) $(CFLAGS) main.cpp

BinTree.o: diff.cpp Makefile
	$(CC) $(CFLAGS) diff.cpp

.PHONY: run
run:
	./main.exe