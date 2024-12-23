#include "Stay.h"
#include "vector"

using namespace std;


Stay::Stay(const int id, const BodyType bT, const string aT, const int auT, const int aN, const Date aD,
        const CourrierCode aCC, const int dN, const Date dD, const CourrierCode dCC):
        id(id), bodyType(bT), aircraftType(aT), authorizedTowing(auT), arrNumber(aN), arrDate(aD), arrCourrierCode(aCC),
        depNumber(dN), depDate(dD), depCourrierCode(dCC) {};



ostream & operator<<(ostream& o,const Stay& s) {
	o << "id : " << s.id << endl;
	o << "body type : " << s.bodyType;
	o << "aircraft type : " << s.aircraftType << endl;
	o << "authorized towing : " << s.authorizedTowing << endl;
    // o << "arr owner cie : " << s.arrOwnerCie << endl;
    // o << "arr exploiting cie : " << s.arrExploitingCie << endl;
    o << "arr number : " << s.arrNumber << endl;
    o << "arr date : " << s.arrDate << endl;
    // o << "arr hour : " << s.arrHour;
    o << "arr courrier code : " << s.arrCourrierCode << endl;
    // o << "arr stop : " << s.arrStop << endl;
    // o << "dep owner cie : " << s.depOwnerCie << endl;
    // o << "dep exploiting cie : " << s.depExploitingCie << endl;
    o << "dep number : " << s.depNumber << endl;
    o << "dep date : " << s.depDate << endl;
    // o << "dep hour : " << s.depHour;
    o << "dep courrier code : " << s.depCourrierCode << endl;
    // o << "dep stop : " << s.depStop << endl;
    o << endl;
	return o;
}


Date Stay::getArrDate() const{
    return arrDate;
}

Date Stay::getDepDate() const{
    return depDate;
}


int Stay::getAuthorizedTowing() const{
    return authorizedTowing;
}

string Stay::getAircraftType() const {
    return aircraftType;
}

int Stay::getId() const{
    return id;
}

BodyType Stay::getBodyType() const{
    return bodyType;
}

int Stay::getArrNumber() const{
    return arrNumber;
}

int Stay::getDepNumber() const{
    return depNumber;
}

CourrierCode Stay::getArrCourrierCode() const{
    return arrCourrierCode;
}

CourrierCode Stay::getDepCourrierCode() const{
    return depCourrierCode;
}