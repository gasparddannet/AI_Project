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
#include <random>

using namespace std;

int _buffer = 20;

RecuitSimule::RecuitSimule(int &nbIter, int &nbIterT, Solution &solutionCourante, vector<Operateur*> operateurs, double T = 200) : T(T), nbIter(nbIter), nbIterT(nbIterT), solutionCourante(solutionCourante), solutionGlobal(solutionCourante), operateurs(operateurs) {}

Solution RecuitSimule::correctSolution(Solution solution, const vector<Parking> &vectParkings, const vector<Operation> &vectOperations)
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> rdistribution(0, 1);
  
    // cout << "Call correctSolution" << endl;
    vector<int> sol = solution.getSolution();

    // cout << "Avant : " << endl;
    // for (int i = 0; i<vectStays.size()-1; i++) {
    //     cout << vectPark[i] << "|";
    // }

    int sizeParkings = vectParkings.size();

    vector<vector<tuple<Date, Date, int>>> tempOccParking(sizeParkings); // tableau indexe par les parkings des tableaux des tuples startDate, startHour, endDate, endHour
    for (int i = 0; i < sol.size(); i++)
    {
        vector<int> compPark = vectOperations[i].getCompParkings();
        auto it = find(compPark.begin(), compPark.end(), sol[i]);
        if (it == compPark.end())
        {
            sol[i] = -1; // Les opérations ne respectant pas la contrainte de compatibilité parking sont changés à -1
        }

        if (sol[i] >= 0)
        {
            tempOccParking[sol[i]].push_back({vectOperations[i].getArrDate(), vectOperations[i].getDepDate(), i});
        }
    }

    int *p_buffer = nullptr;
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
                if (vectOperations[posStay1].getIdStay() == vectOperations[posStay2].getIdStay())
                {
                    int b = 0;
                    p_buffer = &b;
                    // cout << "*p_buffer " << *p_buffer << endl;
                }

                if (startDate1 <= startDate2 && endDate1 + *p_buffer >= startDate2)
                {
                    int r = rdistribution(generator);
                    if (r==1)
                    {
                        sol[posStay2] = -1;
                    }
                    else 
                    {
                        sol[posStay1] = -1;
                    }
                    // cout << "Conflit1 startDate1 : " << startDate1 << " et endDate1 " << endDate1 << endl;
                    // cout << "Conflit1 startDate2 : " << startDate2 << " et endDate2 " << endDate2 << "\n"<< endl;
                }
                else if (startDate2 <= startDate1 && endDate2 + *p_buffer >= startDate1)
                {
                    int r = rdistribution(generator);
                    if (r==1)
                    {
                        sol[posStay2] = -1;
                    }
                    else 
                    {
                        sol[posStay1] = -1;
                    }
                    // cout << "Conflit2 startDate1 : " << startDate1 << " et endDate1 " << endDate1 << endl;
                    // cout << "Conflit2 startDate2 : " << startDate2 << " et endDate2 " << endDate2 << "\n"<< endl;
                }
            }
        }
    }
    Solution newSolution2 = Solution(sol);
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
            poids_allocation += 5;
        }
        else
        {
            // ParkNature parkNature = vectParkings[posPark].getNature();
            // if (op.getNbTowing() == 3)
            // {
            //     switch (vectParkings[posPark].getNature())
            //     case (ParkNature::Contact):
            //         poids_nature += 0.5;
            // }
            if (op.getNbTowing() != 3)
            {
                switch (vectParkings[posPark].getNature())
                case (ParkNature::Large):
                    poids_nature += 1;
            }
        }
    }
    return poids_allocation + poids_nature;
}


Solution RecuitSimule::generateSolution(int compt)
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
    // solution.randomize(sizeParkings, vectOperations);
    // solution.mutateMinusOne(sizeParkings, vectOperations);

    // solution.NonAllocAndContact(sizeParkings,vectOperations,vectParkings);

    // const Solution* newSol;
    Solution* newSol;
    // vector<int>* test;
    if (operateurs.size() >= 2)
    {
        if (compt < 10000)
        {
            operateurs[0]->setSolution(solutionCourante);
            newSol = operateurs[0]->apply();
            // test = &(operateurs[0]->apply(T).getSolution());
        }

        // if (compt % 50 == 0)
        // {
        //     operateurs[0]->setSolution(solution);
        //     solution = operateurs[0]->apply(T);
        //     // cout << "cc0" << endl;
        // }

        // // if (compt % 100 == 0)
        // else
        // {
        //     operateurs[1]->setSolution(solution);
        //     solution = operateurs[1]->apply(T);
        //     // // cout << "cc1" << endl;
        // }
        else if (compt == 10000)
        {
            cout << "10000" << endl;
            T=0.1;
            solutionCourante = solutionGlobal;
            // solution = solutionGlobal;
            operateurs[1]->setSolution(solutionCourante);
            newSol = operateurs[1]->apply();
        }
        // if (compt % 10 == 0)
        // {
        //     operateurs[2]->setSolution(solution);
        //     solution = (operateurs[2]->apply(T));
        //     // sol = &sol2;
        //     // cout << "MMO" << endl;
        // }
        else
        {
            operateurs[1]->setSolution(solutionCourante);
            newSol = operateurs[1]->apply();
            // cout << "M" << endl;
        }
    }
    else {
        operateurs[0]->setSolution(solutionCourante);
        newSol = operateurs[0]->apply();
    }
    // cout << "generateSOlution done" << endl;

    return *newSol;
}

void RecuitSimule::heatUp(double valeurCourante, const vector<Parking> &vectParkings, const vector<Operation> &vectOperations)
{
    T = 0.5;
    int cpt = 0;
    double avg = 0;
    while (cpt <= 1000)
    {
        Solution newSolution = generateSolution(cpt);
        newSolution = correctSolution(newSolution, vectParkings, vectOperations);
        double nouvelleValeur = fonctionObjectif(newSolution, vectParkings, vectOperations);
        double differenceValeur = nouvelleValeur - valeurCourante;
        avg += differenceValeur;
        cpt += 1;
    }
    avg = avg / cpt;
    T = -avg / (log(0.8));
}


void RecuitSimule::majT(float &acc)
{
    // if (T < exp(-acc)) {
    //     T += 17/acc  ;
    //     acc += 1 ;
    // }
    // else
    // {
    //     T *= 0.97;
    // }
    T *= 0.98;

}

Solution RecuitSimule::recuitSimule(const vector<Parking> &vectParkings, const vector<Operation> &vectOperations)
{
    std::random_device rd;
    std::default_random_engine generator(rd());

    auto start = std::chrono::high_resolution_clock::now();

    solutionCourante = correctSolution(solutionCourante, vectParkings, vectOperations);
    double valeurCourante = fonctionObjectif(solutionCourante, vectParkings, vectOperations);
    // cout << "Avant heatUp T : " << T << endl;
    // heatUp(valeurCourante, vectParkings, vectOperations);
    // cout << "Apres heatUp T : " << T << endl;
    std::cout << "\nValeur Initiale: " << valeurCourante << "\n\n";
    valeurGlobale = valeurCourante;
    int compt = 0;
    float acc = 1;
    vector<double> histoT ;
    vector<tuple<double,double, double, double>> histoVal ;
    // while (T > 0.05 && compt < nbIter)
    while (compt < nbIter)
    {
        for (int i = 0; i < nbIterT; ++i)
        {

            Solution newSolution = generateSolution(compt);

            newSolution = correctSolution(newSolution, vectParkings, vectOperations);
            double nouvelleValeur = fonctionObjectif(newSolution, vectParkings, vectOperations);
            // cout << "Nouvelle Valeur : " << nouvelleValeur << endl;
            double differenceValeur = nouvelleValeur - valeurCourante;

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


            // else if (nouvelleValeur - valeurGlobale < 0)
            // {
            //     solutionCourante = newSolution;
            //     valeurCourante = nouvelleValeur;
            //     solutionGlobal = solutionCourante;
            //     valeurGlobale = nouvelleValeur;
            //     std::cout << "change valeur Globale :" << valeurGlobale << endl;
            // }

            else if (differenceValeur < 0)
            {
                solutionCourante = newSolution;
                valeurCourante = nouvelleValeur;
                if (nouvelleValeur - valeurGlobale < 0)
                {
                    solutionGlobal = newSolution;
                    valeurGlobale = nouvelleValeur;
                    std::cout << "change valeur Globale :" << valeurGlobale << endl;
                }
                // solutionGlobal = solutionCourante;
                // valeurGlobale = nouvelleValeur;
                // cout << "change valeur Globale :" << valeurGlobale << endl;
            }
            else
            {
                std::uniform_real_distribution<float> distribution(0.0,1.0);

                // cout << "difV : " << differenceValeur << endl;
                // cout << "rand : " << rand() / static_cast<double>(RAND_MAX) << " | exp : " << exp(-differenceValeur / T) << endl;
                // if (rand() / static_cast<double>(RAND_MAX) < exp(-differenceValeur / T))
                if (distribution(generator) < exp(-differenceValeur / T))
                {
                    // cout << "passe" << endl;
                    solutionCourante = newSolution;
                    valeurCourante = nouvelleValeur;
                }
            }
            compt += 1;
            histoVal.push_back({valeurCourante, valeurGlobale, nouvelleValeur, T});
        }
        // histoT.push_back(T);
        majT(acc);
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

    TXTWrite writer;
    // writer.write(histoT);


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
    if (operateurs.size() == 1) {
        writer.setFilename(operateurs[0]->getName() + ".txt");
        writer.write(histoVal, operateurs[0]->getName());
    }
    else {
        writer.setFilename(operateurs[0]->getName() + "AND" + operateurs[1]->getName() + ".txt");
        // writer.setFilename("solution.txt");
        writer.write(histoVal, operateurs[0]->getName() + "AND" + operateurs[1]->getName());
    }

    return solutionGlobal;
}