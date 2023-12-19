#include "RecuitSimule.h"
#include "Solution.h"
#include "Date.h"
// #include "Stay.h"
#include "Operation.h"
#include "Parking.h"
#include <algorithm>
#include <chrono>
#include <iostream>

using namespace std;

int _buffer = 30;

RecuitSimule::RecuitSimule(int &nbIter, int &nbIterT, Solution &solutionCourante, double T = 200) : T(T), nbIter(nbIter), nbIterT(nbIterT), solutionCourante(solutionCourante), solutionGlobal(solutionCourante) {}

Solution RecuitSimule::correctSolution(Solution solution, const vector<Parking> &vectParkings, const vector<Operation> &vectOperations)
{
    cout << "cs1" << endl;

    vector<vector<int>> vectPark = solution.getSolution();

    // cout << "Avant : " << endl;
    // for (int i = 0; i<vectStays.size()-1; i++) {
    //     cout << vectPark[i] << "|";
    // }


    int sizeParkings = vectPark.size() - 1;
    cout << "sizeParkings : " << sizeParkings << endl;

    // vector<vector<tuple<Date, Date, int>>> tempOccParking(sizeParkings); // tableau indexe par les parkings des tableaux des tuples startDate, startHour, endDate, endHour
    // for (int i = 0; i < vectPark.size(); i++)
    // {
    //     if (vectPark[i] >= 0)
    //     {
    //         tempOccParking[vectPark[i]].push_back({vectOperations[i].getArrDate(), vectOperations[i].getDepDate(), i});
    //     }
    // }

    cout << "cs2" << endl;

    int* p_buffer= nullptr;
    for (int i = 0; i < sizeParkings; i++)
    {
        int s = vectPark[i].size();
        for (int j = 0; j < s - 1; j++)
        {
            cout << "cs3" << endl;

            int posOp1 = vectPark[i][j];
            Operation op1 = vectOperations[posOp1];
            int idStay1 = op1.getIdStay();
            Date startDate1 = op1.getArrDate();
            Date endDate1 = op1.getDepDate();
            // int posStay1 = get<2>(tempOccParking[i][j]);
            for (int k = j + 1; k < s; k++)
            {
                cout << "cs4" << endl;

                int posOp2 = vectPark[i][k];
                Operation op2 = vectOperations[posOp2];
                int idStay2 = op2.getIdStay();
                Date startDate2 = op2.getArrDate();
                Date endDate2 =op2.getDepDate();
                // int posStay2 = get<2>(tempOccParking[i][k]);

                int b = _buffer;
                p_buffer = &b;
                // cout << "*p_buffer " << *p_buffer << endl;
                if (idStay1 == idStay2) {
                    int b=0;
                    p_buffer = &b;
                    // cout << "*p_buffer " << *p_buffer << endl;
                }

                if (startDate1 <= startDate2 && endDate1+*p_buffer >= startDate2)
                {   
                    cout << "cs5" << endl;

                    // vectPark[posStay2] = -1;
                    vectPark[i].erase(vectPark[i].begin()+k);
                    cout << "cs5_1" << endl;
                    
                    cout << "size : " << vectPark[sizeParkings].size() << endl;
                    for (int l=0; l<vectPark[sizeParkings].size(); l++)
                    {
                        cout << "vectPark[sizeParkings]["<<l<<"]: " << vectPark[sizeParkings][l] << endl;
                    }
                    vectPark[sizeParkings].push_back(posOp2);
                    cout << "cs5_2" << endl;

                    // cout << "Conflit1 startDate1 : " << startDate1 << " et endDate1 " << endDate1 << endl;
                    // cout << "Conflit1 startDate2 : " << startDate2 << " et endDate2 " << endDate2 << "\n"<< endl;
                }
                else if (startDate2 <= startDate1 && endDate2+*p_buffer >= startDate1)
                {
                    cout << "cs6" << endl;

                    vectPark[i].erase(vectPark[i].begin()+k);
                    cout << "cs6_1" << endl;

                    cout << "size : " << vectPark[sizeParkings].size() << endl;
                    for (int l=0; l<vectPark[sizeParkings].size(); l++)
                    {
                        cout << "vectPark[sizeParkings]["<<l<<"]: " << vectPark[sizeParkings][l] << endl;
                    }
                    vectPark[sizeParkings].push_back(posOp2);
                    cout << "cs6_2" << endl;

                    // cout << "Conflit2 startDate1 : " << startDate1 << " et endDate1 " << endDate1 << endl;
                    // cout << "Conflit2 startDate2 : " << startDate2 << " et endDate2 " << endDate2 << "\n"<< endl;
                }
            }
        }
    }
    cout << "csf" << endl;

    Solution newSolution2 = Solution(vectPark);
    // cout << "\nApres fonctionObj: " << endl;
    // for (int i = 0; i<vectOperations.size()-1; i++) {
    //     cout << newSolution2.getSolution()[i] << "|";
    // }
    cout << "csf2" << endl;

    return newSolution2;
}

double RecuitSimule::fonctionObjectif(Solution solution, const vector<Parking> &vectParkings, const vector<Operation> &vectOperations)
{
    vector<vector<int>> vectPark = solution.getSolution();

    int poids_allocation = 0;
    int poids_nature = 0;
    int sizeParkings = vectPark.size() - 1;
    for (int i = 0; i < sizeParkings; i++)
    {
        for (int j=0; j<vectPark[i].size(); j++)
        {
            Operation op = vectOperations[vectPark[i][j]];
        // int posPark = vectPark[i];
        // if (posPark == -1)
        // {
        //     poids_allocation += 100;
        // }

            // ParkNature parkNature = vectParkings[posPark].getNature();
            if (op.getNbTowing() == 3)
            {
                switch (vectParkings[i].getNature())
                case (ParkNature::Contact):
                    poids_nature += 40;
            }
            else
            {
                switch (vectParkings[i].getNature())
                case (ParkNature::Large):
                    poids_nature += 60;
            }
        }
    }
    for (int j=0; j<vectPark[sizeParkings].size(); j++) 
    {
        poids_allocation += 100;

    }
    return poids_allocation + poids_nature;
}

void RecuitSimule::majT()
{
    T *= 0.996;
}

Solution RecuitSimule::generateSolution(Solution solution, int sizeParkings, const vector<Operation> &vectOperations, const vector<Parking> &vectParkings)
{
    // solutionCourante.randomizeSubset(0,solutionCourante.getSolution().size(),sizeParkings);
    solutionCourante.randomize(vectOperations);
    // solutionCourante.mutateMinusOne(sizeParkings, vectOperations);

    // solution.NonAllocAndContact(sizeParkings, vectOperations, vectParkings);

    // solutionCourante.smartMutateMinusOne(sizeParkings);
    // cout << "generateSOlution done" << endl;
    return solution;
}

Solution RecuitSimule::recuitSimule(const vector<Parking> &vectParkings, const vector<Operation> &vectOperations)
{
    cout << "rs1" << endl;

    auto start = std::chrono::high_resolution_clock::now();

    solutionCourante = correctSolution(solutionCourante, vectParkings, vectOperations);
    double valeurCourante = fonctionObjectif(solutionCourante, vectParkings, vectOperations);

    cout << "\nValeur Initiale: " << valeurCourante << "\n\n";
    valeurGlobale = valeurCourante;
    int compt = 0;
    cout << "rs2" << endl;

    while (T > 0.001 && compt < nbIter)
    {
        for (int i = 0; i < nbIterT; ++i)
        {
            Solution newSolution = generateSolution(solutionCourante, vectParkings.size(), vectOperations, vectParkings);
            cout << "rs3" << endl;
            
            newSolution = correctSolution(newSolution, vectParkings, vectOperations);
            double nouvelleValeur = fonctionObjectif(newSolution, vectParkings, vectOperations);
            // cout << "\nNouvelle Valeur : " << nouvelleValeur << endl;
            cout << "rs4" << endl;

            double differenceValeur = nouvelleValeur - valeurCourante;
            if (differenceValeur < 0)
            {
                solutionCourante = newSolution;
                valeurCourante = nouvelleValeur;
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
                    solutionCourante = newSolution;
                    valeurCourante = nouvelleValeur;
                }
            }
        }
        compt += 1;
        majT();
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(stop - start);

    cout << "T : " << T << " | compt : " << compt << endl;
    cout << "Duration : " << time_span.count() << " seconds" << endl;
    // cout << "cc0" << endl;
    // double vGlobal = fonctionObjectif(solutionGlobal, vectParkings, vectOperations);
    // cout << "Valeur global : " << vGlobal << endl;
    cout << "Valeur globale : " << valeurGlobale << endl;
    return solutionGlobal;
}