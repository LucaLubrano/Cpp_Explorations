////
////  pois_rand_v1.c
////  Poisson_Random_Number
////
////  Created by Luca Lubrano Lavadera on 15/3/2025.
////
//
//// todo: make a macro for factorial
//// todo: can make this into one function and gain efficiencies
//#include <random>
//#include <iostream>
//#include <math.h>
//
//
//// todo: make a macro for factorial
//// todo: can make this into one function and gain efficiencies
//
//float rand_pois(float lambda, float randi);
//float probability_pois(int k, float lambda);
//float quantile_pois(float p, float lambda);
//float cumulative_pois(int n, float lambda);
//
//std::uniform_real_distribution<> unif_dist(0.0,1.0);
//std::random_device rd;
//std::mt19937 prng(rd());
//
//float rand_pois(float lambda);
//float probability_pois(int k, float lambda);
//float quantile_pois(float p, float lambda);
//float cumulative_pois(int n, float lambda);
//
//float rand_pois(float lambda){
//    float randi = unif_dist(prng);
//    float randp = quantile_pois(randi, lambda);
//    return randp;
//}
//
//// todo: make this function not suck
//float quantile_pois(float p, float lambda){
//    int k = 0;
//    float p_k = 0;
//    while ( p_k < p ){
//        p_k = cumulative_pois(k, lambda);
////        cout << p_k << " | " << p << '\n';
////        if ((k == 0 ) && (p_k >= p)){
////            return k;
////        }
//        k++;
////        cout << k-1 << " | " << p_k << " | " << p << " | " <<  '\n';
//    }
//    return k-1;
//}
//
//float cumulative_pois(int n, float lambda){
//    float cdf_n = 0;
//    for (int i = 0 ; i <= n ; i++){
//        cdf_n += probability_pois(i, lambda);
//    }
//    return cdf_n;
//}
//
//float probability_pois(int k, float lambda){
//    int fac_k = 1;
//    float p;
//    for (int i = 1 ; i <= k ; i++){
//        fac_k *= i;
//    }
//    p = ( ( pow(lambda,k) * exp(-lambda) ) / fac_k);
////    cout << p << " | " << lambda  << " | " << k << " | " << fac_k << " | " <<'\n';
//    return p;
//}
