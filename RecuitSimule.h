#ifndef RECUITSIMULE_H
#define RECUITSIMULE_H

#include <iostream>
#include <cmath>
#include <cstdlib>

class RecuitSimule {
public:
    RecuitSimule(int nbIter, int nbIterT, double solutionCourante, double T);

    double fonctionObjectif(double solution);

    void majT();

    double recuitSimule();

private:
    double T;
    int nbIter;
    int nbIterT;
    double solutionCourante;
    double solutionGlobal;

    double generateSolution(double solution);
};

#endif // RECUITSIMULE_H