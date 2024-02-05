#include "RecuitSimule.h"
#include "Parking.h"
#include "Stay.h"
#include "fstream"
#include "sstream"
#include "Read.h"
#include "Operation.h"
#include "TXTWrite.h"
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <string>
#include "RandomizeSubset.cpp"
#include "NonAllocAndContact.cpp"
#include "SelectiveMutationSubset.cpp"
#include "Randomize.cpp"
#include "MutateMinusOne.cpp"
#include "Mutate.cpp"
#include "Swap.cpp"

using namespace std;

// string ParkingFile = "../Data/parking_2F_2DLarge.csv";
// string StaysFile = "../Data/stays_9_08_2022.csv";

// string ParkingFile = "../Data/parkings.csv";
string ParkingFile = "../Data/parkings_bis.csv";
string StaysFile = "../Data/stays_26_06_2016_bis.csv";
// string StaysFile = "../Data/stays_06_2016.csv";
int TTMA = 30;
int TTMD = 60;

int main()
{
    /**** Read Parkings ****/
    cout << "Read Parkings" << endl;
    vector<Parking> vectParkings = Read::readParkings(ParkingFile);

    /**** Read Stays ****/
    cout << "Read stays" << endl;
    vector<Stay> vectStays = Read::readStays(StaysFile);


    // From a Stay Vect to an Operation Vect
    vector<Operation> vectOperations;
    for (long unsigned int i=0; i<vectStays.size(); i++) {
        int idStay = vectStays[i].getId();
        Date arrDate = vectStays[i].getArrDate();
        Date depDate = vectStays[i].getDepDate();
        string aircraftType = vectStays[i].getAircraftType();
        pair<vector<int>,vector<int>> compatibleParkings = Read::createCompatibleParking(aircraftType, vectParkings);
        vector<int> emptyVec = {};
        int nbTowings = vectStays[i].getAuthorizedTowing();
        if (nbTowings == 0) {
            vectOperations.push_back(Operation(idStay, arrDate, depDate, compatibleParkings.first, compatibleParkings.second, 0, aircraftType));
        }
        else if (nbTowings == 1) {
            vectOperations.push_back(Operation(idStay, arrDate, arrDate+TTMA, compatibleParkings.first, compatibleParkings.second, 1, aircraftType));
            vectOperations.push_back(Operation(idStay, arrDate+TTMA, depDate, compatibleParkings.first, compatibleParkings.second, 1, aircraftType));
        }
        else if (nbTowings == 2) {
            vectOperations.push_back(Operation(idStay, arrDate, arrDate+TTMA, compatibleParkings.first, compatibleParkings.second, 2, aircraftType));
            vectOperations.push_back(Operation(idStay, arrDate+TTMA, depDate-TTMD, emptyVec, compatibleParkings.second, 3, aircraftType));  
            vectOperations.push_back(Operation(idStay, depDate-TTMD, depDate, compatibleParkings.first, compatibleParkings.second, 2, aircraftType));
        }
    }

    int nbIter = 100000;
    int nbIterT = 100;
    double T = 50;

    int sizeOperations = vectOperations.size();
    vector<int> vect(sizeOperations);
    int sizeParkings = vectParkings.size();
    cout << "Size Parkings : " << sizeParkings << endl;
    int sizeStays = vectStays.size();
    cout << "Size Stays :" << sizeStays << endl;
    cout << "Size Operations :" << sizeOperations << endl;
    Solution solutionInit = Solution(vect);
    Randomize opR(sizeParkings,solutionInit,vectOperations,vectParkings) ;
    solutionInit = *opR.apply();

    NonAllocAndContact opNAAC(sizeParkings,solutionInit,vectOperations,vectParkings);
    RandomizeSubset opRS(sizeParkings,solutionInit,vectOperations,vectParkings);
    MutateMinusOne opMMO(sizeParkings,solutionInit,vectOperations,vectParkings);
    Mutate opM(sizeParkings,solutionInit,vectOperations,vectParkings);
    Swap opS(sizeParkings,solutionInit,vectOperations,vectParkings);

    vector<Operateur*> operateurs = {&opNAAC,&opM};

    RecuitSimule rs(nbIter, nbIterT, solutionInit, operateurs, T);

    Solution solGlobal = rs.recuitSimule(vectParkings, vectOperations);


    vector<int> vectSolGlobal = solGlobal.getSolution();


    vector<vector<tuple<Date, Date, int>>> tempOccParking(sizeParkings); // tableau indexe par les parkings des tableaux des tuples startDate, startHour, endDate, endHour
    for (long unsigned int i = 0; i < vectSolGlobal.size(); i++)
    {
        Operation operation = vectOperations[i];
        int posPark = vectSolGlobal[i];
        if (posPark >= 0)
            tempOccParking[posPark].push_back({operation.getArrDate(), operation.getDepDate(), i});
    }
    ofstream fileOccPark("../dataSolution/parking_occ.csv");
    if (!fileOccPark.is_open())
        throw std::runtime_error("Could not open file");
    fileOccPark << "Parking;Stay1;Start Date 1 ;Start Hour 1 ;End Date 1 ;End Hour 1;Stay2;Start Date 2 ;Start Hour 2 ;End Date 2 ;End Hour 2;Stay3;Start Date 3 ;Start Hour 3 ;End Date 3 ;End Hour 3;Stay4;Start Date 4 ;Start Hour 4 ;End Date 4 ;End Hour 4" << endl;
    for (long unsigned int i = 0; i < tempOccParking.size(); i++)
    {
        fileOccPark << vectParkings[i].getName() << ";";
        for (long unsigned int j = 0; j < tempOccParking[i].size(); j++)
        {
            Date startDate = get<0>(tempOccParking[i][j]);
            Date endDate = get<1>(tempOccParking[i][j]);
            int posStay = get<2>(tempOccParking[i][j]);
            fileOccPark << vectOperations[posStay].getIdStay() << ";";
            fileOccPark << startDate << ";";
            fileOccPark << endDate << ";";
        }
        fileOccPark << endl;
    }
    fileOccPark.close();

    vector<tuple<int,int,int,int,int,int,int>> nonAllocatedStays;
    for (long unsigned int i = 0; i < vectSolGlobal.size(); i++) {
        if (vectSolGlobal[i] == -1) 
        {
            Operation op = vectOperations[i];
            Date stayArrDate = op.getArrDate();
            Date stayDepDate = op.getDepDate();
            nonAllocatedStays.push_back({op.getIdStay(),stayArrDate.getDay(), stayArrDate.getHour(),stayArrDate.getMin(),stayDepDate.getDay(),stayDepDate.getHour(),stayDepDate.getMin()});
            cout << op.getIdStay() << " not allocated - " << op.getAircraftType() << endl;
        }
    }
    cout << "Nb non alloc :" << nonAllocatedStays.size() << endl ;
    TXTWrite writer("nonAllocatedStays.txt") ;
    writer.write(nonAllocatedStays);

    return 0;
}