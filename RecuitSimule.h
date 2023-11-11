#ifndef RECUITSIMULE_H
#define RECUITSIMULE_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Solution.h"
#include "Parking.h"
#include "Stay.h"

class RecuitSimule {
public:
    RecuitSimule(int &nbIter, int &nbIterT, Solution &solutionCourante, double T);

    // double fonctionObjectifC(const vector<Parking> &vectParkings, const vector<Stay> &vectStays);
    // double fonctionObjectif(vector<Parking> vectParkings, vector<Stay> vectStays);
    pair<double, Solution> fonctionObjectifC(const vector<Parking> &vectParkings, const vector<Stay> &vectStays);

    void majT();

    Solution recuitSimule(const vector<Parking> &vectParkings, const vector<Stay> &vectStays);

private:
    double T;
    int nbIter; 
    int nbIterT;
    Solution solutionCourante;
    Solution solutionGlobal;

    // Solution generateSolution(Solution solution, int sizeParkings);
    Solution generateSolution(int sizeParkings);

};

#endif // RECUITSIMULE_H