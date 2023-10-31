#ifndef parksolution_h
#define parksolution_h

#include "ParkNature.h"
#include "Date.h"
#include "Time.h"

class ParkSolution {
    int idParking;
    ParkNature parkNature;
    string zone;
    Date startDate;
    Time startHour;
    Date endDate;
    Time endHour;

    public:
        ParkSolution(int iP, ParkNature pN, string z, Date sD, Time sH, Date eD, Time eH);
};

#endif