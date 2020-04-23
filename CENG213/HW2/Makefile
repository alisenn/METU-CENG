CC=g++
CFLAGS=-c -ansi -Wall -pedantic-errors -std=c++11 -O0

all: indexer

indexer: main.o indexer.o indexnodedata.o termtreenodedata.o 
	$(CC) main.o indexer.o indexnodedata.o termtreenodedata.o -o indexer

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

indexer.o: Indexer.cpp Indexer.h
	$(CC) $(CFLAGS) Indexer.cpp -o indexer.o


indexnodedata.o: IndexNodeData.cpp IndexNodeData.h
	$(CC) $(CFLAGS) IndexNodeData.cpp -o indexnodedata.o

termtreenodedata.o: TermTreeNodeData.cpp TermTreeNodeData.h
	$(CC) $(CFLAGS) TermTreeNodeData.cpp -o termtreenodedata.o

clean:
	rm *o
	rm indexer
