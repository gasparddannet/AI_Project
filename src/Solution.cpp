#include "Solution.h"
#include <stdlib.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>

using namespace std;
Solution::Solution() : solution({}) {}
Solution::Solution(vector<int> solution) : solution(solution) {}

Solution::Solution(const Solution &s)
{
    operator=(s);
}

Solution &Solution::operator=(const Solution &s)
{
    if (this != &s) // Avoid self-assignment
    {
        this->solution.resize(s.solution.size());
        this->numberOnPark.resize(s.numberOnPark.size());

        for (int i = 0; i < s.solution.size(); i++)
        {
            this->solution[i] = s.solution[i];
        }
        for (int i = 0; i < s.numberOnPark.size(); i++)
        {
            this->numberOnPark[i] = s.numberOnPark[i];
        }
    }
    return *this;
}

vector<int> Solution::getSolution()
{
    return solution;
}

void Solution::setSolution(vector<int> &s) {
    solution=s;
}

void Solution::changeSolutionI(int i, int k) {
    solution[i]=k;
}

int Solution::getSize() {
    return solution.size();
}



