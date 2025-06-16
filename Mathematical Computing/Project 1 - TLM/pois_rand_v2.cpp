//
//  pois_rand_v2.cpp
//  Poisson_Random_Number
//
//  Created by Luca Lubrano Lavadera on 15/3/2025.
//
//
//#include <iomanip>
//#include <iostream>
//#include <map>
//#include <random>
//#include <string>
//
//std::uniform_real_distribution<> unif_dist(0.0,1.0);
//std::random_device rd;
//std::mt19937 prng(rd());
//
//float pois_rand_v2(float lambda){
//    const float p = unif_dist(prng);
//    int k = 0;
//    float p_k = 0;
//    float cdf_n = 0;
//    int fac_k = 1;
//    
//    while (p_k < p){
//        cdf_n = 0;
//        for (int i = 0 ; i <= k ; i++){
//            fac_k = 1;
//            for (int j = 1 ; j <= i ; j++){
//                fac_k *= j;
//            }
//            float prob = ( ( pow(lambda,i) * exp(-lambda) ) / fac_k);
//            cdf_n += prob;
//        }
//        p_k = cdf_n;
//        k++;
//    }
//    return k-1;
//}
