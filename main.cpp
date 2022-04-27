//lybraries
#include <cmath>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;
#include<iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

//import our files
#include "instance_generator.h"
#include "Solution.h"




int main(){
    double cost [3];
    for (int i=0;i<3;i++)
        cost[i]=i;

    int number_of_client = 100;
    int height = 800;
    int width = 800;
    int capacity_max = 5;
    int demand_max = 1;
    int number_of_truck_max = 500;


    Solution sol = Solution(number_of_client,height,width,demand_max,number_of_truck_max,capacity_max,cost);
    sol.displaysolution();
//    for (int i =0;i<number_of_truck_max;i++)
 //       if (sol.truck_path[i].use)
  //          sol.truck_path[i].print();





}
