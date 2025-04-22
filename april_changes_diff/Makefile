CC = g++
CFLAGS = -Wall -g
LDFLAGS = -g
DOT = dot
DOTFLAGS = -Tpng

.PHONY: all
all: clean_before_built main.exe 

clean_before_built:
	@$(MAKE) clean

main.exe: main.o ExpressionTree.o diff.o
	$(CC) main.o ExpressionTree.o diff.o $(LDFLAGS) -o main.exe

main.o: main.cpp ExpressionTree.h Makefile
	$(CC) $(CFLAGS) -c main.cpp

ExpressionTree.o: ExpressionTree.cpp ExpressionTree.h Makefile
	$(CC) $(CFLAGS) -c ExpressionTree.cpp

diff.o: diff.cpp ExpressionTree.h Makefile
	$(CC) $(CFLAGS) -c diff.cpp

.PHONY: run clean 

run: main.exe 
	./main.exe && $(DOT) $(DOTFLAGS) ExpressionTree.dot -o ExpressionTree.png && $(DOT) $(DOTFLAGS) TreePicture.dot -o TreePicture.png

clean:
	rm -f *.o main.exe ExpressionTree.png ExpressionTree.dot TreePicture.png TreePicture.dot Log.txt