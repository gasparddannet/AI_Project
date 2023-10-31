#include "ParkingOccupation.h"

ParkingOccupation::ParkingOccupation(const int iP, vector<tuple<Date, Time, Date, Time>> occ):
    idParking(iP), occupation(occ) {}
