# Variables to control Makefile operation
CC = g++
CFLAGS = -Wall -g

main: main.o Date.o Operation.o RecuitSimule.o Parking.o Stay.o Read.o Solution.o
	$(CC) $(CFLAGS) -o main main.o Date.o Operation.o RecuitSimule.o Parking.o Stay.o Read.o Solution.o
	
main.o: main.cpp Date.cpp Operation.cpp RecuitSimule.cpp Parking.cpp Stay.cpp Read.cpp Solution.cpp
	$(CC) $(CFLAGS) -c main.cpp
	
Date.o: Date.h

# Time.o: Time.h
Operation.o : Operation.h

RecuitSimule.o: RecuitSimule.h

Parking.o: Parking.h ParkNature.h

Stay.o: Stay.h BodyType.h Date.h Time.h CourrierCode.h

Read.o: Read.h Parking.h Stay.h

Solution.o: Solution.h 
