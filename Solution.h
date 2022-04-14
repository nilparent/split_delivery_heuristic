#pragma once
#include "instance_generator.h"

struct Truck{
   bool use;//true if the truck is use false if it isn't
   int * path; // contains the id of the client deserve in the correct order
   double * quantity_took;// quantity took at the stop
   double sum_quantity_took;
   int number_of_client_deserve;
   int cost(Instance instance, int cout[]);//calculate the cost of the truck and save it in personnal_cost
   int personnal_cost;
   void print();
   ~Truck();
};

struct Solution{
    Instance instance;
    int nbtruckmax;
    double capacitytruck;
    double solution_cost;
    double cost [3];//parameters cost cost[0] : building cost  // cost[1] : routing_cost // cost[2] : stop_cost
    Truck * truck_path;
    void displaysolution();
    void first_optimization();
    void calcul_solution_cost();//actualize the solution_cost (good for the beginning)
    Solution(int numberofclient,int Xmap,int Ymap,int Maxdemand,double NBTRUCKMAX, double CAPACITYTRUCK,double Cost []);
    ~Solution();
    void displayinstance();
};
void displayclient(Client a);
