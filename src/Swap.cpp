#include "Operateur.h"
#include "Operation.h"
#include "Solution.h"
#include <random>

class Swap : public Operateur
{
private:
public:
    Swap(int &sizeParkings, Solution &solution,vector<Operation> &vectOperations,vector<Parking> &vectParkings) : Operateur(sizeParkings,solution,vectOperations,vectParkings) {name = "Swap";}
    Solution* apply() override
    {
        std::random_device rd;
        std::default_random_engine generator(rd());
        vector<int> sol = solution.getSolution();
        std::uniform_int_distribution<int> distribution(0, sol.size() - 1);
        
        int i = distribution(generator);
        int j = distribution(generator);
        int si = sol[i];
        int sj = sol[j];


        if (si == -1)
        {
            vector<int> compParkings = vectOperations[j].getCompParkings();
            std::uniform_int_distribution<int> distribution2(0, compParkings.size() - 1);
            si = compParkings[distribution2(generator)];
        }
        if (sj == -1)
        {
            vector<int> compParkings = vectOperations[i].getCompParkings();
            std::uniform_int_distribution<int> distribution2(0, compParkings.size() - 1);
            sj = compParkings[distribution2(generator)];            
        }

        solution.changeSolutionI(i, sj);
        solution.changeSolutionI(j, si);
        

        return &solution;
    }
};
