#ifndef bodytype_h
#define bodytype_h

#include <ostream>

enum class BodyType { MP };

inline std::ostream& operator<<(std::ostream& o, const BodyType& value){
    switch (value)
    {
    case (BodyType::MP):
        o << "MP";
        break;
    }
    return o;
};

#endif