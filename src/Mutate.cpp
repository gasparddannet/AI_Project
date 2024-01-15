#include "Operateur.h"
#include "Operation.h"
#include "Solution.h"
#include <random>

class Mutate : public Operateur
{
private:
public:
    Mutate(int &sizeParkings, Solution &solution,vector<Operation> &vectOperations,vector<Parking> &vectParkings) : Operateur(sizeParkings,solution,vectOperations,vectParkings) {name = "MutateMinusOne";}
    Solution apply(double T) override
    {
        std::random_device rd;
        std::default_random_engine generator(rd());
        vector<int> sol = solution.getSolution();
        std::uniform_int_distribution<int> distribution(0, sol.size() - 1);
        
        int i = distribution(generator);

        vector<int> compParkings = vectOperations[i].getCompParkings();
        std::uniform_int_distribution<int> distribution2(0, compParkings.size() - 1);
        solution.changeSolutionI(i, compParkings[distribution2(generator)]);

        return solution;
    }
};
