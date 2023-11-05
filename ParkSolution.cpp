#include "ParkSolution.h"
#include <tuple>

ParkSolution::ParkSolution(int iP, ParkNature pN, string z, Date sD, Time sH, Date eD, Time eH):
    idParking(iP), parkNature(pN), zone(z), startDate(sD), startHour(sH), endDate(eD), endHour(eH) {}


int ParkSolution::getPosParking() {
    return idParking;
}


tuple<Date, Time, Date, Time> ParkSolution::getTupleStartEnd() {
    return std::make_tuple(startDate, startHour, endDate, endHour);
}
