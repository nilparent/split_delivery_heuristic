#include "heuristique.h"

bool cout_swap_two_clients_from_one_truck(Truck& truck,int i, int j,double *& distance,Client depot){
    double initial_cost = 0;
    double final_cost= 0;

    double id_client_swap_1= truck.path[i];
    double id_client_swap_2= truck.path[j];
    //problem with i=0 and j=client_serve

    double id_swap_before_1;
    double id_swap_before_2;
    double id_swap_after_1;
    double id_swap_after_2;




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
