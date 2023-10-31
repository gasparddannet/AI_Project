# Variables to control Makefile operation
CC = g++
CFLAGS = -Wall -g

main: main.o Date.o Time.o RecuitSimule.o Parking.o Stay.o  
	$(CC) $(CFLAGS) -o main main.o Date.o Time.o RecuitSimule.o Parking.o Stay.o
	
main.o: main.cpp Date.cpp Time.cpp RecuitSimule.cpp Parking.cpp Stay.cpp
	$(CC) $(CFLAGS) -c main.cpp
	
Date.o: Date.h

Time.o: Time.h

RecuitSimule.o: RecuitSimule.h

Parking.o: Parking.h ParkNature.h

Stay.o: Stay.h BodyType.h Date.h Time.h CourrierCode.h
