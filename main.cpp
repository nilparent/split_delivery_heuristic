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
    for (int i=0;i<3;i++){
        cost[i]=i;}

    int number_of_client = 500;

    int height = 500;
    int width = 500;

    int capacity_max = 1000;
    int demand_max = 5;
    int number_of_truck_max = 50;


    Solution sol = Solution(number_of_client,height,width,demand_max,number_of_truck_max,capacity_max,cost);
    sol.displaysolution();
    double a;
    a=calcul_cout_solution(sol);
    cout<< a;





}
