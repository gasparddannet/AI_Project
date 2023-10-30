#include "RecuitSimule.h"
#include "Parking.h"
#include "Stay.h"
#include "fstream"
#include "sstream"

using namespace std;


string ParkingFile = "Data/parking_2F_2DLarge.csv";
string StaysFile = "Data/stays_2F_090822.csv";

string &rtrim(string &s)
{
    s.erase(s.find_last_not_of(' ') + 1);
    return s;
}

/**********************************************/
/*************     READ PARKING   *************/ 
/**********************************************/

ParkNature stringToParkNature(std::string &pn)
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
    // else throw string("Wrong Parking Nature");
    // else throw std::invalid_argument("Wrong Parking Nature");
    throw std::invalid_argument("Wrong Parking Nature");
}


const vector<int> stringToVectInt(const string &ta)
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

Parking stringstreamToParking(std::stringstream &ss)
{
    vector<string> row;
    string val;
    // int numCol = 0;
    while (getline(ss, val, ';'))
    {
        val = rtrim(val);
        // cout << val.length() << endl;

        row.push_back(val);
        // cout << numCol;
        // cout << val << endl;
        // if(ss.peek() == ';') ss.ignore();
        // numCol++;
    }
    Parking park = Parking(row[0], row[1], row[2], stringToParkNature(row[3]), stringToVectInt(row[4]));
    return park;
}

const vector<Parking> readParkings()
{
    vector<Parking> vectParkings;

    ifstream file(ParkingFile);

    // Make sure the file is open
    if (!file.is_open())
        throw std::runtime_error("Could not open file");

    string line, colname;
    int val;
    getline(file, line);
    while (getline(file, line))
    {
        // cout << line << endl;
        std::stringstream ss(line);
        //  while(std::getline(ss, colname, ';')){

        //     // Initialize and add <colname, int vector> pairs to result
        //     // result.push_back({colname, std::vector<int> {}});
        //     // cout << colname << endl;

        // }
        // while (ss >> colname) {
        //     cout << colname << endl;
        // }
        vectParkings.push_back(stringstreamToParking(ss));
    }
    // used for breaking words
    // stringstream s(line);
    file.close();

    return vectParkings;
}


/**********************************************/
/*************     READ STAYS   *************/ 
/**********************************************/

BodyType stringToBodyType(std::string &bt)
{
    if (bt == "MP")
    {
        return BodyType::MP;
    }
    throw std::invalid_argument("Wrong Body Type");
}

CourrierCode stringToCourrierCode(string &cc) {
    if (cc == "MC")
    {
        return CourrierCode::MC;
    }
    throw std::invalid_argument("Wrong Courrier Code");

}

Date stringToDate(string &d) {
    vector<int> vect;
    string val;
    stringstream ss(d);
    while (getline(ss, val, '/')) {
        vect.push_back(stoi(val));
    }
    return Date(vect[0], vect[1], vect[2]);
}

Time stringToTime(string &t) {
    vector<int> vect;
    string val;
    stringstream ss(t);
    while (getline(ss, val, ':')) {
        vect.push_back(stoi(val));
    }
    return Time(vect[0], vect[1]);
}

Stay stringstreamToStay(stringstream &ss) {
    vector<string> row;
    string val;
    while (getline(ss, val, ';'))
    {
        val = rtrim(val);
        row.push_back(val);
    }
    Stay stay = Stay(stoi(row[0]), stringToBodyType(row[1]), stoi(row[2]), stoi(row[3]), row[4], row[5], 
                     stoi(row[6]), stringToDate(row[7]), stringToTime(row[8]), stringToCourrierCode(row[9]), row[10], row[11],
                     row[12], stoi(row[13]), stringToDate(row[14]), stringToTime(row[15]), stringToCourrierCode(row[16]), row[17]);
    return stay;
}

const vector<Stay> readStays() {
    vector<Stay> vectStays;

    ifstream file(StaysFile);

    if (!file.is_open())
        throw std::runtime_error("Could not open file");

    string line, colname;
    int val;
    getline(file, line);
    while (getline(file, line))
    {
        std::stringstream ss(line);
        vectStays.push_back(stringstreamToStay(ss));
    }
    file.close();

    return vectStays;
}



int main()
{
    RecuitSimule rs(2, 1, 1, 1);

    /* Read Parkings */
    cout << "Read Parkings : " << endl;
    vector<Parking> vectParking = readParkings();

    for (Parking &p : vectParking) {
        cout << p;
    }
    cout << '\n';
    cout << '\n';

    /* Read Stays */
    cout << "Read stays" << endl;
    vector<Stay> vectStays = readStays();

    for (Stay &s : vectStays) {
        cout << s;
    }

    return 0;
}
