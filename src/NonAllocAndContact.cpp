#include "Operateur.h"
#include "Operation.h"
#include "Solution.h"
#include <stdlib.h>
#include <random>
#include <iostream>

class NonAllocAndContact : public Operateur
{
private:

public:
    NonAllocAndContact(int &sizeParkings, Solution &solution, vector<Operation> &vectOperations, vector<Parking> &vectParkings) : Operateur(sizeParkings,solution,vectOperations,vectParkings){name="NonAllocAndContact";}
    Solution apply() override
    {
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::random_device rrd;
        std::default_random_engine rgenerator(rrd());
        vector<int> sol = solution.getSolution();
        for (int i = 0; i < sol.size(); i++)
        {

            vector<int> compParkings = vectOperations[i].getCompParkings();
            std::uniform_int_distribution<int> distribution(0, compParkings.size() - 1);
            std::uniform_real_distribution<float> rdistribution(0, 100);
            float p = 2;
            int posPark = sol[i];

            if (posPark == -1 || (vectOperations[i].getNbTowing() == 3 &&
                                  ((vectParkings[posPark].getNature() == ParkNature::Contact) || (rdistribution(rgenerator) < p))))
            {
                solution.changeSolutionI(i, compParkings[distribution(generator)]);
            }
            else if (vectOperations[i].getNbTowing() != 3 &&
                     ((vectParkings[posPark].getNature() == ParkNature::Large) || (rdistribution(rgenerator) < p)))
            {
                solution.changeSolutionI(i, compParkings[distribution(generator)]);
            }
        }
        return solution;
    }
};
