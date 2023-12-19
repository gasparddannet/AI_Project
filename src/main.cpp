#include "RecuitSimule.h"
#include "Parking.h"
#include "Stay.h"
#include "fstream"
#include "sstream"
#include "Read.h"
#include "Operation.h"
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <string>

using namespace std;

string ParkingFile = "../Data/parking_2F_2DLarge.csv";
string StaysFile = "../Data/stays_2F_090822.csv";
int TTMA = 30;
int TTMD = 60;

int main()
{

    // int j,m,a,h,min;
    // int j2,m2,a2,h2,min2;
    // int j3,m3,a3,h3,min3;
    // int j4,m4,a4,h4,min4;

    // j=9;m=8;a=2022;h=9;min=10;
    // j2=9;m2=8;a2=2022;h2=9;min2=40;
    // j3=9;m3=8;a3=2022;h3=19;min3=45;
    // j4=9;m4=8;a4=2022;h4=20;min4=45;



    // Date d1 = Date(j,m,a,h,min);
    // cout << "Date 1 : " << d1 << endl;
    // Date d2 = Date(j2,m2,a2,h2,min2);
    // cout << "Date 2 : " << d2 << endl;

    // Date d3 = Date(j3,m3,a3,h3,min3);
    // Date d4 = Date(j4,m4,a4,h4,min4);
    // cout << "Date 3 : " << d3 << endl;
    // cout << "Date 4 : " << d4 << endl;


    // Date d5 = d1 + 30;
    // cout << "Date 1 - 30 :" << d5 << endl;

    // bool b = d3 <= d4;
    // cout << "bool d3 <= d4 : " << b << endl;
    // bool b1 = d4 <= d3;
    // cout << "bool d4 <= d3 : " << b1 << endl;
    // if (b) 
    // {
    //     cout << "vrai" << endl;
    // }




    /**** Read Parkings ****/
    cout << "Read Parkings" << endl;
    vector<Parking> vectParkings = Read::readParkings(ParkingFile);


    // for (Parking &p : vectParkings) {
    //     cout << p;
    // }
    // cout << '\n';
    // cout << '\n';

    // std::shuffle(vectParkings.begin(), vectParkings.end(), std::default_random_engine());
    // int tronc = static_cast<int>(vectParkings.size()*0.8) ;
    //vectParkings.resize(tronc);
    int nbToErase = static_cast<int>(vectParkings.size()*0.1) ;
    // vectParkings.resize(tronc);

    vectParkings.erase(vectParkings.begin(),vectParkings.begin() + nbToErase);


    cout << "nbr de Parking supprimé: " << nbToErase << endl;

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
            vectOperations.push_back(Operation(idStay, arrDate, depDate, compatibleParkings, 0));
        }
        else if (nbTowings == 1) {
            vectOperations.push_back(Operation(idStay, arrDate, arrDate+TTMA, compatibleParkings, 1));
            vectOperations.push_back(Operation(idStay, arrDate+TTMA, depDate, compatibleParkings, 1));
        }
        else if (nbTowings == 2) {
            vectOperations.push_back(Operation(idStay, arrDate, arrDate+TTMA, compatibleParkings, 2));
            vectOperations.push_back(Operation(idStay, arrDate+TTMA, depDate-TTMD, compatibleParkings, 3));  
            vectOperations.push_back(Operation(idStay, depDate-TTMD, depDate, compatibleParkings, 2));
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

    int nbIter = 60000;
    int nbIterT = 20;
    double T = 600;

    int sizeOperations = vectOperations.size();
    vector<int> vect(sizeOperations);
    int sizeParkings = vectParkings.size();
    cout << "SizeParkings : " << sizeParkings << endl;

    Solution solutionInit = Solution(vect);
    
    solutionInit.randomize(sizeParkings, vectOperations);
    // for (int i = 0; i<sizeOperations; i++) {
    //     cout << solutionInit.getSolution()[i] << "|";
    // }
    // cout << endl;
    // cout << endl;

    RecuitSimule rs(nbIter, nbIterT, solutionInit, T);
    Solution solGlobal = rs.recuitSimule(vectParkings, vectOperations);

    cout << "\n";


    ofstream file("../DataSolution/test_file.csv");
    if (!file.is_open())
        throw std::runtime_error("Could not open file");
    file << "Stay;BodyType;AircraftType;Towings;Arr_Number;Arr_Date;Arr_Hour;Dep_Number;Dep_Date;Dep_Hour;Parking 1;Contact 1;Zone 1;Start Date 1;Start Hour 1;End Date 1;End Hour 1" << endl;
    vector<int> vectSolGlobal = solGlobal.getSolution();
    // vector<int> vectSolGlobal = solutionInit.getSolution();

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
        for (long unsigned int j=0; j<vectStays.size(); j++) {
            if (vectStays[j].getId() == idStay) {
                posStay = j;
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
        else {
            cout << vectStays[posStay].getId() << " not allocated" << endl;
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
    ofstream fileOccPark("../DataSolution/test_file_parking_occ.csv");
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



    vector<tuple<int,int,int,int,int>> nonAllocatedStays;
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
            nonAllocatedStays.push_back({stay.getId(),stayArrDate.getHour(),stayArrDate.getMin(),stayDepDate.getHour(),stayDepDate.getMin()});
        }
    }
    std::ofstream outputFile("../DataSolution/nonAllocatedStays.txt");
    for (const auto& tuple : nonAllocatedStays) {
        outputFile << std::get<0>(tuple) << ' ' << std::get<1>(tuple) << ' ' << std::get<2>(tuple) << ' ' << std::get<3>(tuple) << 
        ' ' << std::get<4>(tuple) <<'\n';
    }
    outputFile.close();

    return 0;
}