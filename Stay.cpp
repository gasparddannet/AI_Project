#include "Stay.h"
#include "vector"

using namespace std;


Stay::Stay(const int id, const BodyType bT, const int aT, const int auT, const string aOC, const string aEC, 
        const int aN, const Date aD, const  Time aH, const CourrierCode aCC, const string aS, const string dOC,
        const string dEC, const int dN, const Date dD, const Time dH, const CourrierCode dCC, const string dS):
        id(id), bodyType(bT), aircraftType(aT), authorizedTowing(auT), arrOwnerCie(aOC), arrExploitingCie(aEC),
        arrNumber(aN), arrDate(aD), arrHour(aH), arrCourrierCode(aCC), arrStop(aS), depOwnerCie(dOC),
        depExploitingCie(dEC), depNumber(dN), depDate(dD), depHour(dH), depCourrierCode(dCC), depStop(dS) {};


std::ostream& operator<<(std::ostream& o, const BodyType& value){
    switch (value)
    {
    case (BodyType::MP):
        o << "MP" << endl;
        break;
    }
    return o;
};

std::ostream& operator<<(std::ostream& o, const CourrierCode& value){
    switch (value)
    {
    case (CourrierCode::MC):
        o << "MC" << endl;
        break;
    }
    return o;
};

ostream & operator<<(ostream& o,const Stay& s) {
	o << "id : " << s.id << endl;
	o << "body type : " << s.bodyType;
	o << "aircraft type : " << s.aircraftType << endl;
	o << "authorized towing : " << s.authorizedTowing << endl;
    o << "arr owner cie : " << s.arrOwnerCie << endl;
    o << "arr exploiting cie : " << s.arrExploitingCie << endl;
    o << "arr number : " << s.arrNumber << endl;
    o << "arr date : " << s.arrDate;
    o << "arr hour : " << s.arrHour;
    o << "arr courrier code : " << s.arrCourrierCode;
    o << "arr stop : " << s.arrStop << endl;
    o << "dep owner cie : " << s.depOwnerCie << endl;
    o << "dep exploiting cie : " << s.depExploitingCie << endl;
    o << "dep number : " << s.depNumber << endl;
    o << "dep date : " << s.depDate;
    o << "dep hour : " << s.depHour;
    o << "dep courrier code : " << s.depCourrierCode;
    o << "dep stop : " << s.depStop << endl;
    o << endl;
	return o;
}


Date Stay::getArrDate() {
    return arrDate;
}

Time Stay::getArrHour() {
    return arrHour;
}

Date Stay::getDepDate() {
    return depDate;
}

Time Stay::getDepHour() {
    return depHour;
}

int Stay::getAuthorizedTowing() {
    return authorizedTowing;
}

int Stay::getAircraftType() {
    return aircraftType;
}
