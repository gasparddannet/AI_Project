#ifndef RECUITSIMULE_H
#define RECUITSIMULE_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Solution.h"

class RecuitSimule {
public:
    RecuitSimule(int nbIter, int nbIterT, Solution solutionCourante, double T);

    double fonctionObjectif(Solution solution, vector<Parking> vectParkings, vector<Stay> vectStays);

    void majT();

    Solution recuitSimule(vector<Parking> vectParkings, vector<Stay> vectStays);

private:
    double T;
    int nbIter; 
    int nbIterT;
    Solution solutionCourante;
    Solution solutionGlobal;

    Solution generateSolution(Solution solution, int sizeParkings);
};

#endif // RECUITSIMULE_H