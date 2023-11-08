#ifndef solution_h
#define solution_h

#include <vector>

using namespace std;

class Solution
{
    vector<int> solution;

public:
    Solution(vector<int> solution);
    vector<int> getSolution();
    void replace(int sizeParkings);
    void randomize(int sizeParkings);
    void blockReverse(int i,int j);
};

#endif