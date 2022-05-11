#pragma once
#include "solution.h"
#include "instance_generator.h"

void swap_two_clients_from_one_truck(Truck& truck,int i, int j);// i and j are the places in the routes of the path Truck
void exchange_and_swap_two_clients_from_two_truck(Truck& truck1,int i1,Truck& truck2,int i2);//exchange the client place in i1 of the truck1 with the client place in i2 of the truck 2
bool cout_swap_two_clients_from_one_truck(Truck& truck,int i, int j,Instance depot);
