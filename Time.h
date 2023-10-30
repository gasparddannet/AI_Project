#ifndef time_h
#define time_h

#include <iostream>

using namespace std;

class Time
{
    int hour, min;

    public:
        Time(int h, int m);
        void Print();
        friend ostream & operator<<(ostream& o,const Time& t) ;
    };

#endif