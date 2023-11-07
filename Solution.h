#ifndef solution_h
#define solution_h

#include "Parking.h"
#include <vector>

using namespace std;

class Solution
{
    vector<Parking> solution;

public:
    Solution(vector<Parking> solution);
    vector<Parking> getSolution();
};

#endif