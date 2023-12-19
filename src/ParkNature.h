#ifndef parknature_h
#define parknature_h

#include <ostream>


enum class ParkNature { Contact , Large};

inline std::ostream& operator<<(std::ostream& o, const ParkNature& value){
    switch (value)
    {
    case (ParkNature::Contact):
        o << "Contact";
        break;
    
    case (ParkNature::Large):
        o << "Large";
        break;
    }
    return o;
}

#endif