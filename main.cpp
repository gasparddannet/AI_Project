#include "RecuitSimule.h"
#include "Parking.h"
#include "Stay.h"
#include "fstream"
#include "sstream"
#include "Read.h"
#include "Operation.h"
#include <vector>
#include <algorithm>

using namespace std;

string ParkingFile = "Data/parking_2F_2DLarge.csv";
string StaysFile = "Data/stays_2F_090822.csv";
int TTMA = 30;
int TTMD = 60;

int main()
{
    /**** Read Parkings ****/
    cout << "Read Parkings" << endl;
    vector<Parking> vectParkings = Read::readParkings(ParkingFile);

    // for (Parking &p : vectParking) {
    //     cout << p;
    // }
    // cout << '\n';
    // cout << '\n';

    /**** Read Stays ****/
    cout << "Read stays" << endl;
    vector<Stay> vectStays = Read::readStays(StaysFile);

    // for (Stay &s : vectStays) {
    //     cout << s;
    // }

    // From a Stay Vect to an Operation Vect
    vector<Operation> vectOperations;
    for (long unsigned int i=0; i<vectStays.size(); i++) {
        int idStay = vectStays[i].getId();
        Date arrDate = vectStays[i].getArrDate();
        Date depDate = vectStays[i].getDepDate();
        int aircraftType = vectStays[i].getAircraftType();
        vector<int> compatibleParkings = Read::createCompatibleParking(aircraftType, vectParkings);
        int nbTowings = vectStays[i].getAuthorizedTowing();
        if (nbTowings == 0) {
            vectOperations.push_back(Operation(idStay, arrDate, depDate, compatibleParkings));
        }
        else if (nbTowings == 1) {
            vectOperations.push_back(Operation(idStay, arrDate, arrDate+TTMA, compatibleParkings));
            vectOperations.push_back(Operation(idStay, arrDate+TTMA, depDate, compatibleParkings));
        }
        else if (nbTowings == 2) {
            vectOperations.push_back(Operation(idStay, arrDate, arrDate+TTMA, compatibleParkings));
            vectOperations.push_back(Operation(idStay, arrDate+TTMA, depDate-TTMD, compatibleParkings));  
            vectOperations.push_back(Operation(idStay, depDate-TTMD, depDate, compatibleParkings));
        }
    }

    int nbIter = 100;
    int nbIterT = 100;
    int sizeOperations = vectOperations.size();
    vector<int> vect(sizeOperations);
    int sizeParkings = vectParkings.size();

    Solution solutionInit = Solution(vect);
    
    // cout << "size : " << solutionInit.getSolution().size() << endl;
    // cout << endl;
    // for (int i = 0; i<sizeStays-1; i++) {
    //     cout << solutionInit.getSolution()[i] << "|";
    // }
    // cout << endl;
    // cout << endl;

    // solutionInit.randomizeSubset(0, sizeStays-1, sizeParkings);
    // for (int i = 0; i<sizeStays-1; i++) {
    //     cout << solutionInit.getSolution()[i] << "|";
    // }
    // cout << endl;
    // cout << endl;
    
    solutionInit.randomize(sizeParkings, vectOperations);
    for (int i = 0; i<sizeOperations; i++) {
        cout << solutionInit.getSolution()[i] << "|";
    }
    cout << endl;
    cout << endl;

    double T = 200;
    RecuitSimule rs(nbIter, nbIterT, solutionInit, T);
    Solution solGlobal = rs.recuitSimule(vectParkings, vectOperations);

    cout << "\n" << endl;

    // double finesseGlobal = RecuitSimule::fonctionObjectif(solGlobal, vectParkings, vectStays);
    // cout << "finesse Globales : " << finesseGlobal << endl;
    // cout << "cc1" << endl;

    // std::pair<double, Solution> pairGlo = rs.fonctionObjectif(solGlobal, vectParkings, vectStays);

    // cout << "valeurGlobale : " << pairGlo.first << endl;

    ofstream file("test_file.csv");
    if (!file.is_open())
        throw std::runtime_error("Could not open file");
    file << "Stay;BodyType;AircraftType;Towings;Arr_Number;Arr_Date;Arr_Hour;Dep_Number;Dep_Date;Dep_Hour;Parking 1;Contact 1;Zone 1;Start Date 1;Start Hour 1;End Date 1;End Hour 1" << endl;
    vector<int> vectSolGlobal = solGlobal.getSolution();
    for (long unsigned int i = 0; i < vectSolGlobal.size(); i++)
    {
        int idStay = vectOperations[i].getIdStay();
        vector<Stay>::iterator it;
        int posStay;
        // for (it=vectStays.begin(); it != vectStays.end(); it++) {
        //     if (it->getId() == idStay) {
        //         posStay = distance(vectStays.begin(), it);
        //     }
        // }
        for (long unsigned int i=0; i<vectStays.size(); i++) {
            if (vectStays[i].getId() == idStay) {
                posStay = i;
            }
        }

        file << vectStays[posStay].getId() << ";";
        file << vectStays[posStay].getBodyType() << ";";
        file << vectStays[posStay].getAircraftType() << ";";
        file << vectStays[posStay].getAuthorizedTowing() << ";";
        file << vectStays[posStay].getArrNumber() << ";";
        file << vectOperations[i].getArrDate() << ";";
        file << vectStays[posStay].getDepNumber() << ";";
        file << vectOperations[i].getDepDate() << ";";
        if (vectSolGlobal[i] >= 0)
        {
            file << vectParkings[vectSolGlobal[i]].getName() << ";";
            file << vectParkings[vectSolGlobal[i]].getNature() << ";";
            file << vectParkings[vectSolGlobal[i]].getZone() << ";";
            file << vectOperations[i].getArrDate() << ";";
            file << vectOperations[i].getDepDate() << ";";
        }
        file << endl;
    }
    file.close();
    // cout << "cc2" << endl;

    vector<vector<tuple<Date, Date, int>>> tempOccParking(sizeParkings); // tableau indexe par les parkings des tableaux des tuples startDate, startHour, endDate, endHour
    for (long unsigned int i = 0; i < vectSolGlobal.size(); i++)
    {
        Operation operation = vectOperations[i];
        int posPark = vectSolGlobal[i];
        // tempOccParking[posPark].push_back(vectParkSolution[j].getTupleStartEnd());
        if (posPark >= 0)
            tempOccParking[posPark].push_back({operation.getArrDate(), operation.getDepDate(), i});
    }
    ofstream fileOccPark("test_file_parking_occ.csv");
    if (!fileOccPark.is_open())
        throw std::runtime_error("Could not open file");
    fileOccPark << "Parking;Stay1;Start Date 1 ;Start Hour 1 ;End Date 1 ;End Hour 1;Stay2;Start Date 2 ;Start Hour 2 ;End Date 2 ;End Hour 2;Stay3;Start Date 3 ;Start Hour 3 ;End Date 3 ;End Hour 3;Stay4;Start Date 4 ;Start Hour 4 ;End Date 4 ;End Hour 4" << endl;
    for (long unsigned int i = 0; i < tempOccParking.size(); i++)
    {
        fileOccPark << vectParkings[i].getName() << ";";
        // cout << "tempOccParking size : " << tempOccParking[i].size() << endl;
        for (long unsigned int j = 0; j < tempOccParking[i].size(); j++)
        {
            Date startDate = get<0>(tempOccParking[i][j]);
            Date endDate = get<1>(tempOccParking[i][j]);
            // Time startHour = get<1>(tempOccParking[i][j]);
            // Time endHour = get<3>(tempOccParking[i][j]);
            int posStay = get<2>(tempOccParking[i][j]);
            fileOccPark << vectOperations[posStay].getIdStay() << ";";
            fileOccPark << startDate << ";";
            // fileOccPark << startHour << ";";
            fileOccPark << endDate << ";";
            // fileOccPark << endHour << ";";
        }
        // cout << "ligne " << i << endl;
        fileOccPark << endl;
    }
    fileOccPark.close();

    // vector<tuple<int,int,int,int,int>> nonAllocatedStays;
    // for (long unsigned int i = 0; i < vectSolGlobal.size(); i++) {
    //     if (vectSolGlobal[i] == -1) {
    //         Stay stay = vectStays[i];
    //         Date stayArrDate = stay.getArrDate();
    //         Date stayDepDate = stay.getDepDate();
    //         nonAllocatedStays.push_back({stay.getId(),stayArrDate.getHour(),stayArrDate.getMin(),stayDepDate.getHour(),stayDepDate.getMin()});
    //     }
    // }
    // std::ofstream outputFile("nonAllocatedStays.txt");
    // for (const auto& tuple : nonAllocatedStays) {
    //     outputFile << std::get<0>(tuple) << ' ' << std::get<1>(tuple) << ' ' << std::get<2>(tuple) << ' ' << std::get<3>(tuple) << 
    //     ' ' << std::get<4>(tuple) <<'\n';
    // }
    // outputFile.close();

    return 0;
}
