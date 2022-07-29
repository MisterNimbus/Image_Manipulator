CC = g++
CFLAGS = -Wall -g

all: main
main: main.o pnm.o pixel.o
	$(CC) $(CFLAGS) -o main main.o pnm.o pixel.o
main.o: main.cpp pnm.o pixel.o
	$(CC) $(CFLAGS) -c main.cpp
pnm.o: pnm.cpp pnm.h
	$(CC) $(CFLAGS) -c pnm.cpp
pixel.o: pixel.cpp pixel.h
	$(CC) $(CFLAGS) -c pixel.cpp
clean:
	rm -rf *.o main.exe
