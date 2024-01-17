#!/bin/bash


g++ TXTWrite.cpp Date.cpp Operation.cpp RecuitSimule.cpp Parking.cpp Stay.cpp Read.cpp Solution.cpp RandomizeSubset.cpp  SelectiveMutationSubset.cpp Randomize.cpp MutateMinusOne.cpp NonAllocAndContact.cpp main.cpp -o main

./main

cd ..
python3 figureOperator.py
