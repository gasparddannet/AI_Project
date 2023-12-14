#ifndef RECUITSIMULE_H
#define RECUITSIMULE_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Solution.h"
#include "Parking.h"
// #include "Stay.h"
#include "Operation.h"

class RecuitSimule {
public:
    RecuitSimule(int &nbIter, int &nbIterT, Solution &solutionCourante, double T);

    // double fonctionObjectifC(const vector<Parking> &vectParkings, const vector<Stay> &vectStays);
    // double fonctionObjectif(vector<Parking> vectParkings, vector<Stay> vectStays);
    pair<double, Solution> fonctionObjectifC(Solution solution, const vector<Parking> &vectParkings, const vector<Operation> &vectOperations);

    void majT();

    Solution recuitSimule(const vector<Parking> &vectParkings, const vector<Operation> &vectOperation);

private:
    double T;
    int nbIter; 
    int nbIterT;
    Solution solutionCourante;
    Solution solutionGlobal;
    int valeurGlobale;

    // Solution generateSolution(Solution solution, int sizeParkings);
    Solution generateSolution(Solution solution, int sizeParkings, const vector<Operation> &vectOperations, const vector<Parking> &vectParkings);
    // Solution generateSolution(int sizeParkings);

};

#endif // RECUITSIMULE_H