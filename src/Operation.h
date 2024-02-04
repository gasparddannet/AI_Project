#ifndef OPERATION_H
#define OPERATION_H

#include <iostream>
#include "Date.h"
#include <vector>

using namespace std;

class Operation 
{
    const int idStay;
    const Date arrDate;
    const Date depDate;
    int idParking;
    int nbTowing;
    const string aircraftType;

    const vector<int> compatibleParkingsContact;
    const vector<int> compatibleParkingsLarge;

    public:
        Operation(const int& idStays, const Date& arrDate, const Date& depDate, const vector<int> compParkingsContact, const vector<int> compParkingsLarge, const int nbTowing, const string& aircraftType);
        ~Operation();
        void setIdParkind(int idP);
        int getIdParking() const;
        int getIdStay() const;
        const Date& getArrDate() const;
        const Date& getDepDate() const;
        const vector<int> getCompParkings() const;
        const vector<int> getCompParkingsContact() const;
        const vector<int> getCompParkingsLarge() const;
        const int getNbTowing() const;
        const string getAircraftType() const;
};

#endif