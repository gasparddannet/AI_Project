#include "Date.h"
#include <iomanip>
#include <iostream>

Date::Date(int &j, int &m, int &a, int &h, int &min) : jour(j), mois(m), annee(a), hour(h), min(min)
{
}

// Date::Date(int j, int m, int a, int h, int min) : jour(j), mois(m), annee(a), hour(h), min(min)
// {
// }


int Date::comparer(const Date &d)
{
    if (annee != d.annee)
    {
        if (annee < d.annee)
            return -1;
        else
            return 1;
    }
    else if (mois != d.mois)
        return ((mois < d.mois) ? -1 : 1); // utilisation ici de l operateur ternaire
    else if (jour != d.jour)
        return ((jour < d.jour) ? -1 : 1);
    else if (hour != d.hour)
        return ((hour < d.hour) ? -1 : 1);
    else if (min != d.min)
        return ((min < d.min) ? -1 : 1);
    else
        return 0;
}

Date::~Date()
{
    // cout<<"appel destructeur Date sur : ";
    // affiche();
}

int Date::getJour() {return jour;}
int Date::getMois() {return mois;}
int Date::getAnnee() {return annee;}
int Date::getHour() {return hour;}
int Date::getMin() {return min;}


ostream &operator<<(ostream &o, const Date &d)
{
    o << std::setw(2) << std::setfill('0') << d.jour;
    o << "/";
    o << std::setw(2) << std::setfill('0') << d.mois;
    o << "/";
    o << std::setw(4) << std::setfill('0') << d.annee;
    o << ";";
    o << std::setw(2) << std::setfill('0') << d.hour;
    o << ":";
    o << std::setw(2) << std::setfill('0') << d.min;
    return o;
}

// ostream & operator<<(ostream& o,const Date* d) {
//     o << d->jour << "/" << d->mois << "/" << d->annee;
//     return o;
// }

istream &operator>>(istream &i, Date &d)
{
    i >> d.jour >> d.mois >> d.annee >> d.hour >> d.min;
    return i;
}

bool Date::operator<=(const Date &d)
{
    int res = this->comparer(d);
    if (res <= 0)
        return true;
    else
        return false;
}

bool Date::operator>=(const Date &d)
{
    int res = this->comparer(d);
    if (res >= 0)
        return true;
    else
        return false;
}

bool Date::operator==(const Date &d)
{
    int res = this->comparer(d);
    if (res == 0)
        return true;
    else
        return false;
}

// Date& Date::operator++ () {
//     jour++;
//     return *this;
// }

bool Date::operator!=(const Date &d)
{
    int res = this->comparer(d);
    if (res != 0)
        return true;
    else
        return false;
}

// Date& Date::operator-(const Date &t) {
//     // if (this->comparer(t) > 0) {
//     if (this->operator>(t)) {
//         // return Time(t.hour-hour, t.min-min);
//         int time = hour * 60 + min - t.hour*60 - t.min;
//         // cout << time << endl;
//         return Time(time/60, time%60);
//     }
//     throw invalid_argument("The second time is greater than the first");
// }

int Date::ecart(const Date &d) // renvoie l'ecart (en minutes) entre deux dates
{
    if (this->operator>=(d))
    {
        int ecart;
        if (jour == d.jour)
        {
            ecart = hour * 60 + min - d.hour * 60 - d.min;
            return ecart;
        }
        else if (mois == d.mois && annee == d.annee)
        {
            ecart = 24 * 60 - d.hour * 60 - d.min + hour * 60 + min;
            return ecart;
        }
        else
        {
            ecart = 24 * 60;
            return ecart;
        }
    }
    throw invalid_argument("The second time is greater than the first");
}

Date Date::operator+(const int &t)          // ajoute t minutes a la date
{
    int hour2;
    int min2;
    int jour2 = jour;   
    if (hour*60+min + t >= 24*60) {
        jour2 = jour-1;
        int time = hour*60+min+t - 24*60;
        hour2 = time/60;
        min2 = time%60;
    }
    else {
        int time = hour*60+min+t;
        hour2 = time/60;
        min2 = time % 60;
    }
    return Date(jour2, mois, annee, hour2, min2);
}


Date Date::operator-(const int &t)          // enleve t minutes a la date
{
    int hour2;
    int min2;
    int jour2 = jour;
    if (hour*60+min - t <= 0) {
        jour2 = jour-1;
        int time = 24*60 - (hour*60+min-t);
        hour2 = time/60;
        min2 = time%60;
        // cout << "hour : " << hour << std::endl;
        // cout << "min : " << min << std::endl;
    }
    else {
        int time = hour*60+min-t;
        hour2 = time/60;
        min2 = time % 60;
        // cout << "hour : " << hour << std::endl;
        // cout << "min : " << min << std::endl;
    }
    return Date(jour2, mois, annee, hour2, min2);
}