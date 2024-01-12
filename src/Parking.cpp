#include "Parking.h"
#include "vector"
#include "fstream"
#include "ParkNature.h"

using namespace std;

// string ParkingFile = "Data/parking_2F_2DLarge.csv";

Parking::Parking(string n,string z, string t, ParkNature na, vector<string> tA):
    name(n), zone(z), terminal(t), nature(na), typeAvion(tA) {}


Parking::Parking(const Parking &p)
{
    operator=(p);
}

Parking &Parking::operator=(const Parking &p)
{
    if (this != &p) // Avoid self-assignment
    {
        this->name = p.name;
        this->zone = p.zone;
        this->terminal = p.terminal;
        this->nature = p.nature;

        this->typeAvion.resize(p.typeAvion.size());

        for (int i = 0; i < p.typeAvion.size(); i++)
        {
            this->typeAvion[i] = p.typeAvion[i];
        }
    }
    return *this;
}

// static const vector<Parking> readParking() {
//     vector<Parking> vectParking;

//     ifstream file(ParkingFile);

//     // Make sure the file is open
//     if(!file.is_open()) throw std::runtime_error("Could not open file");

//     string line, colname;
//     int val;
//     getline(file, line); 
//     while (getline(file, line)) {
//         cout << line << endl;
//     }   
//         // used for breaking words 
//     // stringstream s(line); 
//     file.close();

//     return vectParking;
// }


// std::ostream& operator<<(std::ostream& o, const ParkNature& value){
//     switch (value)
//     {
//     case (ParkNature::Contact):
//         o << "Contact" << endl;
//         break;
    
//     case (ParkNature::Large):
//         o << "Large" << endl;
//         break;
//     }
//     return o;
// }


ostream & operator<<(ostream& o,const Parking& p) {
	o << "name : " << p.name << endl;
	o << "zone : " << p.zone << endl;
	o << "terminal : " << p.terminal << endl;
	o << "nature : " << p.nature << endl;
    o << "Type Avion : ";
    vector<string> vectTypeAvion = p.typeAvion;
    if (!vectTypeAvion.empty())
    {
        vector<string>::iterator it = vectTypeAvion.begin();
        for (it=vectTypeAvion.begin() ; it != vectTypeAvion.end(); it++) 
        {
            if (it == vectTypeAvion.end() -1){
                o << *it << endl;
            }
            else o << *it << " | ";
        }
    }
    else { cout << "all"<<endl;}

    cout << endl;
	return o;
}

string Parking::getZone() const{
    return zone;
}

ParkNature Parking::getNature() const{
    return nature;
}

vector<string> Parking::getTypeAvion() const {
    return typeAvion;
}

string Parking::getName() const{
    return name;
}
