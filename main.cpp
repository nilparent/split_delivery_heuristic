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
    Solution sol = Solution(5,500,500,1,500,3,cost);

    sol.displaysolution();

}
