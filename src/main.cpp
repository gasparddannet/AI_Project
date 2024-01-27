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

string ParkingFile = "../Data/parkings.csv";
// string StaysFile = "../Data/stays_21_06_2016.csv";
string StaysFile = "../Data/stays_06_2016.csv";
int TTMA = 30;
int TTMD = 60;

int main()
{
    /**** Read Parkings ****/
    cout << "Read Parkings" << endl;
    vector<Parking> vectParkings = Read::readParkings(ParkingFile);


    // for (Parking &p : vectParkings) {
    //     cout << p;
    // }
    // cout << '\n';
    // cout << '\n';



    // int nbToErase = static_cast<int>(vectParkings.size()*0.1) ;
    // vectParkings.erase(vectParkings.begin(),vectParkings.begin() + nbToErase);
    // cout << "nbr de Parking supprimé: " << nbToErase << endl;



    // vectParkings.erase(vectParkings.begin()+2);

    // vectParkings[2] = vectParkings.back();
    // vectParkings.pop_back();

    // for (Parking &p : vectParkings) {
    //     cout << p;
    // }
    // cout << '\n';
    // cout << '\n';

    /**** Read Stays ****/
    cout << "Read stays" << endl;
    vector<Stay> vectStays = Read::readStays(StaysFile);

    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    // vector<int> vectorDay;
    // for (Stay &s : vectStays) {
    //     int day = s.getArrDate().getJour();
    //     if (!(std::find(vectorDay.begin(), vectorDay.end(), day) != vectorDay.end()))
    //     {
    //         vectorDay.push_back(day);
    //     }
    // }

    // for (int& d:vectorDay)
    // {
    //     cout << d << endl;
    // }

    // for (int& d:vectorDay)
    // {
    //     string filename = "../Data/stays_" + to_string(d) + "_08_2022.csv";
    //     cout << "filename : " << filename << endl;
    //     ofstream file(filename);
    //     if (!file.is_open())
    //         throw std::runtime_error("Could not open file");
    //     file << "Stay;BodyType;AircraftType;NbTowings;Arr_Number;Arr_Date;Arr_Hour;Arr_CourrierCode;Dep_Number;Dep_Date;Dep_Hour;Dep_CourrierCode" << endl;
        

    //     for (Stay &s : vectStays)
    //     {
    //         if (s.getArrDate().getJour() == d)
    //         {
    //             file << s.getId() << ";";
    //             file << s.getBodyType() << ";";
    //             file << s.getAircraftType() << ";";
    //             file << s.getAuthorizedTowing() << ";";
    //             file << s.getArrNumber() << ";";
    //             file << s.getArrDate() << ";";
    //             file << s.getArrCourrierCode() << ";";
    //             file << s.getDepNumber() << ";";
    //             file << s.getDepDate() << ";";
    //             file << s.getDepCourrierCode();
    //             file << endl;
    //         }
    //     }
    //     file.close();
    // }

    /*******************************************************************/

    // string filename = "../Data/stays_06_2016.csv";
    // ofstream file(filename);
    // if (!file.is_open())
    //     throw std::runtime_error("Could not open file");
    // file << "Stay;BodyType;AircraftType;NbTowings;Arr_Number;Arr_Date;Arr_Hour;Arr_CourrierCode;Dep_Number;Dep_Date;Dep_Hour;Dep_CourrierCode" << endl;
        
    // for (Stay &s : vectStays)
    // {
    //     file << s.getId() << ";";
    //     file << s.getBodyType() << ";";
    //     file << s.getAircraftType() << ";";
    //     file << s.getAuthorizedTowing() << ";";
    //     file << s.getArrNumber() << ";";
    //     file << s.getArrDate() << ";";
    //     file << s.getArrCourrierCode() << ";";
    //     file << s.getDepNumber() << ";";
    //     file << s.getDepDate() << ";";
    //     file << s.getDepCourrierCode();
    //     file << endl;
    // }
    // file.close();

    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/


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
            vectOperations.push_back(Operation(idStay, arrDate, depDate, compatibleParkings.first, compatibleParkings.second, 0));
        }
        else if (nbTowings == 1) {
            vectOperations.push_back(Operation(idStay, arrDate, arrDate+TTMA, compatibleParkings.first, compatibleParkings.second, 1));
            vectOperations.push_back(Operation(idStay, arrDate+TTMA, depDate, compatibleParkings.first, compatibleParkings.second, 1));
        }
        else if (nbTowings == 2) {
            vectOperations.push_back(Operation(idStay, arrDate, arrDate+TTMA, compatibleParkings.first, compatibleParkings.second, 2));
            vectOperations.push_back(Operation(idStay, arrDate+TTMA, depDate-TTMD, emptyVec, compatibleParkings.second, 3));  
            vectOperations.push_back(Operation(idStay, depDate-TTMD, depDate, compatibleParkings.first, compatibleParkings.second, 2));
        }
    }

    // for (Operation& op : vectOperations)
    // {
    //     int idStay = op.getIdStay();
    //     cout << "StayId : " << idStay;
    //     for (Stay& s: vectStays) 
    //     {
    //         if (s.getId() == idStay)
    //         {
    //             int aircraftType = s.getAircraftType();
    //             cout << " | AircraftType : " << aircraftType << endl;
    //         }
    //     }
    //     vector<int> compParking = op.getCompParkings();

    //     cout << "Park Comp : ";
    //     for (int posPark : compParking) 
    //     {
    //         cout << vectParkings[posPark];
    //     }
    //     cout << "\n\n\n";
    // }    

    // cout << endl;

    // int nbIter = 80000;
    int nbIter = 150000;
    int nbIterT = 100;
    double T = 20;

    int sizeOperations = vectOperations.size();
    vector<int> vect(sizeOperations);
    int sizeParkings = vectParkings.size();
    cout << "Size Parkings : " << sizeParkings << endl;
    int sizeStays = vectStays.size();
    cout << "Size Stays :" << sizeStays << endl;
    cout << "Size Operations :" << sizeOperations << endl;
    Solution solutionInit = Solution(vect);
    
    solutionInit.randomize(sizeParkings, vectOperations);
    // for (int i = 0; i<sizeOperations; i++) {
    //     cout << solutionInit.getSolution()[i] << "|";
    // }
    // cout << endl;
    // cout << endl;

    NonAllocAndContact opNAAC(sizeParkings,solutionInit,vectOperations,vectParkings);
    RandomizeSubset opRS(sizeParkings,solutionInit,vectOperations,vectParkings);
    MutateMinusOne opMMO(sizeParkings,solutionInit,vectOperations,vectParkings);
    Mutate opM(sizeParkings,solutionInit,vectOperations,vectParkings);
    Swap opS(sizeParkings,solutionInit,vectOperations,vectParkings);

    // vector<Operateur*> operateurs = {&opNAAC, &opRS};
    vector<Operateur*> operateurs = {&opM, &opRS};

    RecuitSimule rs(nbIter, nbIterT, solutionInit, operateurs, T);
    Solution solGlobal = rs.recuitSimule(vectParkings, vectOperations);

    cout << "\n";


    // ofstream file("../dataSolution/test_file.csv");
    // if (!file.is_open())
    //     throw std::runtime_error("Could not open file");
    // file << "Stay;BodyType;AircraftType;Towings;Arr_Number;Arr_Date;Arr_Hour;Dep_Number;Dep_Date;Dep_Hour;Parking 1;Contact 1;Zone 1;Start Date 1;Start Hour 1;End Date 1;End Hour 1" << endl;
    vector<int> vectSolGlobal = solGlobal.getSolution();
    // vector<int> vectSolGlobal = solutionInit.getSolution();

    // for (long unsigned int i = 0; i < vectSolGlobal.size(); i++)
    // {
    //     int idStay = vectOperations[i].getIdStay();
    //     vector<Stay>::iterator it;
    //     int posStay;
    //     // for (it=vectStays.begin(); it != vectStays.end(); it++) {
    //     //     if (it->getId() == idStay) {
    //     //         posStay = distance(vectStays.begin(), it);
    //     //     }
    //     // }
    //     for (long unsigned int j=0; j<vectStays.size(); j++) {
    //         if (vectStays[j].getId() == idStay) {
    //             posStay = j;
    //         }
    //     }

    //     file << vectStays[posStay].getId() << ";";
    //     file << vectStays[posStay].getBodyType() << ";";
    //     file << vectStays[posStay].getAircraftType() << ";";
    //     file << vectStays[posStay].getAuthorizedTowing() << ";";
    //     file << vectStays[posStay].getArrNumber() << ";";
    //     file << vectOperations[i].getArrDate() << ";";
    //     file << vectStays[posStay].getDepNumber() << ";";
    //     file << vectOperations[i].getDepDate() << ";";
    //     if (vectSolGlobal[i] >= 0)
    //     {
    //         file << vectParkings[vectSolGlobal[i]].getName() << ";";
    //         file << vectParkings[vectSolGlobal[i]].getNature() << ";";
    //         file << vectParkings[vectSolGlobal[i]].getZone() << ";";
    //         file << vectOperations[i].getArrDate() << ";";
    //         file << vectOperations[i].getDepDate() << ";";
    //     }
    //     else {
    //         cout << vectStays[posStay].getId() << " not allocated" << endl;
    //     }
    //     file << endl;
    // }
    // file.close();
    // // cout << "cc2" << endl;

    vector<vector<tuple<Date, Date, int>>> tempOccParking(sizeParkings); // tableau indexe par les parkings des tableaux des tuples startDate, startHour, endDate, endHour
    for (long unsigned int i = 0; i < vectSolGlobal.size(); i++)
    {
        Operation operation = vectOperations[i];
        int posPark = vectSolGlobal[i];
        // tempOccParking[posPark].push_back(vectParkSolution[j].getTupleStartEnd());
        if (posPark >= 0)
            tempOccParking[posPark].push_back({operation.getArrDate(), operation.getDepDate(), i});
    }
    ofstream fileOccPark("../dataSolution/test_file_parking_occ.csv");
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
            int posStay = get<2>(tempOccParking[i][j]);
            fileOccPark << vectOperations[posStay].getIdStay() << ";";
            fileOccPark << startDate << ";";
            fileOccPark << endDate << ";";
        }
        // cout << "ligne " << i << endl;
        fileOccPark << endl;
    }
    fileOccPark.close();



    vector<tuple<int,int,int,int,int,int,int>> nonAllocatedStays;
    for (long unsigned int i = 0; i < vectSolGlobal.size(); i++) {
        if (vectSolGlobal[i] == -1) {
            int idStay = vectOperations[i].getIdStay();
            int posStay;
            for (long unsigned int j=0; j<vectStays.size(); j++) {
                if (vectStays[j].getId() == idStay)
                {
                    posStay = j;
                }
            }
            
            Stay stay = vectStays[posStay];
            Operation op = vectOperations[i];
            Date stayArrDate = op.getArrDate();
            Date stayDepDate = op.getDepDate();
            nonAllocatedStays.push_back({stay.getId(),stayArrDate.getJour(), stayArrDate.getHour(),stayArrDate.getMin(),stayDepDate.getJour(),stayDepDate.getHour(),stayDepDate.getMin()});
        }
    }
    TXTWrite writer("nonAllocatedStays.txt") ;
    writer.write(nonAllocatedStays);

    return 0;
}