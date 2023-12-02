#include "ParkSolution.h"
#include <tuple>

ParkSolution::ParkSolution(int iP, ParkNature pN, string z, Date sD, Date eD):
    idParking(iP), parkNature(pN), zone(z), startDate(sD), endDate(eD) {}


int ParkSolution::getPosParking() {
    return idParking;
}


tuple<Date, Date> ParkSolution::getTupleStartEnd() {
    return std::make_tuple(startDate, endDate);
}
