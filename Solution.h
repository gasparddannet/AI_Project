#ifndef solution_h
#define solution_h

#include <vector>
#include <list>
#include "Operation.h"

using namespace std;

class Solution
{
    vector<int> solution;
    vector<int> numberOnPark; //numberOnPark[i] = number of Stays that use Parking i

public:
    Solution(vector<int> solution);
    
    Solution(const Solution & s);
    Solution & operator=(const Solution& s);
    
    vector<int> getSolution();
    void randomize(int sizeParking, vector<Operation> vectOperations);
    void initializeNOP(int sizeParkings);
    void computeNOP();
    void mutateMinusOne(int sizeParkings);
    void smartMutateMinusOne(int sizeParkings);
    void randomizeSubset(int i, int j, int sizeParkings);
    void blockReverse(int i,int j);
    void doubleFlip(int i1, int j1, int i2, int j2);
    void shuffleSubset(int i,int j);
    void rotateSubset(int i, int j);
    void selectiveMutationSubset(int i, int j, double mutationProbability, int sizeParkings);
};

#endif