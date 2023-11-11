#include "RecuitSimule.h"
#include "Parking.h"
#include "Stay.h"
#include "fstream"
#include "sstream"
#include "Read.h"
#include <vector>
#include <algorithm>

using namespace std;


string ParkingFile = "Data/parking_2F_2DLarge.csv";
string StaysFile = "Data/stays_2F_090822.csv";


int main()
{
    // RecuitSimule rs(2, 1, 1, 1);

    /* Read Parkings */
    cout << "Read Parkings" << endl;
    vector<Parking> vectParkings = Read::readParkings(ParkingFile);

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
    // cout << "cc1" << endl;


    int nbIter = 100;
    int nbIterT = 100;
    int sizeStays = vectStays.size();
    vector<int> vect(sizeStays);
    int sizeParkings = vectParkings.size();

    Solution solutionInit = Solution(vect);
    solutionInit.randomize(sizeParkings);
    double T = 200;
    RecuitSimule rs(nbIter, nbIterT, solutionInit, T);
    Solution solGlobal = rs.recuitSimule(vectParkings, vectStays);

    cout << "\n" << endl;

    // double finesseGlobal = RecuitSimule::fonctionObjectif(solGlobal, vectParkings, vectStays);
    // cout << "finesse Globales : " << finesseGlobal << endl;
    cout << "cc1" << endl;
    
    // std::pair<double, Solution> pairGlo = rs.fonctionObjectif(solGlobal, vectParkings, vectStays);

    // cout << "valeurGlobale : " << pairGlo.first << endl;

    ofstream file("test_file.csv");
    if (!file.is_open())
        throw std::runtime_error("Could not open file");
    file << "Stay;BodyType;AircraftType;Towings;Arr_Number;Arr_Date;Arr_Hour;Dep_Number;Dep_Date;Dep_Hour;Parking 1;Contact 1;Zone 1;Start Date 1;Start Hour 1;End Date 1;End Hour 1" << endl;   
    vector<int> vectSolGlobal = solGlobal.getSolution();
    for (long unsigned int i = 0 ; i < vectSolGlobal.size() ; i++) {
        file << vectStays[i].getId() << ";";
        file << vectStays[i].getBodyType() << ";";
        file << vectStays[i].getAircraftType() << ";";
        file << vectStays[i].getAuthorizedTowing() << ";";
        file << vectStays[i].getArrNumber() << ";";
        file << vectStays[i].getArrDate() << ";";
        file << vectStays[i].getArrHour() << ";";
        file << vectStays[i].getDepNumber() << ";";
        file << vectStays[i].getDepDate() << ";";
        file << vectStays[i].getDepHour() << ";";
        file << vectParkings[vectSolGlobal[i]].getName() << ";";
        file << vectParkings[vectSolGlobal[i]].getNature() << ";";
        file << vectParkings[vectSolGlobal[i]].getZone() << ";";
        file << vectStays[i].getArrDate() << ";";
        file << vectStays[i].getArrHour() << ";";   
        file << vectStays[i].getDepDate() << ";";
        file << vectStays[i].getDepHour() << endl;
    }
    file.close();
    cout << "cc2" << endl;

    vector<vector<tuple<Date, Time, Date, Time, int>>> tempOccParking(sizeParkings); // tableau indexe par les parkings des tableaux des tuples startDate, startHour, endDate, endHour
    for (long unsigned int i = 0; i < vectSolGlobal.size(); i++)
    {
        Stay stay = vectStays[i];
        int posPark = vectSolGlobal[i];
        // tempOccParking[posPark].push_back(vectParkSolution[j].getTupleStartEnd());
        tempOccParking[posPark].push_back({stay.getArrDate(), stay.getArrHour(), stay.getDepDate(), stay.getDepHour(), i});
    }
    ofstream fileOccPark("test_file_parking_occ.csv");
    if (!fileOccPark.is_open())
        throw std::runtime_error("Could not open file");
    fileOccPark << "Parking;Stay1;Start Date 1 ;Start Hour 1 ;End Date 1 ;End Hour 1;Stay2;Start Date 2 ;Start Hour 2 ;End Date 2 ;End Hour 2;Stay3;Start Date 3 ;Start Hour 3 ;End Date 3 ;End Hour 3;Stay4;Start Date 4 ;Start Hour 4 ;End Date 4 ;End Hour 4" << endl;
    for (long unsigned int i=0; i<tempOccParking.size(); i++) {
        fileOccPark << vectParkings[i].getName() << ";";
        // cout << "tempOccParking size : " << tempOccParking[i].size() << endl;
        for (long unsigned int j=0; j<tempOccParking[i].size(); j++) {
            Date startDate = get<0>(tempOccParking[i][j]);
            Date endDate = get<2>(tempOccParking[i][j]);
            Time startHour = get<1>(tempOccParking[i][j]);
            Time endHour = get<3>(tempOccParking[i][j]);
            int posStay = get<4>(tempOccParking[i][j]);
            fileOccPark << vectStays[posStay].getId() << ";";
            fileOccPark << startDate << ";";
            fileOccPark << startHour << ";";
            fileOccPark << endDate << ";";
            fileOccPark << endHour << ";";
        }
        fileOccPark << endl;
    }
    fileOccPark.close();

    cout << "cc3" << endl;


    // //************************************************************************************************//
    // // std::pair<double, Solution> pairGlo = rs.fonctionObjectif(solGlobal, vectParkings, vectStays);

    // // cout << "valeurGlobale : " << pairGlo.first << endl;

    // ofstream file2("test_file_2.csv");
    // if (!file2.is_open())
    //     throw std::runtime_error("Could not open file");
    // file2 << "Stay;BodyType;AircraftType;Towings;Arr_Number;Arr_Date;Arr_Hour;Dep_Number;Dep_Date;Dep_Hour;Parking 1;Contact 1;Zone 1;Start Date 1;Start Hour 1;End Date 1;End Hour 1" << endl;   
    // vector<int> vectSolGlobal2 = pairGlo.second.getSolution();
    // for (long unsigned int i = 0 ; i < vectSolGlobal2.size() ; i++) {
    //     file2 << vectStays[i].getId() << ";";
    //     file2 << vectStays[i].getBodyType() << ";";
    //     file2 << vectStays[i].getAircraftType() << ";";
    //     file2 << vectStays[i].getAuthorizedTowing() << ";";
    //     file2 << vectStays[i].getArrNumber() << ";";
    //     file2 << vectStays[i].getArrDate() << ";";
    //     file2 << vectStays[i].getArrHour() << ";";
    //     file2 << vectStays[i].getDepNumber() << ";";
    //     file2 << vectStays[i].getDepDate() << ";";
    //     file2 << vectStays[i].getDepHour() << ";";
    //     file2 << vectParkings[vectSolGlobal2[i]].getName() << ";";
    //     file2 << vectParkings[vectSolGlobal2[i]].getNature() << ";";
    //     file2 << vectParkings[vectSolGlobal2[i]].getZone() << ";";
    //     file2 << vectStays[i].getArrDate() << ";";
    //     file2 << vectStays[i].getArrHour() << ";";   
    //     file2 << vectStays[i].getDepDate() << ";";
    //     file2 << vectStays[i].getDepHour() << endl;
    // }
    // file2.close();
    
    // cout << "cc" << endl;

    // vector<vector<tuple<Date, Time, Date, Time, int>>> tempOccParking2(sizeParkings); // tableau indexe par les parkings des tableaux des tuples startDate, startHour, endDate, endHour
    // for (long unsigned int i = 0; i < vectSolGlobal2.size(); i++)
    // {
    //     Stay stay = vectStays[i];
    //     int posPark = vectSolGlobal2[i];
    //     // tempOccParking[posPark].push_back(vectParkSolution[j].getTupleStartEnd());
    //     tempOccParking2[posPark].push_back({stay.getArrDate(), stay.getArrHour(), stay.getDepDate(), stay.getDepHour(), i});
    // }
    // ofstream fileOccPark2("test_file_parking_occ2.csv");
    // if (!fileOccPark2.is_open())
    //     throw std::runtime_error("Could not open file");
    // fileOccPark2 << "Parking;Stay1;Start Date 1 ;Start Hour 1 ;End Date 1 ;End Hour 1;Stay2;Start Date 2 ;Start Hour 2 ;End Date 2 ;End Hour 2;Stay3;Start Date 3 ;Start Hour 3 ;End Date 3 ;End Hour 3;Stay4;Start Date 4 ;Start Hour 4 ;End Date 4 ;End Hour 4" << endl;
    // for (long unsigned int i=0; i<tempOccParking2.size(); i++) {
    //     fileOccPark2 << vectParkings[i].getName() << ";";
    //     // cout << "tempOccParking size : " << tempOccParking[i].size() << endl;
    //     for (long unsigned int j=0; j<tempOccParking2[i].size(); j++) {
    //         Date startDate = get<0>(tempOccParking2[i][j]);
    //         Date endDate = get<2>(tempOccParking2[i][j]);
    //         Time startHour = get<1>(tempOccParking2[i][j]);
    //         Time endHour = get<3>(tempOccParking2[i][j]);
    //         int posStay = get<4>(tempOccParking2[i][j]);
    //         fileOccPark2 << vectStays[posStay].getId() << ";";
    //         fileOccPark2 << startDate << ";";
    //         fileOccPark2 << startHour << ";";
    //         fileOccPark2 << endDate << ";";
    //         fileOccPark2 << endHour << ";";
    //     }
    //     fileOccPark2 << endl;
    // }
    // fileOccPark2.close();


    return 0;
}
