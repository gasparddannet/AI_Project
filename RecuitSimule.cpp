#include "RecuitSimule.h"
#include "Solution.h"
#include "Date.h"
// #include "Stay.h"
#include "Operation.h"
#include "Parking.h"
#include <algorithm>
#include <chrono>

using namespace std;

int _buffer = 30;

RecuitSimule::RecuitSimule(int &nbIter, int &nbIterT, Solution &solutionCourante, double T = 200) : T(T), nbIter(nbIter), nbIterT(nbIterT), solutionCourante(solutionCourante), solutionGlobal(solutionCourante) {}

pair<double, Solution> RecuitSimule::fonctionObjectifC(Solution solution, const vector<Parking> &vectParkings, const vector<Operation> &vectOperations)
{
    // return solution;
    vector<int> vectPark = solution.getSolution();

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

    int* p_buffer= nullptr;
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
                int b = _buffer;
                p_buffer = &b;
                // cout << "*p_buffer " << *p_buffer << endl;
                if (vectOperations[posStay1].getIdStay() == vectOperations[posStay2].getIdStay()) {
                    int b=0;
                    p_buffer = &b;
                    // cout << "*p_buffer " << *p_buffer << endl;
                }

                if (startDate1 <= startDate2 && endDate1+*p_buffer >= startDate2)
                {
                    vectPark[posStay2] = -1;
                    // cout << "Conflit1 startDate1 : " << startDate1 << " et endDate1 " << endDate1 << endl;
                    // cout << "Conflit1 startDate2 : " << startDate2 << " et endDate2 " << endDate2 << "\n"<< endl;
                }
                else if (startDate2 <= startDate1 && endDate2+*p_buffer >= startDate1)
                {
                    vectPark[posStay2] = -1;
                    // cout << "Conflit2 startDate1 : " << startDate1 << " et endDate1 " << endDate1 << endl;
                    // cout << "Conflit2 startDate2 : " << startDate2 << " et endDate2 " << endDate2 << "\n"<< endl;
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
        Operation op = vectOperations[i];
        int posPark = vectPark[i];
        if (posPark == -1)
        {
            poids_allocation += 100;
        }
        else
        {
            // Parking park = vectParkings[posPark];
            // ParkNature parkNature = vectParkings[posPark].getNature();

            if (op.getNbTowing() == 3)
            {
                switch (vectParkings[posPark].getNature())
                case (ParkNature::Contact):
                    poids_nature += 40;
                // break;
            }
            else
            {
                switch (vectParkings[posPark].getNature())
                case (ParkNature::Large):
                    poids_nature += 60;
                // break;
            }
        }
    }
    // return std::make_pair(poids_allocation + poids_nature, Solution(vectPark));
    // cout << "change1" << endl;
    Solution newSolution2 = Solution(vectPark);

    // cout << "\nApres fonctionObj: " << endl;
    // for (int i = 0; i<vectOperations.size()-1; i++) {
    //     cout << solutionCourant2.getSolution()[i] << "|";
    // }

    // cout << "change2" << endl;
    return make_pair(poids_allocation + poids_nature, newSolution2);
}

void RecuitSimule::majT()
{
    T *= 0.998;
}

Solution RecuitSimule::generateSolution(Solution solution, int sizeParkings, const vector<Operation> &vectOperations, const vector<Parking> &vectParkings)
{
    // return (rand() % 1000) / 100.0;
    // solutionCourante.randomizeSubset(0,solutionCourante.getSolution().size(),sizeParkings);
    // solutionCourante.randomize(sizeParkings, vectOperations);
    // solutionCourante.mutateMinusOne(sizeParkings, vectOperations);

    solution.NonAllocAndContact(sizeParkings, vectOperations, vectParkings);

    // solutionCourante.smartMutateMinusOne(sizeParkings);
    // cout << "generateSOlution done" << endl;
    return solution;
}

Solution RecuitSimule::recuitSimule(const vector<Parking> &vectParkings, const vector<Operation> &vectOperations)
{
    auto start = std::chrono::high_resolution_clock::now();
    // const auto start{std::chrono::steady_clock::now()};

    pair<double, Solution> pair1 = fonctionObjectifC(solutionCourante, vectParkings, vectOperations);
    // double valeurCourante = fonctionObjectifC(vectParkings, vectStays);
    double valeurCourante = pair1.first;
    solutionCourante = pair1.second;
    cout << "\nValeur Initiale: " << valeurCourante << "\n\n";
    valeurGlobale = valeurCourante;
    int compt = 0;

    while (T > 0.1 && compt < nbIter)
    {
        for (int i = 0; i < nbIterT; ++i)
        {
            // Solution nouvelleSolution = generateSolution(vectParkings.size(), vectOperations);
            // solutionCourante = nouvelleSolution;
            // solutionCourante = generateSolution(vectParkings.size(), vectOperations, vectParkings);
            Solution newSolution = generateSolution(solutionCourante, vectParkings.size(), vectOperations, vectParkings);
            
            
            // cout << "\nAvant 1 " << endl;
            // for (int i = 0; i<vectOperations.size(); i++) {
            //     cout << solutionCourante.getSolution()[i] << "|";
            // }
            pair<double, Solution> pair2 = fonctionObjectifC(newSolution, vectParkings, vectOperations);
            double nouvelleValeur = pair2.first;
            // cout << "\nNouvelle Valeur : " << nouvelleValeur << endl;

            double differenceValeur = nouvelleValeur - valeurCourante;
            if (differenceValeur < 0)
            {
                solutionCourante = pair2.second;
                valeurCourante = nouvelleValeur;
                // cout << "\nApres 2 : " << endl;
                // for (int i = 0; i<vectOperations.size()-1; i++) {
                //     cout << solutionCourante.getSolution()[i] << "|";
                // }
                solutionGlobal = solutionCourante;
                valeurGlobale = nouvelleValeur;
                // cout << "change valeugGlobale" << endl;
            }
            else
            {
                // cout << "difV : " << differenceValeur << endl;
                // cout << "rand : " << rand() / static_cast<double>(RAND_MAX) << " | exp : " << exp(-differenceValeur / T) << endl;
                if (rand() / static_cast<double>(RAND_MAX) < exp(-differenceValeur / T))
                {
                    // cout << "passe" << endl;
                    solutionCourante = pair2.second;
                    // cout << "\nApres 3 : " << endl;
                    // for (int i = 0; i<vectOperations.size()-1; i++) {
                    //     cout << solutionCourante.getSolution()[i] << "|";
                    // }
                    valeurCourante = nouvelleValeur;
                }
            }
        }
        compt += 1;
        majT();
    }
    auto stop = chrono::high_resolution_clock::now();
    // const auto end{std::chrono::steady_clock::now()};
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    // const std::chrono::duration<double> elapsed_seconds{stop - start};
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(stop - start);

    cout << "T : " << T << " | compt : " << compt << endl;
    cout << "Duration : " << time_span.count() << " seconds" << endl;
    // cout << "cc0" << endl;
    // pair<double, Solution> pair = fonctionObjectifC(solutionGlobal, vectParkings, vectOperations);
    // cout << "Valeur global : " << pair.first << endl;
    cout << "Valeur globale : " << valeurGlobale << endl;
    return solutionGlobal;
}