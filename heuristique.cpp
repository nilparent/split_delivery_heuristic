#include "heuristique.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void assignation_client_depot(int i,int& id_swap_before, int& id_swap_after,int id_depot,Truck truck){
    //give the id of the client before and after the ieme client deserved by the truck

    if (i==0){
        id_swap_before = id_depot;
    }
    else {
        id_swap_before = truck.path[i-1];
    }
    if(i == truck.number_of_client_deserve-1)
        id_swap_after = id_depot;

    else{
        id_swap_after = truck.path[i+1];
    }
}


double calc_distance(const Instance & instance,int id1,int id2,int depot_client){
   if (id1 == depot_client)
       return(distance(instance.listclient[id2],instance.depot));

   if (id2 == depot_client)
       return(distance(instance.listclient[id1],instance.depot));

   return distance(instance.listclient[id1],instance.listclient[id2]);
}

bool cout_swap_two_clients_from_one_truck(Truck& truck,int i, int j,Instance & instance){
    double initial_cost = 0;
    double final_cost= 0;

    int id_client_swap_1= truck.path[i];
    int id_client_swap_2= truck.path[j];

    int id_depot=instance.nbclient;

    int id_swap_before_1;
    int id_swap_after_1;

    int id_swap_before_2;
    int id_swap_after_2;

    assignation_client_depot(i,id_swap_before_1,id_swap_after_1,id_depot,truck);
    assignation_client_depot(j,id_swap_before_2,id_swap_after_2,id_depot,truck);


//calcul des coûts

    initial_cost += calc_distance(instance,id_swap_before_1,id_client_swap_1,id_depot);
    initial_cost += calc_distance(instance,id_swap_after_1,id_client_swap_1,id_depot);
    initial_cost += calc_distance(instance,id_swap_before_2,id_client_swap_2,id_depot);
    initial_cost += calc_distance(instance,id_swap_after_2,id_client_swap_2,id_depot);

    final_cost += calc_distance(instance,id_swap_before_1,id_client_swap_2,id_depot);
    final_cost += calc_distance(instance,id_swap_after_1,id_client_swap_2,id_depot);
    final_cost += calc_distance(instance,id_swap_before_2,id_client_swap_1,id_depot);
    final_cost += calc_distance(instance,id_swap_after_2,id_client_swap_1,id_depot);

    return initial_cost>final_cost;
}


void swap_two_clients_from_one_truck(Truck& truck,int i, int j){
    
    int buffer_id_client = truck.path[i];
    truck.path[i] = truck.path[j];
    truck.path[j] = buffer_id_client;
    
    int buffer_demand = truck.quantity_took[i];
    truck.quantity_took[i] = truck.quantity_took[j];
    truck.quantity_took[j] = buffer_demand;
    
}

bool cout_D_up_star(Truck& truck,int i, int j,const Instance & instance){
    int id_client_swap_1= truck.path[i];
    int id_client_swap_2= truck.path[j];

    int id_depot=instance.nbclient;

    int id_swap_before_1;
    int id_swap_after_1;//no need

    int id_swap_before_2;//no need
    int id_swap_after_2;
    assignation_client_depot(i,id_swap_before_1,id_swap_after_1,id_depot,truck);
    assignation_client_depot(j,id_swap_before_2,id_swap_after_2,id_depot,truck);

    //Calcul des coûts
    double initial_cost = 0;
    double final_cost= 0;
    initial_cost += calc_distance(instance,id_swap_before_1,id_client_swap_1,id_depot);
    initial_cost += calc_distance(instance,id_swap_after_2,id_client_swap_2,id_depot);
    final_cost += calc_distance(instance,id_swap_before_2,id_client_swap_1,id_depot);
    final_cost += calc_distance(instance,id_swap_after_2,id_client_swap_1,id_depot);

    return initial_cost>final_cost;
}
void D_up_star(Truck& truck,int i,int j){
    //reverse the client between i and j
    int * client_change;
    client_change= new int [j-i+1];
    double * quantity_took_change;
    quantity_took_change = new double [j-i];
    
    
    
    for (int i1=0;i1<j-i+1;i1++){
        client_change[i1] = truck.path[i1+i];
        quantity_took_change[i1] = truck.quantity_took[i1+i];
    }
    
    
    for (int i1 = 0;i1<j-i+1; i1 ++){
        truck.path[j-i1] = client_change[i1];
        truck.quantity_took[j-i1] = quantity_took_change[i1];
    }
    
    delete[] client_change;
    delete[] quantity_took_change;
}


bool exchange_and_swap_two_clients_from_two_truck(Truck& truck1,int i1,Truck& truck2,int i2,double capacity_truck){
    
    //can we do the swap
    bool swap;
    int quantity_took_update_1 = truck1.sum_quantity_took - truck1.quantity_took[i1]+truck2.quantity_took[i2];
    int quantity_took_update_2 = truck2.sum_quantity_took - truck2.quantity_took[i2]+truck2.quantity_took[i1];
    swap = not(quantity_took_update_1 > capacity_truck or quantity_took_update_2 > capacity_truck);
    
    if (swap){
        int buffer_id = truck1.path[i1];
        truck1.path[i1] = truck2.path[i2];
        truck2.path[i2] = buffer_id;
        
        int buffer_demand = truck1.quantity_took[i1];
        truck1.quantity_took[i1] = truck2.quantity_took[i2];
        truck2.quantity_took[i2] = buffer_demand;
        
        truck1.sum_quantity_took = quantity_took_update_1;
        truck2.sum_quantity_took = quantity_took_update_2;
    }
    return swap;
}


void first_heuristic(Solution& Sol, int nb_max_iter){
    srand (time(NULL));

    //let's find the first empty truck

    int nb_truck=0;
    while (Sol.truck_path[nb_truck].use){
        nb_truck+=1;
    }
    for (int iter=0;iter<nb_max_iter;iter++){
        int nclient1_1;
        int nclient1_2;
        int nclient2_1;
        int nclient2_2;

        int truck1;
        int truck2;

        truck1 = rand() % nb_truck;
        truck2 = rand() % nb_truck;

        nclient1_1 = rand() % Sol.truck_path[truck1].number_of_client_deserve;
        nclient1_2 = rand() % Sol.truck_path[truck1].number_of_client_deserve;
        nclient2_1 = rand() % Sol.truck_path[truck1].number_of_client_deserve;
        nclient2_2 = rand() % Sol.truck_path[truck1].number_of_client_deserve;

        int method ;
        method = 0;//rand()%3;

        if (method==0){
            if (cout_swap_two_clients_from_one_truck(Sol.truck_path[truck1],nclient1_1, nclient1_2, Sol.instance)){
                swap_two_clients_from_one_truck(Sol.truck_path[truck1],nclient1_1, nclient1_2);
            }
        }










    }

}

