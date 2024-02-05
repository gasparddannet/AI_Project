#include "Time.h"
#include <iomanip>
#include <iostream>

Time::Time(int h, int m) : hour(h), min(m)
{
}

ostream &operator<<(ostream &o, const Time &t)
{
    o << std::setw(2) << std::setfill('0') << t.hour;
    o << ":";
    o << std::setw(2) << std::setfill('0') << t.min;
    return o;
}

int Time::comparer(const Time &t)
{
	if (hour!= t.hour)
    {
        if(hour<t.hour)
            return -1;
        else
            return 1;
    }
	else if (min != t.min)
        return ((min<t.min)?-1:1);	// utilisation ici de l operateur ternaire
    else
        return 0;
}

bool Time::operator==(const Time &t)
{
    if (hour == t.hour)
    {
        if (min == t.min)
        {
            return true;
        }
    }
    return false;
}

Time Time::operator-(const Time &t) {
    if (this->comparer(t) > 0) {
        int time = hour * 60 + min - t.hour*60 - t.min;
        return Time(time/60, time%60);
    }
    throw invalid_argument("The second time is greater than the first");
}

bool Time::operator>=(const Time &t) {
    int res = this->comparer(t);
    if (res >= 0)
        return true;
    else
        return false;
}

bool Time::operator<=(const Time &t) {
    int res = this->comparer(t);
    if (res <= 0)
        return true;
    else
        return false;
}
