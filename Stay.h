#ifndef stay_h
#define stay_h

#include "BodyType.h"
#include "Date.h"
#include "Time.h"
#include "CourrierCode.h"

#include <iostream>

using namespace std;

class Stay
{
    const int id;
    const BodyType bodyType;
    const int aircraftType;
    const int authorizedTowing;
    const string arrOwnerCie;
    const string arrExploitingCie;
    const int arrNumber;
    const Date arrDate;
    const Time arrHour;
    const CourrierCode arrCourrierCode;
    const string arrStop;
    const string depOwnerCie;
    const string depExploitingCie;
    const int depNumber;
    const Date depDate;
    const Time depHour;
    const CourrierCode depCourrierCode;
    const string depStop;

    public:
        Stay(const int id, const BodyType bT, const int aT, const int auT, const string aOC, const string aEC, 
        const int aN, const Date aD, const  Time aH, const CourrierCode aCC, const string aS, const string dOC,
        const string dEC, const int dN, const Date dD, const Time dH, const CourrierCode dCC, const string dS);

        friend ostream & operator<<(ostream& o,const Stay& p) ;

        Date getArrDate();
        Time getArrHour();
        Date getDepDate();
        Time getDepHour();
        int getAuthorizedTowing();
        int getAircraftType();
        int getId();
        BodyType getBodyType();
        int getArrNumber();
        int getDepNumber();
};

#endif