#include "Time.h"
#include <iomanip>
#include <iostream>

Time::Time(int h,int m):hour(h),min(m) {   
}

ostream & operator<<(ostream& o,const Time& t) {
    o << std::setw(2) << std::setfill('0') << t.hour;
    o << ":";
    o << std::setw(2) << std::setfill('0') << t.min;
    o << endl;
    return o;
}
