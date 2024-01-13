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
    Solution(vector<int> solution);
    
    Solution(const Solution & s);
    Solution & operator=(const Solution& s);
    
    vector<int> getSolution();
    void randomize(int sizeParking, vector<Operation> vectOperations);
    void initializeNOP(int sizeParkings);
    void computeNOP();
    void mutateMinusOne(int sizeParkings, vector<Operation> vectOperations);
    void smartMutateMinusOne(int sizeParkings);
    void randomizeSubset(int sizeParkings, vector<Operation> vectOperations);
    void blockReverse(int i,int j);
    void doubleFlip(int i1, int j1, int i2, int j2);
    void shuffleRandomSubset();
    void rotateSubset(int i, int j);
    void selectiveMutationSubset(int i, int j, double mutationProbability, int sizeParkings);
    void NonAllocAndContact(int sizeParkings, vector<Operation> vectOperations, vector<Parking> vectParkings);
};

#endif