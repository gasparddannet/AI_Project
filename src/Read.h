#ifndef read_h
#define read_h

#include "Parking.h"
#include "Stay.h"

#include "fstream"
#include "sstream"

using namespace std;

class Read 
{
    /*************     READ PARKING   *************/ 
    public:
    static string & rtrim(string &s);
    static ParkNature stringToParkNature(std::string &pn);
    static const vector<int> stringToVectInt(const string &ta);
    static Parking stringstreamToParking(std::stringstream &ss);
    static const vector<Parking> readParkings(string parkingFile);


    /*************     READ STAYS   *************/ 

    static BodyType stringToBodyType(std::string &bt);
    static CourrierCode stringToCourrierCode(string &cc);
    static Date stringToDate(string &d, string &t);
    // static Time stringToTime(string &t);
    static int getAuthorizedTowing(int &isTowable, Date& arrDate, Date& depDate);
    static Stay stringstreamToStay(stringstream &ss);
    static const vector<Stay> readStays(string staysFile); 


    static const vector<int> createCompatibleParking(int aircraftType, vector<Parking> vectParkings);

};


#endif