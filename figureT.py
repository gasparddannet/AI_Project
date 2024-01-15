# -*- coding: utf-8 -*-
"""
Created on Wed Dec 20 20:32:02 2023

@author: Arthur
"""
import matplotlib.pyplot as plt


FIC = 'dataSolution/histoT.txt'

def read_txt(fic) :
    with open(fic, "r") as file:
        data = []
        for line in file:
            ligne = line.strip().split()
            data.append(float(ligne[0]))
    return data



def main() :
    f_T = read_txt(FIC)
    abscisses = list(range(len(f_T)))
    plt.plot(abscisses, f_T)
    plt.xlabel('Itération')
    plt.ylabel('T')
    plt.show()

main()
    