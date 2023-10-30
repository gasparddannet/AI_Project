#ifndef PARKING_H
#define PARKING_H

#include <iostream>
#include <vector>
#include <variant>
#include "ParkNature.h"

using namespace std;


class Parking
{
    const string name;
    const string zone;
    const string terminal;
    const ParkNature nature;
    // variant<const string, const vector<int>> typeAvion;
    const vector<int> typeAvion;


    
    public:
        Parking(string n,string z, string t, ParkNature na, const vector<int> tA);
        friend ostream & operator<<(ostream& o,const Parking& p) ;

        // static const vector<Parking> readParking();

};

#endif // PARKING_H