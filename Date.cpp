#include "Date.h"


Date::Date(int j,int m,int a):jour(j),mois(m),annee(a){   
}


int Date::comparer(Date d)
{
	if (annee!= d.annee)
    {
        if(annee<d.annee)
            return -1;
        else
            return 1;
    }
	else if (mois != d.mois)
        return ((mois<d.mois)?-1:1);	// utilisation ici de l operateur ternaire
    else if (jour!=d.jour)
        return ((jour<d.jour)?-1:1);
    else
        return 0;
}

Date::~Date()
{
    // cout<<"appel destructeur Date sur : ";
    // affiche();
}

ostream & operator<<(ostream& o,const Date& d) {
    o << d.jour << "/" << d.mois << "/" << d.annee << endl;
    return o;
}

ostream & operator<<(ostream& o,const Date* d) {
    o << d->jour << "/" << d->mois << "/" << d->annee << endl;
    return o;
}

istream& operator>>(istream& i, Date& d) {
    i >> d.jour >> d.mois >> d.annee;
    return i;
}

bool Date::operator<(const Date&d) {
    int res = this->comparer(d);
    if (res <= 0)
        return true;
    else
        return false;
}

Date& Date::operator++ () {
    jour++;
    return *this;
}


