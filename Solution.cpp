#include "Solution.h"

Solution::Solution(const int iS, vector<ParkSolution> vPS): idStay(iS), vectParkSolutions(vPS) {}

vector<ParkSolution> Solution::getVectParkSolution() {
    return vectParkSolutions;
}
