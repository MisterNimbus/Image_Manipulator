CC = g++
CFLAGS = -Wall -g


main: main.o pnm.o pixel.o
	$(CC) $(CFLAGS) -o main main.o pnm.o pixel.o
main.o: main.cpp pnm.h pixel.h
	$(CC) $(CFLAGS) -c main.cpp
pnm.o: pnm.h pixel.h

pixel.o: pixel.h