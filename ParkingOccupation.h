#ifndef parkingoccupation_h
#define parkingoccupation_h

#include <vector>
#include<tuple>
#include "Date.h"
#include "Time.h"

using namespace std;


class ParkingOccupation {
    const int idParking;
    vector<tuple<Date, Time, Date, Time>> occupation;

    public:
        ParkingOccupation(const int iP, vector<tuple<Date, Time, Date, Time>> occ);
};

#endif