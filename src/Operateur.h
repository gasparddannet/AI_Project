
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

    virtual Solution* apply(double& T) = 0;
    string getName() {return name;}
    // void setSizeParkings(int sp) {sizeParkings=sp;}
    void setSolution(Solution &sol) {solution=sol;}
    // void setVecOperations(const vector<Operation> &vecOp) {vectOperations=vecOp;} const;
    // void setVecParkings(const vector<Parking> &vecPark) {vectParkings=vecPark;}
};

#endif