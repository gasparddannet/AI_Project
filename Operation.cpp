#include "Operation.h"

        
Operation::Operation(const int& idS, const Date& arrDate, const Date& depDate, const vector<int> compParkings):
    idStay(idS), arrDate(arrDate), depDate(depDate), compatibleParkings(compParkings) {}

void Operation::setIdParkind(int idP) {
    idParking = idP;
}

int Operation::getIdParking() {
    return idParking;
}

const Date& Operation::getArrDate() const {
    return arrDate;
}

const Date& Operation::getDepDate() const {
    return depDate;
}

int Operation::getIdStay() {
    return idStay;
}
