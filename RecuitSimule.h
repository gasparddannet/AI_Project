#ifndef RECUITSIMULE_H
#define RECUITSIMULE_H

#include <iostream>
#include <cmath>
#include <cstdlib>

class RecuitSimule {
public:
    RecuitSimule(double T, int nbIter, int nbIterT, double solutionCourante);

    double fonctionObjectif(double solution);

    void majT();

    double recuitSimule();

private:
    double T;
    int nbIter;
    int nbIterT;
    double solutionCourante;

    double generateSolution(double solution);
};

#endif // RECUITSIMULE_H