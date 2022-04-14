#include "heuristique.h"
void swap_two_clients_from_one_truck(Truck& truck,int i, int j){
    int buffer_id_client = truck.path[i];
    truck.path[i] = truck.path[j];
    truck.path[j] = buffer_id_client;
    int buffer_demand = truck.quantity_took[i];
    truck.quantity_took[i] = truck.quantity_took[j];
    truck.quantity_took[j] = buffer_demand;

}

void exchange_and_swap_two_clients_from_two_truck(Truck& truck1,int i1,Truck& truck2,int i2){
    int buffer_id = truck1.path[i1];
    truck1.path[i1] = truck2.path[i2];
    truck2.path[i2] = buffer_id;
}
