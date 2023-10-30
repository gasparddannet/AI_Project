#ifndef DATE_H
#define DATE_H

#include <iostream>

using namespace std;

class Date
{
    int jour,mois,annee;
    
    public:
        Date(int,int,int);

        int comparer(const Date& d);

        virtual ~Date();
        friend ostream & operator<<(ostream& o,const Date& d) ;
        friend ostream & operator<<(ostream& o,const Date* d) ;
        friend istream& operator>>(istream& i, Date& d) ;
        bool operator==(const Date& d);
        bool operator<(const Date&d);
        Date& operator++ ();
};


#endif // DATE_H
