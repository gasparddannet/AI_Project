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
    NonAllocAndContact(int &sizeParkings, Solution &solution, vector<Operation> &vectOperations, vector<Parking> &vectParkings) : Operateur(sizeParkings,solution,vectOperations,vectParkings) {name="NonAllocAndContact";}
    Solution apply(double T) override
    {
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::random_device rrd;
        std::default_random_engine rgenerator(rrd());
        vector<int> sol = solution.getSolution();
        for (long unsigned int i = 0; i < sol.size(); i++)
        {

            vector<int> compParkings = vectOperations[i].getCompParkings();
            vector<int> compParkingsContact = vectOperations[i].getCompParkingsContact();
            vector<int> compParkingsLarge = vectOperations[i].getCompParkingsLarge();

            // std::uniform_int_distribution<int> distribution(0, compParkings.size() - 1);
            std::uniform_real_distribution<double> rdistribution(0.0, 1.0);
            std::uniform_real_distribution<double> distribution2(0.0, 1.0);

            // double p = 0.00001;
            int posPark = sol[i];

            // if (posPark == -1 || (vectOperations[i].getNbTowing() == 3 &&
            //                       ((vectParkings[posPark].getNature() == ParkNature::Contact) || (rdistribution(rgenerator) < p))))
            // {
            //     solution.changeSolutionI(i, compParkings[distribution(generator)]);
            // }
            // else if (vectOperations[i].getNbTowing() != 3 &&
            //          ((vectParkings[posPark].getNature() == ParkNature::Large) || (rdistribution(rgenerator) < p)))
            // {
            //     solution.changeSolutionI(i, compParkings[distribution(generator)]);
            // }


            if (posPark == -1)
            {
                // solution.changeSolutionI(i, compParkings[distribution(generator)]);
                if (vectOperations[i].getNbTowing() == 3)
                {
                    std::uniform_int_distribution<int> distribution(0, compParkingsLarge.size() - 1);
                    solution.changeSolutionI(i, compParkingsLarge[distribution(generator)]);  
                }
                else 
                {
                    if (distribution2(generator) > exp(-T))
                    {
                        std::uniform_int_distribution<int> distribution(0, compParkingsLarge.size() - 1);
                        solution.changeSolutionI(i, compParkingsLarge[distribution(generator)]);  
                    }
                    else
                    {
                        std::uniform_int_distribution<int> distribution(0, compParkings.size() - 1);
                        solution.changeSolutionI(i, compParkings[distribution(generator)]); 

                    }
                }
            }

            else 
            {
                if (vectOperations[i].getNbTowing() == 3 &&
                        ((vectParkings[posPark].getNature() == ParkNature::Contact))) // || (rdistribution(rgenerator) > exp(-T/50000)))) // p > rdistribution(rgenerator))) 
                {
                    std::uniform_int_distribution<int> distribution(0, compParkingsLarge.size() - 1);
                    solution.changeSolutionI(i, compParkingsLarge[distribution(generator)]);
                }

                else if (vectOperations[i].getNbTowing() != 3 &&
                     ((vectParkings[posPark].getNature() == ParkNature::Large))) // || (rdistribution(rgenerator) > exp(-T/50000)))) //p > rdistribution(rgenerator))) 
                {   
                    // if (distribution2(generator) > exp(-T/100))
                    // {
                    //     std::uniform_int_distribution<int> distribution(0, compParkingsLarge.size() - 1);
                    //     solution.changeSolutionI(i, compParkingsLarge[distribution(generator)]);  
                    // }
                    // else 
                    // {
                        std::uniform_int_distribution<int> distribution(0, compParkings.size() - 1);
                        solution.changeSolutionI(i, compParkings[distribution(generator)]); 
                    // }

                }
            }
        }
        return solution;
    }
};
