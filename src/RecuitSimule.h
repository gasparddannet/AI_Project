#ifndef RECUITSIMULE_H
#define RECUITSIMULE_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Solution.h"
#include "Parking.h"
#include "Operation.h"
#include "Operateur.h"

class RecuitSimule {
public:
    RecuitSimule(int &nbIter, int &nbIterT, Solution &solutionCourante, vector<Operateur*> operateurs, double T);

    Solution correctSolution(Solution solution, const vector<Parking> &vectParkings, const vector<Operation> &vectOperations);
    double fonctionObjectif(Solution solution, const vector<Parking> &vectParkings, const vector<Operation> &vectOperations);
    void majT(float &acc);

    Solution recuitSimule(const vector<Parking> &vectParkings, const vector<Operation> &vectOperation);
    void heatUp(double valeurCourante, const vector<Parking> &vectParkings, const vector<Operation> &vectOperations);
    
private:
    double Tinit;
    double T;
    int nbIter; 
    int nbIterT;
    Solution solutionCourante;
    Solution solutionGlobal;
    double valeurGlobale;
    vector<Operateur*> operateurs;

    Solution generateSolution(int compt);
};

#endif // RECUITSIMULE_H
