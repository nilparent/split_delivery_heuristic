#pragma once

#include "Solution.h"
Truck :: ~Truck(){
    delete [] path;
    delete [] quantity_took;
}


bool serve_client(Truck& actual_truck,int idclient,double& demand_deserve,double capacitytruck){//take the id of the client and serve him with the truck actual_truck
    //the actual_truck is use and deserve one more client idclient


    bool is_client_deserve=capacitytruck - actual_truck.sum_quantity_took >= demand_deserve;
    if (is_client_deserve){//the actual truck can completely serve the client_deserve
        actual_truck.quantity_took[actual_truck.number_of_client_deserve] = demand_deserve;
        actual_truck.sum_quantity_took += demand_deserve;
        demand_deserve = 0;
    }

    else {
        demand_deserve -= capacitytruck - actual_truck.sum_quantity_took; //need another truck to deserve this client
        actual_truck.quantity_took[actual_truck.number_of_client_deserve] = capacitytruck - actual_truck.sum_quantity_took;
        actual_truck.sum_quantity_took += capacitytruck - actual_truck.sum_quantity_took;
        cout<<"babines";
    }
    actual_truck.use= true;
    actual_truck.path[actual_truck.number_of_client_deserve] = idclient;
    actual_truck.number_of_client_deserve += 1;
    return(is_client_deserve);

};

Solution :: Solution(int numberofclient,int Xmap,int Ymap,int Maxdemand,double NBTRUCKMAX, double CAPACITYTRUCK,double COST []){
    instance.Modif_instance(numberofclient,Xmap,Ymap,Maxdemand);//on modifie l'instance du constructeur vide pour que tout aille bien...
    nbtruckmax = NBTRUCKMAX;
    capacitytruck = CAPACITYTRUCK;
    for (int i=0;i<3;i++)
        cost[i] = COST[i];
    truck_path = new Truck [nbtruckmax];

    for (int i=0;i<nbtruckmax;i++)
        truck_path[i].use = false,
                truck_path[i].path = new int [instance.nbclient],
                truck_path[i].sum_quantity_took = 0,
                truck_path[i].number_of_client_deserve = 0,
                truck_path[i].quantity_took = new double [instance.nbclient];

    //initialize the solution
    int actual_truck = 0;//the truck that we will full

    //we have to sort the listclient of the instance to have a path which minimize the travel between each client
    //for (int i =0;i< instance.nbclient;i++)
    //we copy the list
    //    ;
    for (int i =0;i<instance.nbclient;i++){
        cout<<"\n idclient i :";
        cout<<i;
        cout<<"\n position : ";
        cout<<instance.listclient[i].x;
        cout<<"   ";
        cout<<instance.listclient[i].y;
        cout<<"\n demand : ";
        cout<<instance.listclient[i].demand;
    }


    double demand_deserve [instance.nbclient];
    for (int i=0;i<instance.nbclient;i++)
        demand_deserve[i] = instance.listclient[i].demand;




    bool is_client_serve =false;
    for (int clientdeserve = 0;clientdeserve < instance.nbclient;clientdeserve++){
        while (not(is_client_serve)){
            is_client_serve = serve_client( truck_path[actual_truck],clientdeserve,demand_deserve[clientdeserve],capacitytruck);
        }
        //next client
        is_client_serve = false;
    }
}

void drawline(Client a,Client b){
    drawLine(a.x,a.y,b.x,b.y,BLACK);
}
void Solution :: displaysolution(){
    instance.displayinstance();
    for (int i=0;i<nbtruckmax;i++){
        if (truck_path[i].use){
            Client point = instance.depot;
            cout<<"numberofclient";
            cout<<truck_path[i].number_of_client_deserve;
            for (int j=0;j<truck_path[i].number_of_client_deserve;j++){
                int numclient=truck_path[i].path[j];
                drawline(point,instance.listclient[numclient]);
                point = instance.listclient[numclient];
                cout<<"\n numclient";
                cout<<numclient;
            }

            drawline(instance.depot,point);
        }
    }
    endGraphics();
}
Solution :: ~Solution(){
    for (int j=0;j<nbtruckmax;j++)
        truck_path[j].~Truck();
    delete [] truck_path;
    instance.~Instance();
}

void Solution :: displayinstance(){
    instance.displayinstance();
}
