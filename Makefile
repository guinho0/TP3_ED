# makefile

all: main

main: main.o hospital.o
	gcc -o main main.o hospital.o

main.o: main.c hospital.h
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic -std=gnu11

hospital.o: hospital.c hospital.h
	gcc -o hospital.o hospital.c -c -W -Wall -ansi -pedantic -std=gnu11

clean:
	rm -rf *.o *~ main