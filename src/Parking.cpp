#include "Parking.h"
#include "vector"
#include "fstream"
#include "ParkNature.h"

using namespace std;

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
