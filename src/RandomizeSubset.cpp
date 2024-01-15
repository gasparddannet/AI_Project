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
    Solution apply(double T) override
    {
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<int> distribution1(0, solution.getSize() - 1);
        int i = distribution1(generator);

        std::uniform_int_distribution<int> distribution2(i, solution.getSize() - 1);
        int j = distribution2(generator);

        // {
        for (int k = i; k <= j; k++)
        {
            vector<int> compParkings = vectOperations[k].getCompParkings();
            std::uniform_int_distribution<int> distribution3(0, compParkings.size() - 1);
            solution.changeSolutionI(k, compParkings[distribution3(generator)]);
        }
        return solution;
    }
};
