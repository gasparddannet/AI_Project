# Variables to control Makefile operation
CC = g++
CFLAGS = -Wall -g

main: main.o Date.o Operation.o RecuitSimule.o Parking.o Stay.o Read.o Solution.o TXTWrite.o Randomize.o RandomizeSubset.o NonAllocAndContact.o SelectiveMutationSubset.o MutateMinusOne.o
	$(CC) $(CFLAGS) -o main main.o Date.o Operation.o RecuitSimule.o Parking.o Stay.o Read.o Solution.o TXTWrite.o
	
main.o: main.cpp Date.cpp Operation.cpp RecuitSimule.cpp Parking.cpp Stay.cpp Read.cpp Solution.cpp TXTWrite.cpp Randomize.cpp RandomizeSubset.cpp NonAllocAndContact.cpp SelectiveMutationSubset.cpp MutateMinusOne.cpp
	$(CC) $(CFLAGS) -c main.cpp
	
Date.o: Date.h

Operation.o : Operation.h

RecuitSimule.o: RecuitSimule.h

Parking.o: Parking.h ParkNature.h

Stay.o: Stay.h BodyType.h Date.h CourrierCode.h

Read.o: Read.h Parking.h Stay.h

Solution.o: Solution.h 

TXTWrite.o : TXTWrite.h

# Randomize.o : Randomize.cpp

# RandomizeSubset.o : RandomizeSubset.cpp

# NonAllocAndContact.o : NonAllocAndContact.cpp

clean:
	rm *.o
	
run:
	./main && \
	cd .. ; python3 figureOperator.py

