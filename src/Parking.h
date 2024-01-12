#ifndef PARKING_H
#define PARKING_H

#include <iostream>
#include <vector>
//#include <variant>
#include "ParkNature.h"

using namespace std;


class Parking
{
    string name;
    string zone;
    string terminal;
    ParkNature nature;
    // variant<const string, const vector<int>> typeAvion;
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
        
        // static const vector<Parking> readParking();

};

#endif // PARKING_H