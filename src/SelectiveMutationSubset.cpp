#include "Operateur.h"
#include "Operation.h"
#include "Solution.h"
#include <random>
#include <iostream>

class SelectiveMutationSubset : public Operateur
{
private:

public:
    SelectiveMutationSubset(int &sizeParkings, Solution &solution, vector<Operation> &vectOperations, vector<Parking> &vectParkings) : Operateur(sizeParkings,solution,vectOperations,vectParkings) {name = "SelectiveMutationSubset";}
    Solution* apply() override
    {
        // int sizeSol = solution.getSize();
        std::random_device rd1;
        std::default_random_engine generator1(rd1());
        std::uniform_int_distribution<int> distribution1(0, solution.getSize() - 1);
        int i = distribution1(generator1);

        std::random_device rd2;
        std::default_random_engine generator2(rd2());
        std::uniform_int_distribution<int> distribution2(i, solution.getSize() - 1);
        long unsigned int j = distribution2(generator2);

        std::random_device rd3;
        std::default_random_engine generator3(rd3());

        double mutationProbability = 0.8;

        for (long unsigned int k = i; k <= j; k++)
        {
            std::uniform_real_distribution<float> distribution4(0,1);
            float p = distribution4(generator1);
            // double randValue = static_cast<double>(rand()) / RAND_MAX;
                // if (randValue < mutationProbability)
            if (p < mutationProbability)
            {
                vector<int> compParkings = vectOperations[k].getCompParkings();
                std::uniform_int_distribution<int> distribution3(0, compParkings.size() - 1);
                solution.changeSolutionI(k, compParkings[distribution3(generator3)]);
            }
        }
        return &solution;   
    }
};
