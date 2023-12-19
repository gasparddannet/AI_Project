#ifndef solution_h
#define solution_h

#include <vector>
#include <list>
#include "Operation.h"
#include "Parking.h"

using namespace std;

class Solution
{
<<<<<<< HEAD
    vector<int> solution;
    vector<int> numberOnPark; //numberOnPark[i] = number of Stays that use Parking i

public:
    Solution(vector<int> solution);
=======
    vector<vector<int>> solution;

public:
    Solution(vector<vector<int>> solution);
>>>>>>> 80d00c0712eb6ef69ae4a8072cacd4d6b656db9f
    
    Solution(const Solution & s);
    Solution & operator=(const Solution& s);
    
<<<<<<< HEAD
    vector<int> getSolution();
    void randomize(int sizeParking, vector<Operation> vectOperations);
    void initializeNOP(int sizeParkings);
    void computeNOP();
    void mutateMinusOne(int sizeParkings, vector<Operation> vectOperations);
    void smartMutateMinusOne(int sizeParkings);
    void randomizeSubset(int i, int j, int sizeParkings);
    void blockReverse(int i,int j);
    void doubleFlip(int i1, int j1, int i2, int j2);
    void shuffleSubset(int i,int j);
    void rotateSubset(int i, int j);
    void selectiveMutationSubset(int i, int j, double mutationProbability, int sizeParkings);
    void NonAllocAndContact(int sizeParkings, vector<Operation> vectOperations, vector<Parking> vectParkings);
=======
    vector<vector<int>> getSolution();
    void randomize(vector<Operation> vectOperations);
    // void mutateMinusOne(int sizeParkings, vector<Operation> vectOperations);
    // void smartMutateMinusOne(int sizeParkings);
    // void randomizeSubset(int i, int j, int sizeParkings);
    // void blockReverse(int i,int j);
    // void doubleFlip(int i1, int j1, int i2, int j2);
    // void shuffleSubset(int i,int j);
    // void rotateSubset(int i, int j);
    // void selectiveMutationSubset(int i, int j, double mutationProbability, int sizeParkings);
    // void NonAllocAndContact(int sizeParkings, vector<Operation> vectOperations, vector<Parking> vectParkings);
>>>>>>> 80d00c0712eb6ef69ae4a8072cacd4d6b656db9f
};

#endif