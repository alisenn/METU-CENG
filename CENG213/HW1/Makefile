CC=g++
CFLAGS=-c -ansi -Wall -pedantic-errors -O0

all: linkedlist polynomial

polynomial: main_polynomial.o term.o polynomial.o
	$(CC) main_polynomial.o term.o polynomial.o -o polynomial

linkedlist: main_linkedlist.o
	$(CC) main_linkedlist.o -o linkedlist

main_polynomial.o: main_polynomial.cpp
	$(CC) $(CFLAGS) main_polynomial.cpp -o main_polynomial.o

main_linkedlist.o: main_linkedlist.cpp
	$(CC) $(CFLAGS) main_linkedlist.cpp -o main_linkedlist.o

term.o: Term.cpp Term.hpp
	$(CC) $(CFLAGS) Term.cpp -o term.o

polynomial.o: Polynomial.cpp Polynomial.hpp LinkedList.hpp Node.hpp Term.hpp
	$(CC) $(CFLAGS) Polynomial.cpp -o polynomial.o

clean:
	rm *o
	rm linkedlist
	rm polynomial
