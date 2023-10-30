#include "Time.h"


Time::Time(int h,int m):hour(h),min(m) {   
}

ostream & operator<<(ostream& o,const Time& t) {
    o << t.hour << ":" << t.min << endl;
    return o;
}
