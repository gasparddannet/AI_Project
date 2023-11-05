#ifndef solution_h
#define solution_h

#include "ParkSolution.h"
#include <vector>

using namespace std;

class Solution
{
    const int idStay;
    vector<ParkSolution> vectParkSolutions;

public:
    Solution(const int iS, vector<ParkSolution> vPS);
    vector<ParkSolution> getVectParkSolution();
};

#endif solution_h