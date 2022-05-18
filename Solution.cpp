#pragma once
#include "tools.h"
#include "Solution.h"

void Truck :: print(){

    cout<<"number_of_client_deserve : ";
    cout<<number_of_client_deserve;
    cout<< "\n";

    cout<< "path : ";
    for (int i =0;i<number_of_client_deserve;i++){
        cout<< path[i];
        cout<< "; ";}
    cout<< "\n";

    cout<< "quantity_took : ";
    for (int j=0;j<number_of_client_deserve;j++){
        cout<< quantity_took[j];
        cout<< "; ";}
    cout<< "\n";

    cout<<"sum_quantity_took : ";
    cout<<sum_quantity_took;
    cout<< '\n';
    cout<< '\n';
}

int Truck :: cost(Instance instance, double cout[]){
    int cost = 0;
    int usecost = use * cout[0];
    int routingcost = 0;
    routingcost += distance(instance.depot,instance.listclient[path[0]]);
    routingcost += distance(instance.depot,instance.listclient[path[number_of_client_deserve-1]]);

    for (int i=1;i<number_of_client_deserve - 1;i++){
        routingcost += distance(instance.listclient[path[i-1]],instance.listclient[path[i]]);
    }

    routingcost *= cout[1];
    int stop_cost = cout[2] * number_of_client_deserve;
    cost = stop_cost+ routingcost + usecost;
    personnal_cost = cost;
    return cost;
}

bool is_in(int T [],int len_T,int argument){
    for (int i=0;i<len_T;i++)
        if (T[i] == argument)
            return(true);
    return(false);
}

int find_indice(double T[],int len_T,double argument){//renvoie l'indice de la première occurence de argument
    for (int i=0;i<len_T;i++)
        if (T[i] == argument)
            return(i);
}
void sort_list(int number_client,int list_sorted[],double* distance ){
    for (int i=0;i<number_client;i++)
        list_sorted[i] = 0;  //initialisation avec le client 0
    for (int count=0;count<number_client-1;count++){
        double* distance_sorted ;
        double* distance_non_sorted;
        distance_sorted = new double [number_client];
        distance_non_sorted = new double [number_client];
        for (int j=0;j<number_client;j++){
            distance_sorted[j] = distance [list_sorted[count]*number_client+j];
            distance_non_sorted[j] = distance [list_sorted[count]*number_client+j];
        }
        tri_selection(distance_sorted,number_client);
        bool next=false;
        int compteur=0;
        while (not(next)){
            compteur+=1;
            int new_client = find_indice(distance_non_sorted,number_client,distance_sorted[compteur]);
            if (not(is_in(list_sorted,number_client,new_client)))
                list_sorted[count+1] = new_client,
                        next = true;
        }


        delete [] distance_non_sorted;
        delete  [] distance_sorted;
    }
}



bool serve_client(Truck& actual_truck,int idclient,double& demand_deserve,double capacitytruck){//take the id of the client and serve him with the truck actual_truck
    //the actual_truck is use and deserve one more client idclient

    bool is_client_deserve=capacitytruck - actual_truck.sum_quantity_took >= demand_deserve;
    //the truck is full
    if (capacitytruck - actual_truck.sum_quantity_took == 0)
        return(false);

    if (is_client_deserve){//the actual truck can completely serve the client_deserve
        actual_truck.quantity_took[actual_truck.number_of_client_deserve] = demand_deserve;
        actual_truck.sum_quantity_took += demand_deserve;
        demand_deserve = 0;
    }

    else {

        double quantity_took = capacitytruck - actual_truck.sum_quantity_took;

        demand_deserve -= quantity_took; //need another truck to deserve this client
        actual_truck.quantity_took[actual_truck.number_of_client_deserve] = quantity_took;
        actual_truck.sum_quantity_took += quantity_took;
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

//    if (not(truck_path == NULL))
//        delete truck_path;

//    truck_path = new Truck [nbtruckmax];

    for (int i=0;i<nbtruckmax;i++)
        truck_path[i].use = false,
                truck_path[i].sum_quantity_took = 0,
                truck_path[i].number_of_client_deserve = 0;
    //initialize the solution
    int actual_truck = 0; //the truck that we will full

    double demand_deserve [instance.nbclient];
    for (int i=0;i<instance.nbclient;i++)
        demand_deserve[i] = instance.listclient[i].demand;


    int list_sorted [instance.nbclient];
    sort_list(numberofclient,list_sorted,instance.distanceclient);
    bool is_client_serve =false;
    for (int clientdeserve = 0;clientdeserve < instance.nbclient;clientdeserve++){
        while (not(is_client_serve)){
            is_client_serve = serve_client( truck_path[actual_truck],list_sorted[clientdeserve],demand_deserve[list_sorted[clientdeserve]],capacitytruck);
            if (not(is_client_serve))
                actual_truck+=1;
        }
        //next client
        is_client_serve = false;
    }
}

void drawline(Client a,Client b){
    drawLine(a.x,a.y,b.x,b.y,BLACK);
}

double Solution :: calcul_cout_solution(){
    double cost1 = 0;
    for (int i=0;i<nbtruckmax;i++){
        if (truck_path[i].use)
            cost1+=truck_path[i].cost(instance, cost);
    }
    return cost1;
}

void Solution :: displaysolution(){
    instance.displayinstance();
    for (int i=0;i<nbtruckmax;i++){
        if (truck_path[i].use){
            Client point = instance.depot;
            for (int j=0;j<truck_path[i].number_of_client_deserve;j++){
                int numclient=truck_path[i].path[j];
                drawline(point,instance.listclient[numclient]);
                point = instance.listclient[numclient];
            }
            drawline(instance.depot,point);
        }
    }
}
bool check_solution(Solution sol){

    int client_serve[sol.instance.nbclient];
    Truck truck;
    for (int i=0;i<sol.instance.nbclient;i++){
        client_serve[i]=0;
    }

    for (int j=0;j<sol.nbtruckmax;j++){
        truck=sol.truck_path[j];
        if (truck.use){
            for (int h=0;h<truck.number_of_client_deserve;h++){
            client_serve[truck.path[h]]+=truck.quantity_took[h];
            }
        }
    }
    for (int i=0;i<sol.instance.nbclient;i++){
        if(client_serve[i]!=sol.instance.listclient[i].demand){
                return false;}
    return true;
    }
}

bool Solution :: check_solution(){

    int client_serve[instance.nbclient];
    Truck truck;
    for (int i=0;i<instance.nbclient;i++){
        client_serve[i]=0;
    }

    for (int j=0;j<nbtruckmax;j++){
        truck=truck_path[j];
        if (truck.use){
            for (int h=0;h<truck.number_of_client_deserve;h++){
            client_serve[truck.path[h]]+=truck.quantity_took[h];
            }
        }
    }
    for (int i=0;i<instance.nbclient;i++){
        if(client_serve[i]!=instance.listclient[i].demand){
                return false;}
    return true;
    }
}
void Solution :: displayinstance(){
    instance.displayinstance();
}
