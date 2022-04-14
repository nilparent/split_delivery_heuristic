//-------------------------------------------------------------------------
// les fonctions de tools.cpp gerent l'interface graphique pour le tri
//-------------------------------------------------------------------------

#include "tools.h"

#include <Imagine/Graphics.h>
using namespace Imagine;

#include <iostream>
#include <ctime>

using namespace std;
//-------------------------------------------------------------------------
// variables globales et fonctions internes au fichier tools.cpp
//-------------------------------------------------------------------------

// Ce n'est pas bien d'avoir des variables globabes, mais c'est parfois bien
// commode... Au moins, on les met dans un namespace, ce qui permet de savoir
// facilement ou elles sont utilisees.
namespace global {
bool graphique = false; // Dessin ou pas?
int fenetre;    // taille de la fenetre
int graph;      // taille du graphique
}

void init_random() {
    srand((unsigned int)time(0));
    rand();
}

// entier entre 0 et a-1
int random(int a) {
    return(rand()%a);
}

void affiche_barre(int taille, int i, double value, Color col=BLUE) {
    if (!global::graphique)
        return;
    int width = global::graph / taille;
    if (width==0) {
        cout << "trop d'elements pour pouvoir afficher le tableau" << endl;
        return;
    }
    fillRect(global::fenetre/10+i*width,
             global::fenetre*9/10-int(value*global::graph),
             (width>1)?width-1:width,
             int(value*global::graph), col);
}

void efface_barre(int taille, int i) {
    if (!global::graphique)
        return;
    int width = global::graph / taille;
    fillRect(global::fenetre/10+i*width, global::fenetre*9/10-global::graph,
             width, global::graph, WHITE);
}

void affiche_tableau(double T[], int taille) {
    if (!global::graphique)
        return;
    noRefreshBegin();
    for (int i=0; i<taille; i++)
        affiche_barre(taille,i,T[i]);
    noRefreshEnd();
    milliSleep(10);
}

//-------------------------------------------------------------------------
// fonction declarees dans tools.h
//-------------------------------------------------------------------------

void init_tools(int taille_fenetre,bool dessiner) {
    init_random();
    global::graphique=dessiner;
    global::fenetre = taille_fenetre;
    global::graph = int(global::fenetre*0.8);
    openWindow(global::fenetre, global::fenetre);
}

void end_tools() {
    endGraphics();
}

void melange_tableau(double T[], int taille,double T0[]){//on mélange bien comme il faut avec cette focntion
    double T1[taille];
    for (int i=0;i<taille;i++)
        T1[i]=1;

    for (int i=0;i<taille;i++){
        int compteur =0;
        int indice=0;
        int n=random(taille-i);

        while (compteur <n+1)
            compteur+=T1[indice],
                    indice +=1;
        T1[indice-1]=0;
        T0[i]=T[indice-1];
    }
    if (global::graphique)
        affiche_tableau(T0,taille);
};
void init_tableau(double T[], int taille) {
    for (int i=0; i<taille; i++) {
        T[i] = double(i+1) / taille;
    }
    if (global::graphique)
        affiche_tableau(T,taille);
}

double valeur(double T[], int taille, int i) {
    return (T[i]);
}

void echange(double T[],int taille, int i, int j) {
    double tmp = T[i];
    T[i] = T[j];
    T[j] = tmp;
}

void init_tri(double T0[], double T[], int taille) {
    for (int i=0; i<taille; i++)
        T[i] = T0[i];
    if (global::graphique)
        affiche_tableau(T,taille);
    click();
}

void fin_tri() {
    if (global::graphique) {
        click();
        clearWindow();
    }
}
void tri_selection(double T[],int taille){
    for (int i=0;i<taille;i++){
        int k=0;
        for (int j=0;j<(taille-i);j++){
            if (valeur(T,taille,j)>valeur(T,taille,k))
                k=j;

        }
        echange(T,taille,k,taille-i-1);
    }
};
void tri_bulle(double T[],int taille){
    for (int i=0;i<taille;i++)
        for (int j=0;j<taille-1-i;j++)
            if (valeur(T,taille,j)>valeur(T,taille,j+1))
                echange(T,taille,j,j+1);
};
void tri_insertion(double T[],int taille){
    for (int i=0;i<taille;i++){
        int k=i;
        for (int j=0;j<i;j++)
            if (valeur(T,taille,i)<valeur(T,taille,j))
                echange(T,taille,i,j);

    }
};
int pivot(double T[],int taille,int debut ,int fin1){
    int pivot=debut;//place du pivot
    int fin=fin1;
    for (int i=0;i<fin1-debut;i++)
        if (valeur(T,taille,pivot+1)<valeur(T,taille,pivot))
            echange(T,taille,pivot,pivot+1),
                    pivot+=1;
        else
            echange(T,taille,fin,pivot+1),
                    fin -=1;
    return(pivot);
};
void quicksort(double T[],int taille,int debut, int fin){
    if (debut-fin ==0)
        return;
    int p=pivot(T,taille,debut,fin);
    if (p!=fin)
        quicksort(T,taille,p+1,fin);

    if (p!=debut)
        quicksort(T,taille,debut,p);
};
