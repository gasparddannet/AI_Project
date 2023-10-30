#ifndef stays_h
#define stays_h

#include "BodyType.h"
#include "Date.h"
#include "Time.h"
#include "CourrierCode.h"

#include <iostream>

using namespace std;

class Stays
{
    const int id;
    const BodyType bodyType;
    const int aircraftType;
    const bool isTowable;
    const string arrOwnerCie;
    const string arrExploitingCie;
    const int arrNumber;
    const Date arrDate;
    const Time arrHour;
    const CourrierCode arrCourrierCode;
    const string arrStop;
    
};

#endif