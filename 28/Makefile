all: main
	./main

main: main.c binarysearch.o
	gcc -Wall -Wextra -pedantic -o main main.c binarysearch.o

binarysearch.o: binarysearch.c
	gcc -Wall -Wextra -pedantic -c -o binarysearch.o binarysearch.c
