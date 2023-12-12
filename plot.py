# -*- coding: utf-8 -*-
"""
Created on Fri Nov 24 01:07:47 2023

@author: Arthur
"""

import csv
import matplotlib.pyplot as plt
import matplotlib.patches as patches

FIC = 'test_file_parking_occ.csv'
N_LABEL_PARK_ON_SCREEN = 20  # Nombre de parking affiché sur chaque figure
N_NON_ALLOCATED_STAYS_ON_SCREEN = int(1.5*N_LABEL_PARK_ON_SCREEN)

FIC_NAS = 'nonAllocatedStays.txt'

def readcsv(fic):
    donnees = []
    with open(fic, 'r') as f_csv:
        lecteur_csv = csv.reader(f_csv)

        for ligne in lecteur_csv:
            liste = ligne[0].split(';')
            donnees.append(liste)
    return donnees

def read_txt_non_allocated_stays(fic) :
    with open(fic, "r") as file:
        data = []
        for line in file:
            ligne = line.strip().split()
            if ligne[0] == '0' :
                break
            data.append(ligne)
    return data

def string_time_to_float(time) :
    string_h, string_min = time.split(':')
    floa = int(string_h) + int(string_min)/60
    return floa

    

def main():
    ###PLOTING ALLOCATED STAYS###
    donnees = readcsv(FIC)
    nplot = int(len(donnees)/N_LABEL_PARK_ON_SCREEN) + 1  # Nombre de figure
    figax = [plt.subplots() for i in range(nplot)]

    label = [[""]*N_LABEL_PARK_ON_SCREEN for i in range(nplot)] # Les labels seront les noms des parking
    y = [i+1 for i in range(N_LABEL_PARK_ON_SCREEN)]
    starts = [[] for i in range(nplot)]
    ends = [[] for i in range(nplot)]
    couleurs = ['r', 'g', 'b', 'y', 'c', 'm', 'k', 'orange', 'purple']

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
            start = string_time_to_float(start_hour)
            end = string_time_to_float(end_hour)
            starts[num_fig].append(start)
            ends[num_fig].append(end)
            width = N_LABEL_PARK_ON_SCREEN/40
            rectangle = patches.Rectangle((start, y[k]-0.25), end - start, width, edgecolor=couleurs[int(j/5)], facecolor=couleurs[int(j/5)])
            fig,ax = figax[num_fig]
            ax.add_patch(rectangle)
            ax.text((start + end) / 2, y[k] + 0.4, stay,
                    ha='center', va='center', color='black', size=8)
    
    for i,(fig,ax) in enumerate(figax) :
        ax.set_yticks(y)
        ax.set_yticklabels(label[i])
        ax.set_ylim(0, N_LABEL_PARK_ON_SCREEN + 1)
        ax.set_xlim(min(starts[i]),max(ends[i]))
        ax.set_xlabel('Heure')
        ax.set_ylabel('Parking')



    ###PLOTING NON ALLOCATED STAYS###
    data = read_txt_non_allocated_stays(FIC_NAS)
    nplot = int(len(data)/N_NON_ALLOCATED_STAYS_ON_SCREEN) + 1
    figax = [plt.subplots() for i in range(nplot)]
    # starts = [[] for i in range(nplot)]
    # ends = [[] for i in range(nplot)]
    
    starts = []
    ends = []
    
    y_bis = [i+1 for i in range(N_NON_ALLOCATED_STAYS_ON_SCREEN)]
    for i  in range(len(data)) :
        num_fig = int((i-1) / N_NON_ALLOCATED_STAYS_ON_SCREEN) # Numéro de figure sur laquelle on travaille
        k = (i-1) % N_NON_ALLOCATED_STAYS_ON_SCREEN # Indice de la ligne par rapport à la figure correspondante
        lignei = data[i]
        for j in range(0, len(lignei)-1, 5):
            id_stay = lignei[j]
            start = int(lignei[j+1])+int(lignei[j+2])/60
            end = int(lignei[j+3])+int(lignei[j+4])/60
            # starts[num_fig].append(start)
            # ends[num_fig].append(end)
            
            starts.append(start)
            ends.append(end)
            
            width = N_NON_ALLOCATED_STAYS_ON_SCREEN/40
            rectangle = patches.Rectangle((start, y_bis[k]-0.25), end - start, width, edgecolor='r', facecolor='r')
            fig,ax = figax[num_fig]
            ax.add_patch(rectangle)
            ax.text((start + end) / 2, y_bis[k]-0.1, id_stay,
                    ha='center', va='center', color='black', size=7)
    for i,(fig,ax) in enumerate(figax) :
        ax.set_ylim(0, N_NON_ALLOCATED_STAYS_ON_SCREEN + 1)
        # ax.set_xlim(min(starts[i]),max(ends[i]))
        
        ax.set_xlim(min(starts),max(ends))
        
        ax.set_xlabel('Heure')
        ax.set_title("Non allocated stays")

    
    plt.show()


main()

#vector<vector<int>>#14-15 mardi 19