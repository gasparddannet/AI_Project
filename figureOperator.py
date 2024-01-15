# -*- coding: utf-8 -*-
"""
Created on Fri Jan 12 10:36:58 2024

@author: Arthur
"""

import matplotlib.pyplot as plt


FIC_NAAC = 'dataSolution/NonAllocAndContact.txt'
FIC_R = 'dataSolution/Randomize.txt'
FIC_MMO = 'dataSolution/MutateMinusOne.txt'
FIC_RS = 'dataSolution/RandomizeSubset.txt'
FIC_SMS = 'dataSolution/SelectiveMutationSubset.txt'
FIC = 'dataSolution/NonAllocAndContactANDRandomizeSubset.txt'


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
    abscisses = []
    operateur = f[0][0]
    for i in range(1,n) :
        yValCourante.append(int(f[i][0]))
        yValGlobale.append(int(f[i][1]))
        abscisses.append(i)
    plt.plot(abscisses, yValCourante, label = "Valeur Courante")
    plt.plot(abscisses, yValGlobale, label = "Valeur Globale")
    plt.xlabel('Itération')
    plt.ylabel('Finesse')
    plt.title(operateur)
    plt.legend()
    # plt.show()
    return abscisses, yValGlobale

def main() :
    # a, y_NAAC = plotOperator(FIC_NAAC)
    # a, y_R = plotOperator(FIC_R)
    # a, y_MMO = plotOperator(FIC_MMO)
    # a, y_RS = plotOperator(FIC_RS)
    # a, y_SMS = plotOperator(FIC_SMS)
    # a, y_SMS = plotOperator(FIC_SMS)
    a, y = plotOperator(FIC)
    
    # plt.plot(a, y_NAAC, label = "NonAllocatedAndContact")
    # plt.plot(a, y_MMO, label = "MinuteMinusOne")
    # plt.plot(a, y_R, label = "Randomize")
    # plt.plot(a, y_RS, label = "RandomizeSubset")
    # plt.plot(a, y_SMS, label = "SelectiveMutationSubset")
    # plt.plot(a, y)
    # plt.xlabel('Itération')
    # plt.ylabel('Finesse')
    # plt.legend()
    plt.show()
    
main()