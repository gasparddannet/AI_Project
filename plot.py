# -*- coding: utf-8 -*-
"""
Created on Fri Nov 24 01:07:47 2023

@author: Arthur
"""

import csv
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np

FIC = 'dataSolution/parking_occ.csv'
# FIC_TEST_FILE = 'test_file.csv'
# FIC_TEST_FILE = 'Data/stays_2F_090822.csv'
FIC_TEST_FILE = 'Data/stays.csv'
# FIC_TEST_FILE = 'Data/stays_21_06_2016.csv'


N_LABEL_PARK_ON_SCREEN = 15  # Nombre de parking affiché sur chaque figure
N_NON_ALLOCATED_STAYS_ON_SCREEN = int(1.5*N_LABEL_PARK_ON_SCREEN)

FIC_NAS = 'dataSolution/nonAllocatedStays.txt'

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
    # floa = int(string_h) + int(string_min)/60
    floa = int(string_h) + int(string_min)/60
    return floa

def string_date_to_float(date) :
    string_d, _, _ = date.split('/')
    floa = int(string_d)*24
    return floa

def read_test_file():
    dictStayAircraftType = {}
    with open(FIC_TEST_FILE) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=';')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                line_count+=1
            else:
                dictStayAircraftType[row[0].strip()] = row[2].strip()
    return dictStayAircraftType
                
            
def store(data) :
    dicoDatePark = {}
    for i in range(1, len(data)):
        lignei = data[i]
        parking = lignei.pop(0)
        for j in range(0, len(lignei)-1, 5):
            date = lignei[j+1]
            if (date,parking) in dicoDatePark:
                dicoDatePark[(date,parking)].append(lignei[j:j+5])
            else :
                dicoDatePark[(date,parking)]=[lignei[j:j+5]]
            
    dicoData = {}
    for (date, parking), stays in dicoDatePark.items():
        liste_stays = []
        for l in stays :
            liste_stays.extend(l)
        liste_stays.insert(0,parking)
        if date in dicoData :
            dicoData[date].append(liste_stays)
        else :
            dicoData[date] = [liste_stays]
    return dicoData

def store_nas(data) :
    dicoDataNas = {}
    for i in range(len(data)) :
        lignei = data[i]
        date = lignei[1]+'/06/2016'
        if date in dicoDataNas :
            dicoDataNas[date].append(lignei)
        else :
            dicoDataNas[date] = [lignei]
    return dicoDataNas

# def plot(donnees,date):
def plot(donnees):
    ###PLOTING ALLOCATED STAYS###
    nplot = int(len(donnees)/N_LABEL_PARK_ON_SCREEN) + 1  # Nombre de figure
    figax = [plt.subplots() for i in range(nplot)]

    label = [[""]*N_LABEL_PARK_ON_SCREEN for i in range(nplot)] # Les labels seront les noms des parking
    y = [i+1 for i in range(N_LABEL_PARK_ON_SCREEN)]
    starts = [[] for i in range(nplot)]
    ends = [[] for i in range(nplot)]
    # couleurs = ['r', 'g', 'b', 'y', 'c', 'm', 'k', 'orange', 'purple', 'darkorange', 'lime', 'royalblue', 'orchid', 'chartreuse']
    colorsTypeAircraft = {"318" : 'tomato', "319":'green', "320":'blue', "321":'goldenrod', "223":'brown', "737" : 'orchid', "E70":'chartreuse', "E90":'royalblue', "340":'darkorange', "777":'aquamarine', "330":'crimson', "350":'sandybrown'}
    
    dictStayAircraftType = read_test_file()
    # print(dictStayAircraftType)
    # print(dictStayAircraftType["3300476"])
    
    for i in range(1,len(donnees)):
        num_fig = int((i) / N_LABEL_PARK_ON_SCREEN) # Numéro de figure sur laquelle on travaille
        k = (i) % N_LABEL_PARK_ON_SCREEN # Indice de la ligne par rapport à la figure correspondante
        lignei = donnees[i]
        label[num_fig][k] = lignei.pop(0)
        for j in range(0, len(lignei)-1, 5):
            stay = lignei[j]
            start_date = lignei[j+1]
            start_hour = lignei[j+2]
            end_date = lignei[j+3]
            end_hour = lignei[j+4]
            start = string_time_to_float(start_hour) + string_date_to_float(start_date)
            end = string_time_to_float(end_hour) + string_date_to_float(end_date)
            starts[num_fig].append(start)
            ends[num_fig].append(end)
            width = N_LABEL_PARK_ON_SCREEN/40
            # rectangle = patches.Rectangle((start, y[k]-width), end - start, 0.5, edgecolor=couleurs[int(j/5)], facecolor=couleurs[int(j/5)])
            color = colorsTypeAircraft[dictStayAircraftType[stay]]
            rectangle = patches.Rectangle((start, y[k]-0.5/2), end - start, 0.5, edgecolor=color, facecolor=color, alpha=0.75)
            fig,ax = figax[num_fig]
            ax.add_patch(rectangle)
            ax.text((start + end) / 2, y[k], stay,
                    ha='center', va='center', color='black', size=8)
    
    
    for i,(fig,ax) in enumerate(figax):
        ax.set_yticks(y)
        ax.set_yticklabels(label[i])
        ax.set_ylim(0, N_LABEL_PARK_ON_SCREEN + 1)
        xmin, xmax = min(starts[i]),max(ends[i])
        # print(xmin)
        # print(xmax)
        xmin = int(xmin)
        xmax = int(xmax)
        # print(np.arange(xmin, xmax, step = 6))
        nbJours = (xmax-xmin)//24
        # ax.set_xlim(xmin, xmax)
        ax.set_xticks(np.arange(xmin, xmax+2, step=8), labels=['{0:02}:00'.format(i%24) for i in np.arange(xmin, xmax+2, step=8)])   #str(i%24)

        for h in range (int(xmin),int(xmax)) :
            if (h%24==0) :
                ax.vlines(x=h, ymin=0,ymax=50, color='black', linestyle='--', linewidth=1, alpha=0.8)
                if nbJours > 9 :
                    ax.text(h, -1.5, f"{h//24}/06/16" , color='green', fontsize=5)
                elif nbJours < 5 :
                    ax.text(h, -2, f"{h//24}/06/16" , color='green', fontsize=12)
                else :
                    ax.text(h, -1.5, f"{h//24}/06/16" , color='green', fontsize=8)
                

        ax.set_xlabel('Heure',labelpad=12)
        ax.set_ylabel('Parking')
        # ax.set_title(date)
    # plt.show()


    ###PLOTING NON ALLOCATED STAYS###
# def plot_nas(data,date) :
def plot_nas(data) :
    if (len(data) > 0):
        starts = []
        ends = []
        
        
        nplot = int(len(data)/N_NON_ALLOCATED_STAYS_ON_SCREEN) + 1
        figax = [plt.subplots() for i in range(nplot)]
        # starts = [[] for i in range(nplot)]
        # ends = [[] for i in range(nplot)]
        
        y_bis = [i+1 for i in range(N_NON_ALLOCATED_STAYS_ON_SCREEN)]
        for i in range(len(data)) :
            num_fig = int((i-1) / N_NON_ALLOCATED_STAYS_ON_SCREEN) # Numéro de figure sur laquelle on travaille
            k = (i-1) % N_NON_ALLOCATED_STAYS_ON_SCREEN # Indice de la ligne par rapport à la figure correspondante
            lignei = data[i]
            
            id_stay = lignei[0]
            start =  int(lignei[2]) + int(lignei[3])/60 + int(lignei[1])*24
            end = int(lignei[5]) + int(lignei[6])/60 + int(lignei[4])*24
            # starts[num_fig].append(start)
            # ends[num_fig].append(end)
            
            starts.append(start)
            ends.append(end)
            
            width = N_NON_ALLOCATED_STAYS_ON_SCREEN/40
            rectangle = patches.Rectangle((start, y_bis[k]-0.5/2), end - start, 0.5, edgecolor='r', facecolor='r')
            fig,ax = figax[num_fig]
            ax.add_patch(rectangle)
            ax.text((start + end) / 2, y_bis[k], id_stay,
                    ha='center', va='center', color='black', size=7)
        for i,(fig,ax) in enumerate(figax) :
            ax.set_ylim(0, N_NON_ALLOCATED_STAYS_ON_SCREEN + 1)
            # ax.set_xlim(min(starts[i]),max(ends[i]))
            xmin, xmax = int(min(starts)), int(max(ends))
            
            
            ax.set_xticks(np.arange(xmin, xmax+2, step=8), labels=['{0:02}:00'.format(i%24) for i in np.arange(xmin, xmax+2, step=8)]) 
            
            nbJours = (xmax-xmin)//24
            ax.set_xlim(xmin,xmax)
            for h in range (int(xmin),int(xmax)) :
                if (h%24==0) :
                    ax.vlines(x=h, ymin=0,ymax=50, color='black', linestyle='--', linewidth=1, alpha=0.8)
                    if nbJours > 9 :
                        ax.text(h, -2, f"{h//24}/06/16" , color='green', fontsize=5)
                    elif nbJours < 5 :
                        ax.text(h, -2.5, f"{h//24}/06/16" , color='green', fontsize=12)
                    else :
                        ax.text(h, -2.25, f"{h//24}/06/16" , color='green', fontsize=8)
                

            ax.set_xlabel('Heure',labelpad=12)
            # ax.set_title("Non allocated stays  " + date)
            ax.set_title("Non allocated stays")

    # ax.legend()
    # plt.show()


def main():
    donnees = readcsv(FIC)
    # dicoDate = store(donnees)
    # for date, stays in dicoDate.items():
    #     plot(stays,date)
    plot(donnees)
    data = read_txt_non_allocated_stays(FIC_NAS)
    # dicoDateNas = store_nas(data)
    # for date, nas in dicoDateNas.items() :
    #     plot_nas(nas,date)
    plot_nas(data)
    plt.show()

main()