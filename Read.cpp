#include "Read.h"
#include "CourrierCode.h"
#include "BodyType.h"
#include "ParkNature.h"

using namespace std;

string & Read::rtrim(string &s)
{
    s.erase(s.find_last_not_of(' ') + 1);
    return s;
}

/**********************************************/
/*************     READ PARKING   *************/ 
/**********************************************/

ParkNature Read::stringToParkNature(std::string &pn)
{
    // pn = rtrim(pn);
    // cout << "pn : " << pn << endl;
    // if (pn.compare("Contact") == 0)
    // {
    //     cout << "ccc" << endl;
    // }
    if (pn == "Contact")
    {
        return ParkNature::Contact;
    }
    else if (pn == "Large")
    {
        return ParkNature::Large;
    }
    throw std::invalid_argument("Wrong Parking Nature");
}


const vector<int> Read::stringToVectInt(const string &ta)
{
    // variant<const string, const vector<int>> variantTa;
    vector<int> Ta;
    stringstream ss(ta);
    string type;
    while (getline(ss, type, ','))
    {
        if (type.compare("-") == 0) {
            // variantTa = TypeAvion{"all"};
            // variantTa = in_place_index<0>();
        }
        else {
            // cout << type << endl;
            // variantTa.emplace<1>.push_back(stoi(type));
            Ta.push_back(stoi(type));
        }
    }
    return Ta;
}

Parking Read::stringstreamToParking(std::stringstream &ss)
{
    vector<string> row;
    string val;
    while (getline(ss, val, ';'))
    {
        val = rtrim(val);
        row.push_back(val);
    }
    Parking park = Parking(row[0], row[1], row[2], stringToParkNature(row[3]), stringToVectInt(row[4]));
    return park;
}

const vector<Parking> Read::readParkings(string parkingFile)
{
    vector<Parking> vectParkings;
    ifstream file(parkingFile);
    if (!file.is_open())
        throw std::runtime_error("Could not open file");

    string line;
    getline(file, line);
    while (getline(file, line))
    {
        std::stringstream ss(line);
        vectParkings.push_back(stringstreamToParking(ss));
    }
    file.close();

    return vectParkings;
}


/**********************************************/
/*************     READ STAYS   *************/ 
/**********************************************/

BodyType Read::stringToBodyType(std::string &bt)
{
    if (bt == "MP")
    {
        return BodyType::MP;
    }
    throw std::invalid_argument("Wrong Body Type");
}

CourrierCode Read::stringToCourrierCode(string &cc) {
    if (cc == "MC")
    {
        return CourrierCode::MC;
    }
    throw std::invalid_argument("Wrong Courrier Code");

}

Date Read::stringToDate(string &d) {
    vector<int> vect;
    string val;
    stringstream ss(d);
    while (getline(ss, val, '/')) {
        vect.push_back(stoi(val));
    }
    return Date(vect[0], vect[1], vect[2]);
}

Time Read::stringToTime(string &t) {
    vector<int> vect;
    string val;
    stringstream ss(t);
    while (getline(ss, val, ':')) {
        vect.push_back(stoi(val));
    }
    return Time(vect[0], vect[1]);
}

int Read::getAuthorizedTowing(int &isTowable, Date& arrDate, Time& arrTime, Date& depDate, Time& depTime) {
    if (isTowable == 1) {
        if (arrDate == depDate) {
            if (depTime - arrTime >= Time(4,0)) {
                return 2;
            }
            else return 1;
        }
        else {
            if (Time(20,0) >= arrTime or depTime >= Time(4,0)) {
                return 2;
            }
            else return 1;
        }
    }

    else return 0;
}

Stay Read::stringstreamToStay(stringstream &ss) {
    vector<string> row;
    string val;
    while (getline(ss, val, ';'))
    {
        val = rtrim(val);
        row.push_back(val);
    }
    int id = stoi(row[0]);
    BodyType bodyType = stringToBodyType(row[1]);
    int aircraftType = stoi(row[2]);
    string arrOwnerCie = row[4];
    string arrExploitingCie = row[5];
    int arrNumber = stoi(row[6]);
    Date arrDate = stringToDate(row[7]);
    Time arrHour = stringToTime(row[8]);
    CourrierCode arrCourrierCode = stringToCourrierCode(row[9]);
    string arrStop = row[10];
    string depOwnerCie = row[11];
    string depExploitingCie = row[12];
    int depNumber = stoi(row[13]);
    Date depDate = stringToDate(row[14]);
    Time depHour = stringToTime(row[15]);
    CourrierCode depCourrierCode = stringToCourrierCode(row[16]);
    string depStop = row[17];
    int isTowable = stoi(row[3]);
    int authorizedTowing = getAuthorizedTowing(isTowable, arrDate, arrHour, depDate, depHour);

    Stay stay = Stay(id, bodyType, aircraftType, authorizedTowing, arrOwnerCie, arrExploitingCie , 
                     arrNumber, arrDate, arrHour, arrCourrierCode, arrStop, depOwnerCie,
                     depExploitingCie, depNumber, depDate, depHour, depCourrierCode, row[17]);
    return stay;
}

const vector<Stay> Read::readStays(string staysFile) {
    vector<Stay> vectStays;

    ifstream file(staysFile);

    if (!file.is_open())
        throw std::runtime_error("Could not open file");

    string line;
    getline(file, line);
    while (getline(file, line))
    {
        std::stringstream ss(line);
        vectStays.push_back(stringstreamToStay(ss));
    }
    file.close();

    return vectStays;
}
