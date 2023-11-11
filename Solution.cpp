#include "Solution.h"
#include <stdlib.h> 
#include <ctime>
#include <iostream>

using namespace std ;
Solution::Solution(vector<int> solution):solution(solution) {}

vector<int> Solution::getSolution() {
    return solution;
}

//////////////////////////////////////////////////// OPERATORS //////////////////////////////////////////////
void Solution::replace(int sizeParkings) {
    for (int i=0;i<solution.size();i++) {
        if (solution[i] == -1) {
        solution[i] = rand() % sizeParkings;
        }
    }
}

void Solution::randomize(int sizeParkings) {
    srand((int) time(0));
    for (int i=0;i<solution.size();i++) {
        int r = rand() % sizeParkings;
        solution[i] = r;
        // cout << "random number : " << r;
        // cout << " | ";
    }
}

void Solution::blockReverse(int i, int j) {
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
//////////////////////////////////////////////////// OPERATORS //////////////////////////////////////////////
