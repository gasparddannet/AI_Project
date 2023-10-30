#include "RecuitSimule.h"
#include "Parking.h"
#include "fstream"
#include "sstream"

using namespace std;



string ParkingFile = "Data/parking_2F_2DLarge.csv";

string &rtrim(string &s)
{
    s.erase(s.find_last_not_of(' ') + 1);
    return s;
}

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

const vector<Parking> readParking()
{
    vector<Parking> vectParking;

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
        vectParking.push_back(stringstreamToParking(ss));
    }
    // used for breaking words
    // stringstream s(line);
    file.close();

    return vectParking;
}

int main()
{
    RecuitSimule rs(2, 1, 1, 1);
    vector<Parking> vectParking = readParking();

    for (Parking &p : vectParking) {
        cout << p;
    }
    return 0;
}
