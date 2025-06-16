//
//  main.cpp
//  Tau_Leap_Method
//
//  Created by Luca Lubrano Lavadera on 11/3/2025.
//

#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <time.h>
#include "tau_leap.h"

using namespace std;

int main()
{
    int tau = 1;
    int T = 100;
    int t0 = 0;
    float k[3] = {1, 0.1, 0.05};
    int x0[2] = {100, 0};
    int nu[3][2] = {{1, 0},{-1, 1},{0, -1}};
    
    double time1, timedif;
    time1 = (double) clock();            /* get initial time */
    time1 = time1 / CLOCKS_PER_SEC;      /*    in seconds    */
    
    
    
//    for (int i = 0 ; i < 10000 ; i++){
        tau_leap_v3(x0, k, nu, tau, t0, T);
//    }
    
    timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
    
    cout << "| elapsed time : " << timedif << " seconds | \n";
    
    return 0;
}

