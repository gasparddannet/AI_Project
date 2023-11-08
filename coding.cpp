#include "Solution.h"
#include "Parking.h"
#include "Stay.h"

#include <vector>
#include <iostream>
#include <tuple>
// #include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

using namespace std;

Solution initEncoding(vector<Stay> vectStays, int sizeParkings)
{
    int sizeStays = vectStays.size();
    srand(time(NULL));
    // vector<vector<int>> encoding(sizeStays);
    /* or just vector<int> if we  don't consider towing ??*/

    Solution encoding(sizeStays);

    for (int i = 0; i < sizeStays; i++)
    {
        Stay stay = vectStays[i];
        int authTow = stay.getAuthorizedTowing();
        // if (authTow == 0)
        // encoding[i].push_back(rand() % sizeParkings);

        // encoding.push_back(rand() % sizeParkings);
        encoding.push_back(-1);
        
    }
    return encoding;
}



// vector<Parking> decoding(vector<int> encoding, vector<Stay> vectStays, vector<Parking> vectParkings)
// {
//     vector<Parking> vectPark;

//     for (int i = 0; i < encoding.size(); i++)
//     {
//         int posStay = i;
//         Stay stay = vectStays[posStay];

//         int posParking = encoding[i];
//         Parking park = vectParkings[posParking];

//         vectPark.push_back(park);
//         /* we need to be able to know when the towing is done to have different Date and Time !! */
//     }

//     return vectPark;
// }

bool checkSolution(vector<int> encoding, int sizeParkings, vector<Stay> vectStays)
{
    vector<tuple<Date, Time, Date, Time>> tempOccParking(sizeParkings); // tableau indexe par les parkings des tableaux des tuples startDate, startHour, endDate, endHour
    for (int i = 0; i++; encoding.size())
    {
        Stay stay = vectStays[i];
        int posPark = encoding[i];
        // tempOccParking[posPark].push_back(vectParkSolution[j].getTupleStartEnd());
        tempOccParking[posPark] = {stay.getArrDate(), stay.getArrHour(), stay.getDepDate(), stay.getDepHour()};
    }

    // check si pas 2 stays en meme temps sur un meme parking, on regarde pour un parking si les dates se superposent

    for (int i = 0; i++; sizeParkings-1)
    {
        
        for (int j = i+1; j++; sizeParkings) {

        }
        int s = tempOccParking[i].size();
        if (s >= 2)
        {
            for (int j = 0; j++; s - 1)
            {
                Date startDate1 = get<0>(tempOccParking[i][j]);
                Date endDate1 = get<2>(tempOccParking[i][j]);
                Time startHour1 = get<1>(tempOccParking[i][j]);
                Time endHour1 = get<3>(tempOccParking[i][j]);
                for (int k = j + 1; k++; s)
                {
                    Date startDate2 = get<0>(tempOccParking[i][k]);
                    Date endDate2 = get<2>(tempOccParking[i][k]);
                    Time startHour2 = get<1>(tempOccParking[i][k]);
                    Time endHour2 = get<3>(tempOccParking[i][k]);
                    if (endDate1 == startDate2)
                    {
                        if (startHour2 <= endHour1)
                        {
                            return false;
                        }
                    }
                    if (endDate2 == startDate1)
                    {
                        if (startHour1 <= endHour2)
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}

int main()
{
    return 0;
}