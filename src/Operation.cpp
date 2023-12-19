#include "Operation.h"

        
Operation::Operation(const int& idS, const Date& arrDate, const Date& depDate, const vector<int> compParkings, const int nbTowing):
    idStay(idS), arrDate(arrDate), depDate(depDate), compatibleParkings(compParkings), nbTowing(nbTowing) {}

Operation::~Operation() 
{
    // std::cout << "Destructor Operation" << std::endl;
}

void Operation::setIdParkind(int idP) {
    idParking = idP;
}

int Operation::getIdParking() const {
    return idParking;
}

const Date& Operation::getArrDate() const {
    return arrDate;
}

const Date& Operation::getDepDate() const {
    return depDate;
}

int Operation::getIdStay() const {
    return idStay;
}

const vector<int> Operation::getCompParkings() const {
    return compatibleParkings;
}

const int Operation::getNbTowing() const {
    return nbTowing;
}