#include "RecuitSimule.h"

RecuitSimule::RecuitSimule(double T, int nbIter, int nbIterT, double solutionCourante) :
    T(T),
    nbIter(nbIter),
    nbIterT(nbIterT),
    solutionCourante(solutionCourante) {}

double RecuitSimule::fonctionObjectif(double solution) {
    return solution;
}

void RecuitSimule::majT() {
    T *= 0.1;
}

double RecuitSimule::generateSolution(double solution) {
    return (rand() % 1000) / 100.0;
}

double RecuitSimule::recuitSimule() {
    double solutionCourante = generateSolution(solutionCourante);
    double valeurCourante = fonctionObjectif(solutionCourante);
    int compt = 0;

    while (T > 0.1 && compt < nbIter) {
        for (int i = 0; i < nbIterT; ++i) {
            double nouvelleSolution = generateSolution(solutionCourante);
            double nouvelleValeur = fonctionObjectif(nouvelleSolution);

            double differenceValeur = nouvelleValeur - valeurCourante;
            if (differenceValeur < 0 || rand() / static_cast<double>(RAND_MAX) < exp(-differenceValeur / T)) {
                solutionCourante = nouvelleSolution;
                valeurCourante = nouvelleValeur;
            }
        }
        compt += 1;
        majT();
    }

    return solutionCourante;
}