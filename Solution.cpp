#include "Solution.h"
#include <stdlib.h> 
#include <time.h>   /* time */

using namespace std ;
Solution::Solution(vector<int> solution):solution(solution) {}

vector<int> Solution::getSolution() {
    return solution;
}

//////////////////////////////////////////////////// OPERATORS //////////////////////////////////////////////
void Solution::replace(int sizeParkings) {
    srand(time(NULL));
    for (int i=0;i<solution.size();i++) {
        if (solution[i] == -1) {
            solution[i] = rand() % sizeParkings;
        }
    }
}

void Solution::randomize(int sizeParkings) {
    for (int i=0;i<solution.size();i++) {
        solution[i] = rand() % sizeParkings;
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
