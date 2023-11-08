#ifndef RECUITSIMULE_H
#define RECUITSIMULE_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Solution.h"

class RecuitSimule {
public:
    RecuitSimule(int nbIter, int nbIterT, Solution solutionCourante, double T);

    double fonctionObjectif(Solution solution);

    void majT();

    Solution recuitSimule();

private:
    double T;
    int nbIter; 
    int nbIterT;
    Solution solutionCourante;
    Solution solutionGlobal;

    Solution generateSolution(Solution solution);
};

#endif // RECUITSIMULE_H