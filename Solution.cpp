#include "Solution.h"

Solution::Solution(vector<int> solution):solution(solution) {}

vector<int> Solution::getSolution() {
    return solution;
}

//////////////////////////////////////////////////// OPERATORS //////////////////////////////////////////////
void Solution::replace(int sizeParkings) {
    for (i=0;i<solution.size();i++) {
        if solution[i] == -1 {
            solution[i] = rand() % sizeParkings
        }
    }
}

void Solution::randomize(int sizeParkings) {
    for (i=0;i<solution.size();i++) {
        solution[i] = rand() % sizeParkings
    }
}

//////////////////////////////////////////////////// OPERATORS //////////////////////////////////////////////
