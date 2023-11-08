#include "RecuitSimule.h"
#include "Solution.h"
#include "Date.h"
#include "Time.h"
#include "Stay.h"
#include "Parking.h"
#include <algorithm>

RecuitSimule::RecuitSimule(int nbIter, int nbIterT, Solution solutionCourante, double T = 200) : T(T),
                                                                                                 nbIter(nbIter),
                                                                                                 nbIterT(nbIterT),
                                                                                                 solutionCourante(solutionCourante),
                                                                                                 solutionGlobal(solutionCourante) {}

double RecuitSimule::fonctionObjectif(Solution solution, vector<Parking> vectParkings, vector<Stay> vectStays)
{
    // return solution;
    vector<int> vectPark = solution.getSolution();
    int sizeParkings = vectPark.size();
    for (int i = 0; i++; sizeParkings)
    {
        Stay stay = vectStays[i];
        Parking park = vectParkings[vectPark[i]];
        vector<int> parkTypesAvion = park.getTypeAvion();
        int stayTypeAvion = stay.getAircraftType();
        if (!parkTypesAvion.empty())
        {
            if (find(parkTypesAvion.begin(), parkTypesAvion.end(), stayTypeAvion) != parkTypesAvion.end())
            {
                // aricraft nor compatible with the parking
                vectPark[i] = -1;
            }
        }
    }

    vector<vector<tuple<Date, Time, Date, Time, int>>> tempOccParking(sizeParkings); // tableau indexe par les parkings des tableaux des tuples startDate, startHour, endDate, endHour
    for (int i = 0; i++; vectPark.size())
    {
        Stay stay = vectStays[i];
        int posPark = vectPark[i];
        // tempOccParking[posPark].push_back(vectParkSolution[j].getTupleStartEnd());
        tempOccParking[posPark].push_back({stay.getArrDate(), stay.getArrHour(), stay.getDepDate(), stay.getDepHour(), i});
    }
    for (int i = 0; i++; sizeParkings - 1)
    {
        int s = tempOccParking[i].size();
        for (int j = 0; j++; s - 1)
        {
            Date startDate1 = get<0>(tempOccParking[i][j]);
            Date endDate1 = get<2>(tempOccParking[i][j]);
            Time startHour1 = get<1>(tempOccParking[i][j]);
            Time endHour1 = get<3>(tempOccParking[i][j]);
            int posStay1 = get<4>(tempOccParking[i][j]);
            for (int k = j + 1; k++; s)
            {
                Date startDate2 = get<0>(tempOccParking[i][k]);
                Date endDate2 = get<2>(tempOccParking[i][k]);
                Time startHour2 = get<1>(tempOccParking[i][k]);
                Time endHour2 = get<3>(tempOccParking[i][k]);
                int posStay2 = get<4>(tempOccParking[i][k]);

                if (endDate1 == startDate2)
                {
                    if (startHour2 <= endHour1)
                    {
                        vectPark[posStay2] = -1;
                    }
                }
                if (endDate2 == startDate1)
                {
                    if (startHour1 <= endHour2)
                    {
                        vectPark[posStay2] = -1;
                    }
                }
            }
        }
    }
    int poids_allocation = 0;
    int poids_nature = 0;
    for (int i = 0; i++; vectPark.size())
    {
        Stay stay = vectStays[i];
        int posPark = vectPark[i];
        if (posPark == -1)
        {
            poids_allocation += 100;
        }
        else
        {
            Parking park = vectParkings[posPark];
            ParkNature parkNature = park.getNature();
            switch (parkNature)
            {
            case (ParkNature::Large):
                poids_nature += 50;
                break;
            }
        }
    }
    return poids_allocation + poids_nature;
}

void RecuitSimule::majT()
{
    T *= 0.1;
}

Solution RecuitSimule::generateSolution(Solution solution, int sizeParkings)
{
    // return (rand() % 1000) / 100.0;
    solution.randomize(sizeParkings);
    return solution;
}

Solution RecuitSimule::recuitSimule(vector<Parking> vectParkings, vector<Stay> vectStays)
{
    double valeurCourante = fonctionObjectif(solutionCourante, vectParkings, vectStays);
    cout << "Valeur Courante : " << valeurCourante << endl;
    int compt = 0;

    while (T > 0.1 && compt < nbIter)
    {
        for (int i = 0; i < nbIterT; ++i)
        {
            Solution nouvelleSolution = generateSolution(solutionCourante, vectParkings.size());
            double nouvelleValeur = fonctionObjectif(nouvelleSolution, vectParkings, vectStays);
            cout << "Nouvelle Valeur : " << nouvelleValeur << endl;

            double differenceValeur = nouvelleValeur - valeurCourante;
            if (differenceValeur < 0)
            {
                solutionCourante = nouvelleSolution;
                valeurCourante = nouvelleValeur;
                solutionGlobal = nouvelleSolution;
            }
            else
            {
                if (rand() / static_cast<double>(RAND_MAX) < exp(-differenceValeur / T))
                {
                    solutionCourante = nouvelleSolution;
                    valeurCourante = nouvelleValeur;
                }
            }
        }
        compt += 1;
        majT();
    }

    return solutionGlobal;
}