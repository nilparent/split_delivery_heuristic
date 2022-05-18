#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;

const int nb_client = 50;
struct Client{//une branche est délimité par un point plus un vecteur
    int demand;
    int x,y;
    //Client(int X,int Y,int DEMANDE);
};
struct Instance{
    int nbclient;
    int maxdemand;
    int xmap;
    int ymap;
    Client depot;
    Client listclient [nb_client];
    double distanceclient [nb_client * nb_client];
    Instance();
    Instance(int numberofclient,int Xmap,int Ymap,int Maxdemand);
    void Modif_instance(int numberofclient,int Xmap,int Ymap,int Maxdemand);
    void displayinstance();
};
double distance(const Client & a, const Client & b);

