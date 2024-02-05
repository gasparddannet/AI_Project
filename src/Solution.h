#ifndef solution_h
#define solution_h

#include <vector>
#include <list>
#include "Operation.h"
#include "Parking.h"

using namespace std;

class Solution
{
    vector<int> solution;
    vector<int> numberOnPark; //numberOnPark[i] = number of Stays that use Parking i

public:
    Solution();
    Solution(vector<int> solution);
    
    Solution(const Solution & s);
    Solution & operator=(const Solution& s);
    
    vector<int> getSolution();
    void setSolution(vector<int> &s);
    void changeSolutionI(int i,int k);
    int getSize();

};

#endif