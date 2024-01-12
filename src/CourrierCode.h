#ifndef courriercode_h
#define courriercode_h

#include <ostream>

enum class CourrierCode
{
    MC,
    LC
};

inline std::ostream &operator<<(std::ostream &o, const CourrierCode &value)
{
    switch (value)
    {
        case (CourrierCode::MC):
            o << "MC";
            break;
        case (CourrierCode::LC):
            o << "LC";
            break;
    }
    return o;
};

#endif