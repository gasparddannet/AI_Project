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

    const vector<int> compatibleParkings;

    public:
        Operation(const int& idStays, const Date& arrDate, const Date& depDate, const vector<int> compParkings);
        ~Operation();
        void setIdParkind(int idP);
        int getIdParking();
        int getIdStay();
        const Date& getArrDate() const;
        const Date& getDepDate() const;
        const vector<int> getCompParkings() const;
};

#endif