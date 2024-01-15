#include "Read.h"
#include "CourrierCode.h"
#include "BodyType.h"
#include "ParkNature.h"
#include <algorithm>
// #include <boost/algorithm/string.hpp>


using namespace std;

string &Read::trim(string &s)
{
    s.erase(s.find_last_not_of(' ') + 1);       //suffixing spaces
    s.erase(0, s.find_first_not_of(' '));       //prefixing spaces
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

const vector<string> Read::stringToVectString(const string &ta)
{
    // variant<const string, const vector<int>> variantTa;
    vector<string> Ta;
    stringstream ss(ta);
    string type;
    while (getline(ss, type, ','))
    {
        if (type.compare("-") == 0)
        {
            // variantTa = TypeAvion{"all"};
            // variantTa = in_place_index<0>();
        }
        else
        {
            // cout << type << endl;
            // variantTa.emplace<1>.push_back(stoi(type));
            // Ta.push_back(stoi(type));
            Ta.push_back(type);

        }
    }
    return Ta;
}

Parking Read::stringstreamToParking(std::stringstream &ss)
{
    // cout << "stringstreamToPArkings\n";
    vector<string> row;
    string val;
    while (getline(ss, val, ';'))
    {
        val = trim(val);
        // boost::trim(val);
        row.push_back(val);
    }

    // for (string& s:row)
    // {
    //     cout << s;
    //     cout << endl;
    // }
    // cout << typeid(row[0]).name() << endl;

    Parking park = Parking(row[0], row[1], row[2], stringToParkNature(row[3]), stringToVectString(row[4]));
    return park;
}

vector<Parking> Read::readParkings(string parkingFile)
{
    // cout << "Read parkings   \n";
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

BodyType Read::stringToBodyType(std::string& bt)
{
    if (bt == "MP")
    {
        return BodyType::MP;
    }
    else if (bt == "3N")
    {
        return BodyType::N3;
    }
    else if (bt == "GP")
    {
        return BodyType::GP;
    }

    string msg = "Wrong Body Type :" + bt;
    throw std::invalid_argument(msg);
}

CourrierCode Read::stringToCourrierCode(string &cc)
{
    if (cc == "MC")
    {
        return CourrierCode::MC;
    }
    else if (cc == "LC")
    {
        return CourrierCode::LC;
    }

    string msg = "Wrong Courrier Code :" + cc;
    throw std::invalid_argument(msg);
}

Date Read::stringToDate(string &d, string &t)
{
    vector<int> vect;
    string val;
    stringstream ss(d);
    while (getline(ss, val, '/'))
    {
        vect.push_back(stoi(val));
    }
    stringstream st(t);
    while (getline(st, val, ':'))
    {
        vect.push_back(stoi(val));
    }
    return Date(vect[0], vect[1], vect[2], vect[3], vect[4]);
}

// Time Read::stringToTime(string &t) {
//     vector<int> vect;
//     string val;
//     stringstream ss(t);
//     while (getline(ss, val, ':')) {
//         vect.push_back(stoi(val));
//     }
//     return Time(vect[0], vect[1]);
// }

int Read::getAuthorizedTowing(int &isTowable, Date &arrDate, Date &depDate)
{
    if (isTowable == 1)
    {
        // if (arrDate == depDate) {
        //     // if (depTime - arrTime >= Time(4,0)) {
        //     if (depDate.ecart(arrDate) >= 4*60) {
        //         return 2;
        //     }
        //     else return 1;
        // }
        // else {
        //     if (Time(20,0) >= arrTime or depTime >= Time(4,0)) {
        //         return 2;
        //     }
        //     else return 1;
        // }
        if (depDate.ecart(arrDate) >= 4 * 60)
        {
            return 2;
        }
        else
            return 1;
    }

    else
        return 0;
}



Stay Read::stringstreamToStayOriginal(stringstream &ss)
{
    // cout << "StringstramToStay" << endl;
    vector<string> row;
    string val;
    while (getline(ss, val, ';'))
    {
        val = trim(val);
        // boost::trim(val);
        row.push_back(val);
    }

    // for (string& s:row)
    // {
    //     cout << s;
    //     cout << endl;
    // }
    int id = stoi(row[0]);
    BodyType bodyType = stringToBodyType(row[1]);
    string aircraftType = row[2];
    // string arrOwnerCie = row[4];
    // string arrExploitingCie = row[5];
    int arrNumber = stoi(row[6]);
    Date arrDate = stringToDate(row[7], row[8]);
    // Time arrHour = stringToTime(row[8]);
    CourrierCode arrCourrierCode = stringToCourrierCode(row[9]);
    // string arrStop = row[10];
    // string depOwnerCie = row[11];
    // string depExploitingCie = row[12];
    int depNumber = stoi(row[13]);
    Date depDate = stringToDate(row[14], row[15]);
    // Time depHour = stringToTime(row[15]);
    CourrierCode depCourrierCode;
    try {
        depCourrierCode = stringToCourrierCode(row[16]);
    }   
    catch (std::invalid_argument& e) {
        depCourrierCode = stringToCourrierCode(row[9]);
    }
    // string depStop = row[17];
    int isTowable = stoi(row[3]);
    int authorizedTowing = getAuthorizedTowing(isTowable, arrDate, depDate);

    // Stay stay = Stay(id, bodyType, aircraftType, authorizedTowing, arrOwnerCie, arrExploitingCie,
    //                  arrNumber, arrDate, arrCourrierCode, arrStop, depOwnerCie,
    //                  depExploitingCie, depNumber, depDate, depCourrierCode, row[17]);
    Stay stay = Stay(id, bodyType, aircraftType, authorizedTowing, arrNumber, arrDate,
                    arrCourrierCode, depNumber, depDate, depCourrierCode);
    return stay;
}


Stay Read::stringstreamToStay(stringstream &ss)
{
    vector<string> row;
    string val;
    while (getline(ss, val, ';'))
    {
        val = trim(val);
        // boost::trim(val);
        row.push_back(val);
    }

    // for (string& s:row)
    // {
    //     cout << s;
    //     cout << endl;
    // }
    int id = stoi(row[0]);
    BodyType bodyType = stringToBodyType(row[1]);
    string aircraftType = row[2];
    int authorizedTowing = stoi(row[3]);
    int arrNumber = stoi(row[4]);
    Date arrDate = stringToDate(row[5], row[6]);
    CourrierCode arrCourrierCode = stringToCourrierCode(row[7]);
    int depNumber = stoi(row[8]);
    Date depDate = stringToDate(row[9], row[10]);
    CourrierCode depCourrierCode;
    try {
        depCourrierCode = stringToCourrierCode(row[11]);
    }   
    catch (std::invalid_argument& e) {
        depCourrierCode = stringToCourrierCode(row[7]);
    }

    Stay stay = Stay(id, bodyType, aircraftType, authorizedTowing, arrNumber, arrDate,
                    arrCourrierCode, depNumber, depDate, depCourrierCode);
    return stay; 
}


const vector<Stay> Read::readStays(string staysFile)
{
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

const vector<int> Read::createCompatibleParking(string aircraftType, vector<Parking> vectParkings)
{
    vector<int> compatibleParkings;
    for (int i = 0; i < vectParkings.size(); i++)
    {
        const vector<string> parkTypesAvion = vectParkings[i].getTypeAvion();

        if (!parkTypesAvion.empty())
        {
            if (find(parkTypesAvion.begin(), parkTypesAvion.end(), aircraftType) != parkTypesAvion.end()){
                compatibleParkings.push_back(i);
            }
            // for (int j = 0; j < vectParkings[i].getTypeAvion().size(); j++)
            // {
            //     if (vectParkings[i].getTypeAvion()[j] == aircraftType)
            //     {
            //         compatibleParkings.push_back(i);
            //     }
            // }
        }
        else {
            compatibleParkings.push_back(i);
        }
    }
    return compatibleParkings;
}