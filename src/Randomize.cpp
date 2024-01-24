#include "Operateur.h"
#include "Operation.h"
#include "Solution.h"
#include <iostream>
#include <random>



class Randomize : public Operateur {
private:
public:
    Randomize(int &sizeParkings, Solution &solution, vector<Operation> &vectOperations, vector<Parking> &vectParkings):Operateur(sizeParkings,solution,vectOperations,vectParkings) {name = "Randomize";}
    Solution* apply(double& T) override {
        // srand((int)time(0));
        std::random_device rd;
        std::default_random_engine generator(rd());

        for (int i = 0; i < solution.getSize(); i++)
        {
            vector<int> compParkings = vectOperations[i].getCompParkings();

            std::uniform_int_distribution<int> distribution(0, compParkings.size()-1);
            // std::cout << endl << "random : " << distribution(generator) << endl;
            solution.changeSolutionI(i,compParkings[distribution(generator)]);
        }
        return &solution;
    }
};
