#include "Operation.h"

        
Operation::Operation(const int& idS, const Date& arrDate, const Date& depDate, const vector<int> compParkingsContact, const vector<int> compParkingsLarge, const int nbTowing):
    idStay(idS), arrDate(arrDate), depDate(depDate), compatibleParkingsContact(compParkingsContact), compatibleParkingsLarge(compParkingsLarge), nbTowing(nbTowing) {}

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
    vector<int> vectInt(compatibleParkingsContact);
    vectInt.insert(vectInt.end(), compatibleParkingsLarge.begin(), compatibleParkingsLarge.end());
    return vectInt;
}

const vector<int> Operation::getCompParkingsContact() const {
    return compatibleParkingsContact;
}

const vector<int> Operation::getCompParkingsLarge() const {
    return compatibleParkingsLarge;
}
const int Operation::getNbTowing() const {
    return nbTowing;
}