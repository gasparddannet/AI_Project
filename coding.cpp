#include "Solution.h"
#include "Parking.h"
#include "Stay.h"

#include <vector>
#include <variant>
#include <iostream>
#include <tuple>
// #include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;


template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>; // line not needed in C++20...


// vector<int> initEncoding(vector<Stay> vectStays, int sizeParkings) {
vector<variant<int, vector<tuple<int, Date, Time, int>>>> initEncoding(vector<Stay> vectStays, int sizeParkings) {
    int sizeStays = vectStays.size();
    srand (time(NULL));
    // vector<vector<int>> encoding(sizeStays);
    /* or just vector<int> if we  don't consider towing ??*/

    vector<variant<int, vector<tuple<int, Date, Time, int>>>> encoding(sizeStays);

    for (int i=0; i < sizeStays; i++) {
        Stay stay = vectStays[i];
        int authTow = stay.getAuthorizedTowing();
        if (authTow == 0) {
            // encoding[i].push_back(rand() % sizeParkings);

            // variant<int, vector<tuple<Date,Time,int>>> elmt = rand() % sizeParkings;
            encoding.push_back(rand() % sizeParkings);
        }
        else if (authTow == 1) {
            int p1 = rand() % sizeParkings;
            Date dateTow = Date(rand(), rand(), rand());
            Time timeTow = Time(rand(), rand());
            int p2 = rand() % sizeParkings;
            // encoding[i].push_back(p1);
            // encoding[i].push_back(p2);
            tuple<int, Date, Time, int> {p1, dateTow, timeTow, p2};
            tuple<int, Date, Time, int> t = make_tuple(p1, dateTow, timeTow, p2);
            vector<tuple<int, Date, Time, int>> vect = {t};
            encoding.push_back(vect);
        }
        else if (authTow == 2) {
            int p1 = rand() % sizeParkings;
            Date dateTow1 = Date(rand(), rand(), rand());
            Time timeTow1 = Time(rand(), rand());
            int p2 = rand() % sizeParkings;
            Date dateTow2 = Date(rand(), rand(), rand());
            Time timeTow2 = Time(rand(), rand());
            int p3 = rand() % sizeParkings;
            // encoding[i].push_back(p1);
            // encoding[i].push_back(p2);
            // encoding[i].push_back(p3);
            tuple<int, Date, Time, int> t1 = {p1, dateTow1, timeTow1, p2};
            tuple<int, Date, Time, int> t2 = {p2, dateTow2, timeTow2, p3};
            vector<tuple<int, Date, Time, int>> vect = {t1, t2};
            encoding.push_back(vect);

        }
        else {
            throw invalid_argument("Too much towing");
        }
    }
    return encoding;
}


// vector<Solution> decoding(vector<vector<int>> encoding, vector<Stay> vectStays, vector<Parking> vectParkings) {
vector<Solution> decoding(vector<variant<int, vector<tuple<int, Date, Time, int>>>> encoding, 
                          vector<Stay> vectStays, vector<Parking> vectParkings) {

    vector<Solution> vectSol;
    for (int i=0; i<encoding.size(); i++) {
        int posStay = i;
        Stay stay = vectStays[posStay];
        vector<ParkSolution> vectParkSolutions;


        std::visit(overload{
            [&](int &posParking) {
                Parking park = vectParkings[posParking];
                // int idParking = vectParkings[posParking].name;
                ParkNature pN = park.getNature();
                string zone = park.getZone();
                Date sD = stay.getArrDate();
                Time sH = stay.getArrHour();
                Date eD = stay.getDepDate();
                Time eH = stay.getDepHour();
                ParkSolution parkSolution = ParkSolution(posParking, pN, zone, sD, sH, eD, eH);
                vectParkSolutions.push_back(parkSolution);
            },
            [&](vector<tuple<int, Date, Time, int>> &vect) {
                for (int j=0; j<vect.size(); j++) {
                    int posParking = get<0>(vect[j]);
                    Parking park = vectParkings[posParking];
                    // int idParking = vectParkings[posParking].name;
                    ParkNature pN = park.getNature();
                    string zone = park.getZone();
                    Date sD = stay.getArrDate();
                    Time sH = stay.getArrHour();
                    Date eD = get<1>(vect[j]);
                    Time eH = get<2>(vect[j]);
                    ParkSolution parkSolution = ParkSolution(posParking, pN, zone, sD, sH, eD, eH);
                    vectParkSolutions.push_back(parkSolution);
                    /* the start date are not correct if there are two tows, but we only need one date and time ??*/
                }
            }
        }, encoding[i]);



        // for (int p=0; p < encoding[i].size(); p++) {
        //     int posParking = encoding[i][p];
        //     Parking park = vectParkings[posParking];
        //     // int idParking = vectParkings[posParking].name;
        //     ParkNature pN = park.getNature();
        //     string zone = park.getZone();
        //     Date sD = stay.getArrDate();
        //     Time sH = stay.getArrHour();
        //     Date eD = stay.getDepDate();
        //     Time eH = stay.getDepHour();
        //     ParkSolution parkSolution = ParkSolution(posParking, pN, zone, sD, sH, eD, eH);
        //     vectParkSolutions.push_back(parkSolution);

        //     /* we need to be able to know when the towing is done to have different Date and Time !! */
        // }

        Solution sol = Solution(posStay, vectParkSolutions);
        vectSol.push_back(sol);

    }
    return vectSol;
}


bool checkSolution(vector<Solution> vectSol, int sizeParkings) {
    vector<vector<tuple<Date, Time, Date, Time>>> tempOccParking(sizeParkings); // tableau indexe par les parkings des tableaux des tuples startDate, startHour, endDate, endHour
    for (int i=0; i++; vectSol.size()) {
        vector<ParkSolution> vectParkSolution = vectSol[i].getVectParkSolution();
        for (int j=0; j++; vectParkSolution.size()) {
            int posPark = vectParkSolution[j].getPosParking();
            tempOccParking[posPark].push_back(vectParkSolution[j].getTupleStartEnd());
        }
    }

    // check si pas 2 stays en meme temps sur un meme parking, on regarde pour un parking si les dates se superposent

    for (int i=0; i++; sizeParkings) {
        int s = tempOccParking[i].size();
        if (s >= 2) {
            for (int j=0; j++; s-1) {
                Date startDate1 = get<0>(tempOccParking[i][j]);
                Date endDate1 = get<2>(tempOccParking[i][j]);
                Time startHour1 = get<1>(tempOccParking[i][j]);
                Time endHour1 = get<3>(tempOccParking[i][j]);
                for (int k=j+1; k++; s) {
                    Date startDate2 = get<0>(tempOccParking[i][k]);
                    Date endDate2 = get<2>(tempOccParking[i][k]);
                    Time startHour2 = get<1>(tempOccParking[i][k]);
                    Time endHour2 = get<3>(tempOccParking[i][k]);
                    if (endDate1 == startDate2 ) {
                        if (startHour2 <= endHour1) {
                            return false;
                        }
                    }
                    if (endDate2 == startDate1) {
                        if (startHour1 <= endHour2) {
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}


int main() {
    return 0;
}