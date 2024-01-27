# -*- coding: utf-8 -*-
"""
Created on Fri Jan 12 10:36:58 2024

@author: Arthur
"""

import matplotlib.pyplot as plt

FIC_M = 'dataSolution/Mutate.txt'
FIC_NAAC = 'dataSolution/NonAllocAndContact.txt'
FIC_R = 'dataSolution/Randomize.txt'
FIC_MMO = 'dataSolution/MutateMinusOne.txt'
FIC_RS = 'dataSolution/RandomizeSubset.txt'
FIC_SMS = 'dataSolution/SelectiveMutationSubset.txt'
FIC_NAAC_RS = 'dataSolution/NonAllocAndContactANDRandomizeSubset.txt'
FIC_NAAC_M = 'dataSolution/NonAllocAndContactANDMutate.txt'
FIC_NAAC_MMO = 'dataSolution/NonAllocAndContactANDMutateMinusOne.txt'
FIC_NAAC_S = 'dataSolution/NonAllocAndContactANDSwap.txt'
FIC_M_MMO = 'dataSolution/MutateANDMutateMinusOne.txt'
FIC_S = 'dataSolution/Swap.txt'
FIC = 'dataSolution/solution.txt'
FIC_S_M = 'dataSolution/SwapANDMutate.txt'
FIC_S_RS = 'dataSolution/SwapANDRandomizeSubset.txt'
FIC_S_MMO = 'dataSolution/SwapANDMutateMinusOne.txt'


def read_txt(fic) :
    with open(fic, "r") as file:
        data = []
        for line in file:
            ligne = line.strip().split()
            data.append(ligne)
    return data



def plotOperator(fic) :
    f = read_txt(fic)
    n = len(f)
    yValCourante = []
    yValGlobale = []
    yNewVal = []
    yValT = []
    abscisses = []
    operateur = f[0][0]
    for i in range(1,n) :
        yValCourante.append(float(f[i][0]))
        yValGlobale.append(float(f[i][1]))
        yNewVal.append(float(f[i][2]))
        yValT.append(float(f[i][3]))
        abscisses.append(i)
    plt.figure()
    plt.plot(abscisses, yValGlobale, label = "Valeur Globale", color="red")
    plt.plot(abscisses, yNewVal, label = "New Val", color="blueviolet", alpha=0.5)
    plt.plot(abscisses, yValCourante, label = "Valeur Courante", color="blue")
    
    
    # plt.plot(abscisses, yValT, label = "T")
    plt.xlabel('Itération')
    plt.ylabel('Finesse')
    # plt.title(operateur)
    plt.legend()
    #plt.show()
    
    plt.figure()
    plt.plot(abscisses, yValT)
    plt.xlabel("Iteration")
    plt.ylabel("T")
    return abscisses, yValGlobale

def main() :
    # Operateur simple
    a, y_NAAC = plotOperator(FIC_NAAC)
    a, y_MMO = plotOperator(FIC_MMO)
    a_RS, y_RS = plotOperator(FIC_RS)
    a, y_S = plotOperator(FIC_S)
    a, y_M = plotOperator(FIC_M)
       
    # Double opérateur
    # NAAC 
    a, y_NAAC_M = plotOperator(FIC_NAAC_M)
    a, y_NAAC_RS = plotOperator(FIC_NAAC_RS)
    a, y_NAAC_MMO = plotOperator(FIC_NAAC_MMO)
    a, y_NAAC_S = plotOperator(FIC_NAAC_S)
    
    #Swap
    a, y_S_M = plotOperator(FIC_S_M)
    a_S_RS,y_S_RS = plotOperator(FIC_S_RS)
    a,y_S_MMO = plotOperator(FIC_S_MMO)
    
    plt.figure()
    plt.plot(a, y_NAAC, label = "NonAllocatedAndContact")
    plt.plot(a, y_MMO, label = "MutateMinusOne")
    plt.plot(a, y_M, label = "Mutate")

    # plt.plot(a, y_RS, label = "RandomizeSubset")
    plt.plot(a, y_S, label="Swap")
    plt.plot(a, y_NAAC_M, label = "NAACandM")
    plt.plot(a, y_NAAC_MMO, label = "NAACandMMO")
    plt.plot(a, y_NAAC_RS, label = "NAACandRS")
    plt.plot(a, y_NAAC_S, label = "NAACandS")
    plt.plot(a, y_S_M, label = "SandM")
    plt.plot(a_S_RS, y_S_RS, label = "SandRS")
    plt.plot(a, y_S_MMO, label = "SandMMO")

    plt.xlabel('Itération')
    plt.ylabel('Finesse')
    plt.legend()
    plt.show()
    
main()