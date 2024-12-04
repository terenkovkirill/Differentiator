CC=g++
CFLAGS=-c -Wall

main.exe: main.o RecursiveDescent.o diff.o
	$(CC) main.o RecursiveDescent.o diff.o -o main.exe

main.o: main.cpp Makefile
	$(CC) $(CFLAGS) main.cpp

RecursiveDescent.o: RecursiveDescent.cpp Makefile
	$(CC) $(CFLAGS) RecursiveDescent.cpp

diff.o: diff.cpp Makefile
	$(CC) $(CFLAGS) diff.cpp

.PHONY: run
run:
	./main.exe Expression.txt