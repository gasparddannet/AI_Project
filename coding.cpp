#include <vector>
// #include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Solution.h"
#include "Parking.h"
#include "Stay.h"

using namespace std;

vector<int> initEncoding(vector<Stay> vectStays, int sizeParkings) {
    int sizeStays = vectStays.size();
    srand (time(NULL));
    vector<vector<int>> encoding(sizeStays);
    /* or just vector<int> if we  don't consider towing ??*/
    
    for (int i=0; i < sizeStays; i++) {
        Stay stay = vectStays[i];
        int authTow = stay.getAuthorizedTowing();
        if (authTow == 0) {
            encoding[i].push_back(rand() % sizeParkings);
        }
        else if (authTow == 1) {
            int p1 = rand() % sizeParkings;
            int p2 = rand() % sizeParkings;
            encoding[i].push_back(p1);
            encoding[i].push_back(p2);
        }
        else if (authTow == 2) {
            int p1 = rand() % sizeParkings;
            int p2 = rand() % sizeParkings;
            int p3 = rand() % sizeParkings;
            encoding[i].push_back(p1);
            encoding[i].push_back(p2);
            encoding[i].push_back(p3);
        }
        else {
            throw invalid_argument("Too much towing");
        }
    }
}


vector<Solution> decoding(vector<vector<int>> encoding, vector<Stay> vectStays, vector<Parking> vectParkings) {
    vector<Solution> vectSol;
    for (int i=0; i<encoding.size(); i++) {
        int posStay = i;
        Stay stay = vectStays[posStay];
        vector<ParkSolution> vectParkSolutions;

        for (int p=0; p < encoding[i].size(); p++) {
            int posParking = encoding[i][p];
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

            /* we need to be able to know when the towing is done to have different Date and Time !! */
        }

        Solution sol = Solution(posStay, vectParkSolutions);
        vectSol.push_back(sol);

    }
    return vectSol;
}
