#include "Operateur.h"
#include "Operation.h"
#include "Solution.h"
#include <random>

class MutateMinusOne : public Operateur
{
private:
public:
    MutateMinusOne(int &sizeParkings, Solution &solution,vector<Operation> &vectOperations,vector<Parking> &vectParkings) : Operateur(sizeParkings,solution,vectOperations,vectParkings) {name = "MutateMinusOne";}
    Solution apply(double T) override
    {
        // srand(time(NULL));
        // srand((int)time(0));
        std::random_device rd;
        std::default_random_engine generator(rd());
        vector<int> sol = solution.getSolution();
        for (long unsigned int i = 0; i < sol.size(); i++)
        {
            if (sol[i] == -1)
            {
                vector<int> compParkings = vectOperations[i].getCompParkings();
                std::uniform_int_distribution<int> distribution(0, compParkings.size() - 1);
                solution.changeSolutionI(i, compParkings[distribution(generator)]);
            }
        }
        return solution;
    }
};
