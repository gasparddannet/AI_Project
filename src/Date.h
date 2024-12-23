#ifndef DATE_H
#define DATE_H

#include <iostream>

using namespace std;

class Date
{
    int day,month,year;
    int hour, min;
    
    public:
        Date(int& j,int& m,int& a,int& h,int& min);
        // Date(int j,int m,int a,int h,int min);

        int comparer(const Date& d);

        virtual ~Date();
        int getDay();
        int getMonth();
        int getYear();
        int getHour();
        int getMin();
        friend ostream & operator<<(ostream& o,const Date& d) ;
        // friend ostream & operator<<(ostream& o,const Date* d) ;
        friend istream& operator>>(istream& i, Date& d) ;
        bool operator==(const Date& d);
        bool operator<=(const Date&d);
        bool operator>=(const Date&d);
        bool operator!=(const Date&d);
        // Date& operator++ ();
        // Date& operator-(const Date &t);
        int ecart(const Date &d);
        Date operator+(const int &t);
        Date operator-(const int &t);
};


#endif // DATE_H
