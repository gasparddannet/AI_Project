# -*- coding: utf-8 -*-
"""
Created on Fri Nov 24 01:07:47 2023

@author: Arthur
"""

import csv
import matplotlib.pyplot as plt
import matplotlib.patches as patches

FIC = 'test_file_parking_occ.csv'
N_LABEL_PARK_ON_SCREEN = 7  # Nombre de parking affiché sur chaque figure


def readcsv(fic):
    donnees = []
    with open(fic, 'r') as f_csv:
        lecteur_csv = csv.reader(f_csv)

        for ligne in lecteur_csv:
            liste = ligne[0].split(';')
            donnees.append(liste)
    return donnees


def main():
    donnees = readcsv(FIC)
    nplot = int(len(donnees)/N_LABEL_PARK_ON_SCREEN) + 1  # Nombre de figure
    figax = [plt.subplots() for i in range(nplot)]

    label = [[""]*N_LABEL_PARK_ON_SCREEN for i in range(nplot)] # Les labels seront les noms des parking
    y = [i+1 for i in range(N_LABEL_PARK_ON_SCREEN)]
    starts = [[] for i in range(nplot)]
    ends = [[] for i in range(nplot)]
    couleurs = ['r', 'g', 'b', 'y', 'c', 'm', 'k', 'w', 'orange', 'purple']

    for i in range(1, len(donnees)):
        num_fig = int((i-1) / N_LABEL_PARK_ON_SCREEN) # Numéro de figure sur laquelle on travaille
        k = (i-1) % N_LABEL_PARK_ON_SCREEN # Indice de la ligne par rapport à la figure correspondante
        lignei = donnees[i]
        label[num_fig][k] = lignei.pop(0)
        for j in range(0, len(lignei)-1, 5):
            stay = lignei[j]
            start_date = lignei[j+1]
            start_hour = lignei[j+2]
            end_date = lignei[j+3]
            end_hour = lignei[j+4]
            start_string_h, start_string_min = start_hour.split(':')
            end_string_h, end_string_min = end_hour.split(':')
            start = int(start_string_h) + int(start_string_min)/60
            end = int(end_string_h) + int(end_string_min)/60
            starts[num_fig].append(start)
            ends[num_fig].append(end)
            rectangle = patches.Rectangle(
                (start, y[k]-0.25), end - start, 0.5, edgecolor=couleurs[int(j/5)], facecolor=couleurs[int(j/5)])
            fig,ax = figax[num_fig]
            ax.add_patch(rectangle)
            ax.text((start + end) / 2, y[k] + 0.4, stay,
                    ha='center', va='center', color='black', size=8)
    
    for i,(fig,ax) in enumerate(figax) :
        ax.set_yticks(y)
        ax.set_yticklabels(label[i])
        ax.set_ylim(0, N_LABEL_PARK_ON_SCREEN + 1)
        ax.set_xlim(min(starts[i]),max(ends[i]))

    plt.show()

main()
