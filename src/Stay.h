#ifndef stay_h
#define stay_h

#include "BodyType.h"
#include "Date.h"
// #include "Time.h"
#include "CourrierCode.h"

#include <iostream>

using namespace std;

class Stay
{
    const int id;
    const BodyType bodyType;
    const string aircraftType;
    const int authorizedTowing;
    const int arrNumber;
    const Date arrDate;
    const CourrierCode arrCourrierCode;
    const int depNumber;
    const Date depDate;
    const CourrierCode depCourrierCode;

    public:
        Stay(const int id, const BodyType bT, const string aT, const int auT, 
        const int aN, const Date aD, const CourrierCode aCC, const int dN, const Date dD, const CourrierCode dCC);

        friend ostream & operator<<(ostream& o,const Stay& p) ;

        Date getArrDate() const;
        Date getDepDate() const;
        int getAuthorizedTowing() const;
        string getAircraftType() const;
        int getId() const;
        BodyType getBodyType() const;
        int getArrNumber() const;
        int getDepNumber() const;
        CourrierCode getArrCourrierCode() const;
        CourrierCode getDepCourrierCode() const;


};

#endif