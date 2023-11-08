#include "RecuitSimule.h"
#include "Parking.h"
#include "Stay.h"
#include "fstream"
#include "sstream"
#include "Read.h"

using namespace std;


string ParkingFile = "Data/parking_2F_2DLarge.csv";
string StaysFile = "Data/stays_2F_090822.csv";


int main()
{
    // RecuitSimule rs(2, 1, 1, 1);

    /* Read Parkings */
    cout << "Read Parkings : " << endl;
    vector<Parking> vectParking = Read::readParkings(ParkingFile);

    // for (Parking &p : vectParking) {
    //     cout << p;
    // }
    // cout << '\n';
    // cout << '\n';

    /* Read Stays */
    cout << "Read stays" << endl;
    vector<Stay> vectStays = Read::readStays(StaysFile);

    // for (Stay &s : vectStays) {
    //     cout << s;
    // }


    // Time t1 = Time(1,50);
    // Time t2 = Time(12,30);
    // Time t3 = t2 - t1;
    // cout << t1;
    // cout << t2;
    // cout << t3;
    // cout << "cc" << endl;

    int nbIter = 100;
    int nbIterT = 100;
    Solution solutionInit = Solution();
    double T = 200;
    RecuitSimule rs(nbIter, nbIterT, solutionInit, T);
    return 0;
}
