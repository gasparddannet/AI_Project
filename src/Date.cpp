#include "Date.h"
#include <iomanip>
#include <iostream>

Date::Date(int &da, int &m, int &y, int &h, int &min) : day(da), month(m), year(y), hour(h), min(min)
{
}



int Date::comparer(const Date &d)
{
    if (year != d.year)
    {
        if (year < d.year)
            return -1;
        else
            return 1;
    }
    else if (month != d.month)
        return ((month < d.month) ? -1 : 1); // utilisation ici de l operateur ternaire
    else if (day != d.day)
        return ((day < d.day) ? -1 : 1);
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

int Date::getDay() {return day;}
int Date::getMonth() {return month;}
int Date::getYear() {return year;}
int Date::getHour() {return hour;}
int Date::getMin() {return min;}


ostream &operator<<(ostream &o, const Date &d)
{
    o << std::setw(2) << std::setfill('0') << d.day;
    o << "/";
    o << std::setw(2) << std::setfill('0') << d.month;
    o << "/";
    o << std::setw(4) << std::setfill('0') << d.year;
    o << ";";
    o << std::setw(2) << std::setfill('0') << d.hour;
    o << ":";
    o << std::setw(2) << std::setfill('0') << d.min;
    return o;
}

istream &operator>>(istream &i, Date &d)
{
    i >> d.day >> d.month >> d.year >> d.hour >> d.min;
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

bool Date::operator!=(const Date &d)
{
    int res = this->comparer(d);
    if (res != 0)
        return true;
    else
        return false;
}

int Date::ecart(const Date &d) // renvoie l'ecart (en minutes) entre deux dates
{
    if (this->operator>=(d))
    {
        int ecart;
        if (day == d.day)
        {
            ecart = hour * 60 + min - d.hour * 60 - d.min;
            return ecart;
        }
        else if (month == d.month && year == d.year)
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
    int day2 = day;   
    if (hour*60+min + t >= 24*60) {
        day2 = day-1;
        int time = hour*60+min+t - 24*60;
        hour2 = time/60;
        min2 = time%60;
    }
    else {
        int time = hour*60+min+t;
        hour2 = time/60;
        min2 = time % 60;
    }
    return Date(day2, month, year, hour2, min2);
}


Date Date::operator-(const int &t)          // enleve t minutes a la date
{
    int hour2;
    int min2;
    int day2 = day;
    if (hour*60+min - t <= 0) {
        day2 = day-1;
        int time = 24*60 - (hour*60+min-t);
        hour2 = time/60;
        min2 = time%60;
    }
    else {
        int time = hour*60+min-t;
        hour2 = time/60;
        min2 = time % 60;
    }
    return Date(day2, month, year, hour2, min2);
}