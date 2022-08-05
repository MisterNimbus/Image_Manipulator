CC = g++
CFLAGS = -Wall -g

all: main
main: main.o pnm.o
	$(CC) $(CFLAGS) -o main main.o pnm.o
main.o: main.cpp pnm.o
	$(CC) $(CFLAGS) -c main.cpp
pnm.o: pnm.cpp pnm.h
	$(CC) $(CFLAGS) -c pnm.cpp
clean:
	rm -rf *.o main.exe *.ppm *.pbm *.pgm *Output.png
