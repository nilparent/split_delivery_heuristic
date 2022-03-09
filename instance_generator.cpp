#pragma once
#include <iostream>
#include "instance_generator.h"
#include <cmath>
#include <cstdlib>
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
    srand ( (unsigned int)time(0) );

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

double distance(Client a, Client b) {
    double xa=a.x;
    double xb=b.x;
    double ya=a.y;
    double yb=b.y;
    double dist = sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb));
    return dist;
}

void writeFile (std::string directory, std::string to_write)
{
  ofstream myfile;
  myfile.open(directory);
  myfile << to_write +"\n";

  myfile.close();
  return ;
}
