#include "RecuitSimule.h"
#include "Solution.h"
#include "Date.h"
#include "Time.h"
// #include "Stay.h"
#include "Operation.h"
#include "Parking.h"
#include <algorithm>

using namespace std;

RecuitSimule::RecuitSimule(int &nbIter, int &nbIterT, Solution &solutionCourante, double T = 200) : T(T), nbIter(nbIter), nbIterT(nbIterT), solutionCourante(solutionCourante), solutionGlobal(solutionCourante) {}

pair<double, Solution> RecuitSimule::fonctionObjectifC(const vector<Parking> &vectParkings, const vector<Operation> &vectOperations)
{
    // return solution;
    vector<int> vectPark = solutionCourante.getSolution();

    // cout << "Avant : " << endl;
    // for (int i = 0; i<vectStays.size()-1; i++) {
    //     cout << vectPark[i] << "|";
    // }

    int sizeParkings = vectPark.size();
    // for (int i = 0; i < sizeParkings; i++)
    // {
    //     // Stay stay = vectStays[i];
    //     // Parking park = vectParkings[vectPark[i]];
    //     // cout << "cc1" << endl;
    //     int posPark = vectPark[i];
    //     if (posPark >= 0)
    //     {
    //         const vector<int> parkTypesAvion = vectParkings[vectPark[i]].getTypeAvion();
    //         // cout << "cc2" << endl;
    //         int stayTypeAvion = vectStays[i].getAircraftType();
    //         if (!parkTypesAvion.empty())
    //         {
    //             if (find(parkTypesAvion.begin(), parkTypesAvion.end(), stayTypeAvion) != parkTypesAvion.end())
    //             {
    //                 // aircraft nor compatible with the parking
    //                 vectPark[i] = -1;
    //             }
    //         }
    //     }
    // }

    vector<vector<tuple<Date, Date, int>>> tempOccParking(sizeParkings); // tableau indexe par les parkings des tableaux des tuples startDate, startHour, endDate, endHour
    for (int i = 0; i < vectPark.size(); i++)
    {
        // Stay stay = vectStays[i];
        // int posPark = vectPark[i];
        // tempOccParking[posPark].push_back(vectParkSolution[j].getTupleStartEnd());
        if (vectPark[i] >= 0)
        {
            tempOccParking[vectPark[i]].push_back({vectOperations[i].getArrDate(), vectOperations[i].getDepDate(), i});
        }
    }
    for (int i = 0; i < sizeParkings; i++)
    {
        int s = tempOccParking[i].size();
        for (int j = 0; j < s - 1; j++)
        {
            Date startDate1 = get<0>(tempOccParking[i][j]);
            Date endDate1 = get<1>(tempOccParking[i][j]);
            // Time startHour1 = get<1>(tempOccParking[i][j]);
            // Time endHour1 = get<3>(tempOccParking[i][j]);
            int posStay1 = get<2>(tempOccParking[i][j]);
            for (int k = j + 1; k < s; k++)
            {
                Date startDate2 = get<0>(tempOccParking[i][k]);
                Date endDate2 = get<1>(tempOccParking[i][k]);
                // Time startHour2 = get<1>(tempOccParking[i][k]);
                // Time endHour2 = get<3>(tempOccParking[i][k]);
                int posStay2 = get<2>(tempOccParking[i][k]);

                // if (endDate1 == startDate2)
                // {
                    // if (startHour2 <= endHour1)
                if (startDate2 <= endDate1)
                {
                    vectPark[posStay2] = -1;
                }
                else if (startDate1 <= endDate2) {
                    vectPark[posStay2] = -1;
                }
                // if (endDate2 == startDate1)
                // {
                //     if (startHour1 <= endHour2)
                //     {
                //         vectPark[posStay2] = -1;
                //     }
                // }
            }
        }
    }
    int poids_allocation = 0;
    int poids_nature = 0;
    for (int i = 0; i < vectPark.size(); i++)
    {
        // Stay stay = vectStays[i];
        int posPark = vectPark[i];
        if (posPark == -1)
        {
            poids_allocation += 100;
        }
        else
        {
            // Parking park = vectParkings[posPark];
            // ParkNature parkNature = vectParkings[posPark].getNature();
            switch (vectParkings[posPark].getNature())
            {
            case (ParkNature::Large):
                poids_nature += 50;
                break;
            }
        }
    }
    // return std::make_pair(poids_allocation + poids_nature, Solution(vectPark));
    // cout << "change1" << endl;
    Solution solutionCourant2 = Solution(vectPark);
    cout << "Apres fonctionObj: " << endl;
    for (int i = 0; i<vectOperations.size()-1; i++) {
        cout << solutionCourant2.getSolution()[i] << "|";
    }
    // cout << "change2" << endl;
    return make_pair(poids_allocation + poids_nature, solutionCourant2);
}

void RecuitSimule::majT()
{
    T *= 0.1;
}

Solution RecuitSimule::generateSolution(int sizeParkings)
{
    // return (rand() % 1000) / 100.0;
    // solutionCourante.randomizeSubset(0,solutionCourante.getSolution().size(),sizeParkings);
    solutionCourante.randomize(sizeParkings);
    return solutionCourante;
}

Solution RecuitSimule::recuitSimule(const vector<Parking> &vectParkings, const vector<Operation> &vectOperations)
{
    pair<double, Solution> pair1 = fonctionObjectifC(vectParkings, vectOperations);
    // double valeurCourante = fonctionObjectifC(vectParkings, vectStays);
    double valeurCourante = pair1.first;
    solutionCourante = pair1.second;
    cout << "Valeur Initiale: " << valeurCourante << endl;
    int compt = 0;

    while (T > 0.1 && compt < nbIter)
    {
        for (int i = 0; i < nbIterT; ++i)
        {
            Solution nouvelleSolution = generateSolution(vectParkings.size());
            solutionCourante = nouvelleSolution;
            cout << "Avant 1 " << endl;
            for (int i = 0; i<vectOperations.size()-1; i++) {
                cout << solutionCourante.getSolution()[i] << "|";
            }
            pair<double, Solution> pair2 = fonctionObjectifC(vectParkings, vectOperations);
            double nouvelleValeur = pair2.first;
            cout << "Nouvelle Valeur : " << nouvelleValeur << endl;

            double differenceValeur = nouvelleValeur - valeurCourante;
            if (differenceValeur < 0)
            {
                solutionCourante = pair2.second;
                valeurCourante = nouvelleValeur; 
                cout << "Apres 2 : " << endl;
                for (int i = 0; i<vectOperations.size()-1; i++) {
                    cout << solutionCourante.getSolution()[i] << "|";
                }
                solutionGlobal = solutionCourante;
            }
            else
            {
                if (rand() / static_cast<double>(RAND_MAX) < exp(-differenceValeur / T))
                {
                    solutionCourante = pair2.second;
                    cout << "Apres 3 : " << endl;
                    for (int i = 0; i<vectOperations.size()-1; i++) {
                        cout << solutionCourante.getSolution()[i] << "|";
                    }
                    valeurCourante = nouvelleValeur;
                }
            }
        }
        compt += 1;
        majT();
    }

    // cout << "cc0" << endl;
    // cout << "valeurGlobale : " << fonctionObjectif(solutionGlobal, vectParkings, vectStays) << endl;
    return solutionGlobal;
}