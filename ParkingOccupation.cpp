#include "ParkingOccupation.h"

ParkingOccupation::ParkingOccupation(const int iP, vector<tuple<Date, Date>> occ):
    idParking(iP), occupation(occ) {}
