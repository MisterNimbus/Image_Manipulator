CC = g++
CFLAGS = -Wall -g

all: main
main: main.o pnm.o ColorSphere.o
	$(CC) $(CFLAGS) -o main main.o pnm.o ColorSphere.o
main.o: main.cpp pnm.o ColorSphere.o
	$(CC) $(CFLAGS) -c main.cpp
pnm.o: pnm.cpp pnm.h
	$(CC) $(CFLAGS) -c pnm.cpp
ColorSphere.o: ColorSphere.cpp ColorSphere.h
	$(CC) $(CFLAGS) -c ColorSphere.cpp

clean:
	rm -rf *.o main.exe *.ppm *.pbm *.pgm *Output.png *Output.gif *Output*
