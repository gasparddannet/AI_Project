#ifndef bodytype_h
#define bodytype_h

#include <ostream>

enum class BodyType
{
    MP,
    N3,
    GP
};

inline std::ostream &operator<<(std::ostream &o, const BodyType &value)
{
    switch (value)
    {
    case (BodyType::MP):
        o << "MP";
        break;
    case (BodyType::N3):
        o << "3N";
        break;
    case (BodyType::GP):
        o << "GP";
        break;
    }
    return o;
};

#endif