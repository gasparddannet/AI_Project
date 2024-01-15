#include "Operateur.h"
#include "Operation.h"
#include "Solution.h"
#include <random>
#include <iostream>

class RandomizeSubset : public Operateur
{
private:

public:
    RandomizeSubset(int &sizeParkings, Solution &solution, const vector<Operation> &vectOperations, const vector<Parking> &vectParkings) : Operateur(sizeParkings,solution,vectOperations,vectParkings) {name = "RandomizeSubset" ;}
    Solution apply() override
    {
        std::random_device rd1;
        std::default_random_engine generator1(rd1());
        std::uniform_int_distribution<int> distribution1(0, solution.getSize() - 1);
        int i = distribution1(generator1);

        std::random_device rd2;
        std::default_random_engine generator2(rd2());
        std::uniform_int_distribution<int> distribution2(i, solution.getSize() - 1);
        int j = distribution2(generator2);

        std::random_device rd3;
        std::default_random_engine generator3(rd3());
        // {
        for (int k = i; k <= j; k++)
        {
            vector<int> compParkings = vectOperations[k].getCompParkings();
            std::uniform_int_distribution<int> distribution3(0, compParkings.size() - 1);
            solution.changeSolutionI(k, compParkings[distribution3(generator3)]);
        }
        return solution;
    }
};
