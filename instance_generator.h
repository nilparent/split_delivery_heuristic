#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;


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
    Client * listclient;
    double * distanceclient;
    bool * client_already_served;
    Instance();
    Instance(int numberofclient,int Xmap,int Ymap,int Maxdemand);
    void Modif_instance(int numberofclient,int Xmap,int Ymap,int Maxdemand);
    ~Instance();
    void displayinstance();
};
double distance(const Client & a, const Client & b);

