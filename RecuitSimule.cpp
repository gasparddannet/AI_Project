#include "RecuitSimule.h"
#include "Solution.h"

RecuitSimule::RecuitSimule(int nbIter, int nbIterT, Solution solutionCourante, double T=200) :
    T(T),
    nbIter(nbIter),
    nbIterT(nbIterT),
    solutionCourante(solutionCourante),
    solutionGlobal(solutionCourante) {}

double RecuitSimule::fonctionObjectif(Solution solution) {
    // return solution;
    return 1;
}

void RecuitSimule::majT() {
    T *= 0.1;
}

Solution RecuitSimule::generateSolution(Solution solution) {
    // return (rand() % 1000) / 100.0;
    return solution;
}

Solution RecuitSimule::recuitSimule() {
    double valeurCourante = fonctionObjectif(solutionCourante);
    int compt = 0;

    while (T > 0.1 && compt < nbIter) {
        for (int i = 0; i < nbIterT; ++i) {
            Solution nouvelleSolution = generateSolution(solutionCourante);
            double nouvelleValeur = fonctionObjectif(nouvelleSolution);

            double differenceValeur = nouvelleValeur - valeurCourante;
            if (differenceValeur < 0) {
                solutionCourante = nouvelleSolution;
                valeurCourante = nouvelleValeur;
                solutionGlobal = nouvelleSolution;
            } 
            else {
                if (rand() / static_cast<double>(RAND_MAX) < exp(-differenceValeur / T)) {
                    solutionCourante = nouvelleSolution;
                    valeurCourante = nouvelleValeur;
                }
            }
        }
        compt += 1;
        majT();
    }

    return solutionGlobal;
}