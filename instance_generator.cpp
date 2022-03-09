#pragma once
#include <iostream>
#include "instance_generator.h"
#include <cmath>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;

Instance :: ~Instance(){
    delete [] listclient;
}
Instance :: Instance(int numberofclient,int Xmap,int Ymap,int Maxdemand){
    nbclient = numberofclient;
    maxdemand = Maxdemand;
    xmap=Xmap;
    ymap = Ymap;
    listclient = new Client[nbclient];
    for(int i=0;i<nbclient;i++){
        listclient[i].demand = rand()%(maxdemand-1) + 1;//a client cannot have a demand null
        listclient[i].x = rand()%xmap;
        listclient[i].y = rand()%ymap;
    }
}
void Instance :: displayinstance(){
    openWindow(xmap,ymap);
    for(int i=0;i<nbclient;i++){
        fillCircle(listclient[i].x,listclient[i].y,5*listclient[i].demand,BLACK);
    }
    endGraphics();
}
