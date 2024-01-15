#include "RecuitSimule.h"
#include "Solution.h"
#include "Date.h"
// #include "Stay.h"
#include "Operation.h"
#include "Parking.h"
#include "TXTWrite.h"
#include <algorithm>
#include <chrono>
#include <string>

using namespace std;

int _buffer = 20;

RecuitSimule::RecuitSimule(int &nbIter, int &nbIterT, Solution &solutionCourante, Operateur* opNAAC, Operateur* opRS, double T = 200) : T(T), nbIter(nbIter), nbIterT(nbIterT), solutionCourante(solutionCourante), solutionGlobal(solutionCourante), opNAAC(opNAAC), opRS(opRS) {}



Solution RecuitSimule::correctSolution(Solution solution, const vector<Parking> &vectParkings, const vector<Operation> &vectOperations)
{   
    // cout << "Call correctSolution" << endl;
    vector<int> vectPark = solution.getSolution();

    // cout << "Avant : " << endl;
    // for (int i = 0; i<vectStays.size()-1; i++) {
    //     cout << vectPark[i] << "|";
    // }

    int sizeParkings = vectPark.size();

    vector<vector<tuple<Date, Date, int>>> tempOccParking(sizeParkings); // tableau indexe par les parkings des tableaux des tuples startDate, startHour, endDate, endHour
    for (int i = 0; i < vectPark.size(); i++)
    {   
        vector<int> compPark = vectOperations[i].getCompParkings() ;  
        auto it = find(compPark.begin(), compPark.end(), vectPark[i]);
        if (it == compPark.end()) {
            vectPark[i] = -1 ; // Les opérations ne respectant pas la contrainte de compatibilité parking sont changés à -1
        }

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
            int posStay1 = get<2>(tempOccParking[i][j]);
            for (int k = j + 1; k < s; k++)
            {
                Date startDate2 = get<0>(tempOccParking[i][k]);
                Date endDate2 = get<1>(tempOccParking[i][k]);
                int posStay2 = get<2>(tempOccParking[i][k]);

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
            }
        }
    }
    Solution newSolution2 = Solution(vectPark);
    // cout << "\nApres fonctionObj: " << endl;
    // for (int i = 0; i<vectOperations.size()-1; i++) {
    //     cout << newSolution2.getSolution()[i] << "|";
    // }
    return newSolution2;
}

double RecuitSimule::fonctionObjectif(Solution solution, const vector<Parking> &vectParkings, const vector<Operation> &vectOperations)
{
    vector<int> vectPark = solution.getSolution();

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
            // ParkNature parkNature = vectParkings[posPark].getNature();
            if (op.getNbTowing() == 3)
            {
                switch (vectParkings[posPark].getNature())
                case (ParkNature::Contact):
                    poids_nature += 40;
            }
            else
            {
                switch (vectParkings[posPark].getNature())
                case (ParkNature::Large):
                    poids_nature += 60;
            }
        }
    }
    return poids_allocation + poids_nature;
}

void RecuitSimule::majT(int &acc)
{
    if (T < exp(-acc)) {
        T += 400/acc  ;
        acc += 1 ;
    }
    T *= 0.996;
}

Solution RecuitSimule::generateSolution(Solution solution, int compt)
{
    // if (operateur == "randomize" ) {
    //     solution.randomize(sizeParkings, vectOperations);
    // }
    // else if (operateur == "NonAllocAndContact" ) {
    //     solution.NonAllocAndContact(sizeParkings, vectOperations, vectParkings);
    // }
    // else if (operateur == "mutateMinusOne" ) {
    //     solution.mutateMinusOne(sizeParkings, vectOperations);
    // }
    // solutionCourante.randomizeSubset(0,solutionCourante.getSolution().size(),sizeParkings);
    //solution.randomize(sizeParkings, vectOperations);
    // solution.mutateMinusOne(sizeParkings, vectOperations);

    // solution.NonAllocAndContact(sizeParkings,vectOperations,vectParkings);

    Solution *sol;
    if (compt % 100 == 0)
    {
        opNAAC->setSolution(solution);
        *sol = opNAAC->apply();
    }

    else 
    {
        opRS->setSolution(solution);
        *sol = opRS->apply();
    }

    // solution.smartMutateMinusOne(sizeParkings);
    // cout << "generateSOlution done" << endl;
    return *sol;
}

Solution RecuitSimule::recuitSimule(const vector<Parking> &vectParkings, const vector<Operation> &vectOperations)
{
    auto start = std::chrono::high_resolution_clock::now();

    solutionCourante = correctSolution(solutionCourante, vectParkings, vectOperations);
    double valeurCourante = fonctionObjectif(solutionCourante, vectParkings, vectOperations);

    std::cout << "\nValeur Initiale: " << valeurCourante << "\n\n";
    valeurGlobale = valeurCourante;
    int compt = 0;
    int acc = 1;
    vector<double> histoT ;
    vector<tuple<int,int>> histoVal ;
    while (T > 0.001 && compt < nbIter)
    {
        for (int i = 0; i < nbIterT; ++i)
        {
            Solution newSolution = generateSolution(solutionCourante, compt);
            
            newSolution = correctSolution(newSolution, vectParkings, vectOperations);
            double nouvelleValeur = fonctionObjectif(newSolution, vectParkings, vectOperations);
            // cout << "\nNouvelle Valeur : " << nouvelleValeur << endl;

            if (nouvelleValeur == 0)
            {
                solutionGlobal = solutionCourante;
                valeurGlobale = nouvelleValeur;
                auto stop = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
                chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(stop - start);

                std::cout << "T : " << T << " | compt : " << compt << endl;
                std::cout << "Duration : " << time_span.count() << " seconds" << endl;
                std::cout << "Valeur globale : " << valeurGlobale << endl;
                return solutionGlobal;
                     
            }

            if (nouvelleValeur - valeurGlobale < 0) {
                solutionCourante = newSolution;
                valeurCourante = nouvelleValeur;
                solutionGlobal = solutionCourante;
                valeurGlobale = nouvelleValeur;
                std::cout << "change valeur Globale :" << valeurGlobale << endl;
            }

            double differenceValeur = nouvelleValeur - valeurCourante;
            if (differenceValeur < 0)
            {
                solutionCourante = newSolution;
                valeurCourante = nouvelleValeur;
                // solutionGlobal = solutionCourante;
                // valeurGlobale = nouvelleValeur;
                // cout << "change valeur Globale :" << valeurGlobale << endl;
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
            compt += 1;
        }
        histoT.push_back(T);
        majT(acc);
        histoVal.push_back({valeurCourante,valeurGlobale}) ;
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(stop - start);

    std::cout << "T : " << T << " | compt : " << compt << endl;
    std::cout << "Duration : " << time_span.count() << " seconds" << endl;
    // cout << "cc0" << endl;
    // double vGlobal = fonctionObjectif(solutionGlobal, vectParkings, vectOperations);
    // cout << "Valeur global : " << vGlobal << endl;
    std::cout << "Valeur globale : " << valeurGlobale << endl;

    TXTWrite writer("histoT.txt");
    writer.write(histoT);
    // cout << "Nom opérateur :" << operateur->getName() << endl ;

    // if (operateur->getName() == "Randomize") {
    //     writer.setFilename("histoValR.txt") ;
    // }
    // else if (operateur->getName() == "NonAllocAndContact") {
    //     writer.setFilename("histoValNAAC.txt") ;
    // }
    // else if (operateur->getName() == "MutateMinusOne") {
    //     writer.setFilename("histoValMMO.txt") ;
    // }
    // else if (operateur->getName() == "RandomizeSubset") {
    //     writer.setFilename("histoValRS.txt") ;
    // }
    // else if (operateur->getName() == "SelectiveMutationSubset") {
    //     writer.setFilename("histoValSMS.txt") ;
    // }
    // writer.write(histoVal, operateur->getName()) ;


    writer.setFilename("histoVaRSandNAAC.txt");
    writer.write(histoVal, "RSandNAAX");
    return solutionGlobal;
}