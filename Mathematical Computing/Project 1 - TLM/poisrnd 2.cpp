//
//  pois_rand_v3.cpp
//  Poisson_Random_Number
//
//  Created by Luca Lubrano Lavadera on 16/3/2025.
//

#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>


std::uniform_real_distribution<> unif_dist(0.0,1.0);
std::random_device rd;
std::mt19937 prng(rd());


float pois_rand(float lambda){
    const float p = unif_dist(prng);
    int k = 0;
    float p_k = 0;
    int fac_k = 1;
    while (p_k < p){
        if (k){
            fac_k *= k;
        } else {
            fac_k = 1;
        }
        p_k += ( ( pow(lambda,k) * exp(-lambda) ) / fac_k);
        k++;
    }
    return k-1;
}
