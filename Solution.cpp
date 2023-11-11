#include "Solution.h"
#include <stdlib.h> 
#include <algorithm>  
#include <cstdlib>    
#include <ctime>
#include <random>
#include <iostream>

using namespace std ;
Solution::Solution(vector<int> solution):solution(solution) {}

vector<int> Solution::getSolution() {
    return solution;
}

// Number of Stays on each Parking initialized to 0
void Solution::initializeNOP(int sizeParkings){ 
    numberOnPark.assign(sizeParkings,0);
}

// We compute the real value of numberOnPark
void Solution::computeNOP() { 
    for (int i=0;solution.size();i++) {
        int iPark = solution[i];
        if (iPark != -1) {
            numberOnPark[iPark]++;
        }
    }
}

void Solution::randomize(int sizeParkings) {
    srand((int) time(0));
    for (int i=0; i<solution.size(); i++) {
        solution[i] = rand() % sizeParkings;
    }
}

//////////////////////////////////////////////////// OPERATORS //////////////////////////////////////////////

// Replace elements in the solution with random Parking assignment if they don't have one
void Solution::mutateMinusOne(int sizeParkings) {
    srand(time(NULL));
    for (int i=0;i<solution.size();i++) {
        if (solution[i] == -1) {
        solution[i] = rand() % sizeParkings;
        }
    }
}

// Replace elements in the solution with less occupied Parking assignment if they don't have one
void Solution::smartMutateMinusOne(int sizeParkings) {
    initializeNOP(sizeParkings);
    computeNOP();
    for (int i=0;i<solution.size();i++) {
        if (solution[i] == -1) {
            int iLessOccupiedPark = distance(numberOnPark.begin(), min_element(numberOnPark.begin(), numberOnPark.end()));
            solution[i] = iLessOccupiedPark;
            numberOnPark[i]++;
        }
    }
}


// Randomize elements in the solution, from index i to j
void Solution::randomizeSubset(int i, int j, int sizeParkings) {
    srand((int)time(0));
    if (i >= 0 && i < solution.size() && j >= 0 && j < solution.size() && i < j) {
        for (int k = i; k <= j; k++) {
            solution[k] = rand() % sizeParkings;
        }
    }
    // else std::cout << "erreur" << std::endl;
}

//Perform block reversal on elements in the solution, from index i to j
void Solution::blockReverse(int i, int j) {
    if (i >= 0 && i < solution.size() && j >= 0 && j < solution.size() && i < j) {
        int a = i ;
        int b = j;
        while(a<=b) {
            int vala=solution[a];
            solution[a] = solution[b];
            solution[b] = vala;
            a++;
            b--;
        }
    }
}

void Solution::doubleFlip(int i1, int j1, int i2, int j2) {
    blockReverse(i1, j1);
    blockReverse(i2, j2);
}

// Shuffle a subset of elements within the solution.
void Solution::shuffleSubset(int i, int j) {
    if (i >= 0 && i < solution.size() && j >= 0 && j < solution.size() && i < j) {
        vector<int> subset(solution.begin() + i, solution.begin() + j + 1);
        shuffle(subset.begin(), subset.end(), default_random_engine(std::time(0)));
        copy(subset.begin(), subset.end(), solution.begin() + i);
    }
}

// Rotate a subset of elements within the solution
void Solution::rotateSubset(int i, int j) {
    if (i >= 0 && i < solution.size() && j >= 0 && j < solution.size() && i < j) {
        std::rotate(solution.begin() + i, solution.begin() + i + 1, solution.begin() + j + 1);
    }
}

// Mutate a subset of elements based on a probability.
void Solution::selectiveMutationSubset(int i, int j, double mutationProbability, int sizeParkings) {
    if (i >= 0 && i < solution.size() && j >= 0 && j < solution.size() && i < j) {
        for (int i = i; i <= j; ++i) {
            double randValue = static_cast<double>(rand()) / RAND_MAX;
            if (randValue < mutationProbability) {
                solution[i] = rand() % sizeParkings;
            }
        }
    }
}

//////////////////////////////////////////////////// OPERATORS //////////////////////////////////////////////
