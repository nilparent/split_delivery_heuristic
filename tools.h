#pragma once

// Initialise Tools. graphique: dessiner ou non
void init_tools(int taille_fenetre,bool graphique);
// Termine Tools
void end_tools();

// Remplit le tableau avec des valeurs croissantes de 0 a 1
void init_tableau(double T[], int taille);
// Melange un tableau
void melange_tableau(double T[], int taille,double T0[]);
void tri_selection(double T[],int taille);
void tri_bulle(double T[],int taille);
void tri_insertion(double T[],int taille);
int pivot(double T[],int taille);
// A appeler avant chaque tri
// T0: tableau melange
// T:  recopie de T0, prete a etre triee
void init_tri(double T0[], double T[], int taille);
// A appeler a la fin du tri
void fin_tri();

// Retourne T[i] (et dessine)
double valeur(double T[], int taille, int i);
// Echange T[i] et T[j] (et dessine)
void echange(double T[], int taille, int i, int j);
void quicksort(double T[],int taille,int debut, int fin);
