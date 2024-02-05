
#ifndef operateur_h
#define operateur_h
#include "Solution.h"

class Operateur {
protected:
    int sizeParkings;
    Solution solution;
    const vector<Operation> vectOperations;
    const vector<Parking> vectParkings;
    string name;

public:
    Operateur(int &sizeParkings, Solution &solution, const vector<Operation> &vectOperations,const vector<Parking> &vectParkings) : sizeParkings(sizeParkings), solution(solution), vectOperations(vectOperations), vectParkings(vectParkings) {}
    virtual ~Operateur() {}

    virtual Solution* apply() = 0;
    string getName() {return name;}
    void setSolution(Solution &sol) {solution=sol;}

};

#endif