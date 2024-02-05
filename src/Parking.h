#ifndef PARKING_H
#define PARKING_H

#include <iostream>
#include <vector>
#include "ParkNature.h"

using namespace std;


class Parking
{
    string name;
    string zone;
    string terminal;
    ParkNature nature;
    vector<string> typeAvion;


    
    public:
        Parking(string n,string z, string t, ParkNature na, vector<string> tA);

        Parking(const Parking & p);
        Parking & operator=(const Parking& p);

        friend ostream & operator<<(ostream& o,const Parking& p) ;
        string getZone() const;
        ParkNature getNature() const;
        vector<string> getTypeAvion() const;
        string getName() const;
};

#endif // PARKING_H