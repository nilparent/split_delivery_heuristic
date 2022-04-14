#include "instance_generator.h"

double distance(Client a, Client b) {
    double xa=a.x;
    double xb=b.x;
    double ya=a.y;
    double yb=b.y;
    double dist = sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb));
    return dist;
}

Instance :: ~Instance(){
    delete [] listclient;
    delete [] distanceclient;
    delete [] client_already_served;
}
void Instance :: Modif_instance(int numberofclient, int Xmap, int Ymap, int Maxdemand){
    nbclient = numberofclient;
    maxdemand = Maxdemand;
    xmap=Xmap;
    ymap = Ymap;
    listclient = new Client[nbclient];
    srand ( (unsigned int)time(0) );
    if (maxdemand == 1)
        for(int i=0;i<nbclient;i++){
            listclient[i].demand = 1;//the demand of the client is necessatily 1
            listclient[i].x = rand()%xmap;
            listclient[i].y = rand()%ymap;
        }
    else{
        for(int i=0;i<nbclient;i++){
            listclient[i].demand = rand()%(maxdemand-1) + 1;//a client cannot have a demand null
            listclient[i].x = rand()%xmap;
            listclient[i].y = rand()%ymap;
        }
    }
    distanceclient = new double[nbclient*nbclient];
    for (int i=0;i<nbclient;i++){
        for (int j=0;j<nbclient;j++)
            distanceclient[i+j*nbclient]=distance(listclient[i],listclient[j]);
    }
    depot.x = xmap/2;
    depot.y = ymap/2;
    depot.demand = 10;
}
Instance :: Instance(int numberofclient,int Xmap,int Ymap,int Maxdemand){
    nbclient = numberofclient;
    maxdemand = Maxdemand;
    xmap=Xmap;
    ymap = Ymap;
    listclient = new Client[nbclient];
    srand ( (unsigned int)time(0) );
    if (maxdemand == 1)
        for(int i=0;i<nbclient;i++){
            listclient[i].demand = 1;//the demand of the client is necessatily 1
            listclient[i].x = rand()%xmap;
            listclient[i].y = rand()%ymap;
        }
    else{
        for(int i=0;i<nbclient;i++){
            listclient[i].demand = rand()%(maxdemand-1) + 1;//a client cannot have a demand null
            listclient[i].x = rand()%xmap;
            listclient[i].y = rand()%ymap;
        }}
    distanceclient = new double[nbclient*nbclient];
    for (int i=0;i<nbclient;i++){
        for (int j=0;j<nbclient;j++)
            distanceclient[i+j*nbclient]=distance(listclient[i],listclient[j]);
    }
    depot.x = xmap/2;
    depot.y = ymap/2;
    depot.demand = 10;
}

void displayclient(Client a ,Color col){
    fillCircle(a.x,a.y,3 * a.demand,col);
}

void Instance :: displayinstance(){
    openWindow(xmap,ymap);
    for(int i=0;i<nbclient;i++){
        displayclient(listclient[i],BLACK);
    }
    displayclient(depot,RED);
}
Instance ::Instance(){//pb d'instance...

}
void writeFile (std::string directory, std::string to_write)
{
    ofstream myfile;
    myfile.open(directory);
    myfile << to_write +"\n";

    myfile.close();
    return ;
}
