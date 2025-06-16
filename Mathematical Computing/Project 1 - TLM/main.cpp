//
//  main.cpp
//  Poisson_Random_Number
//
//  Created by Luca Lubrano Lavadera on 14/3/2025.
//

// poisson random number generator v2
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>


std::uniform_real_distribution<> unif_dist(0.0,1.0);
std::random_device rd;
std::mt19937 prng(rd());


float pois_rand_v2(float lambda){
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

int main()
{
//    double time1, timedif;
//    time1 = (double) clock();            /* get initial time */
//    time1 = time1 / CLOCKS_PER_SEC;      /*    in seconds    */
//    
//    for (int i = 0 ; i < 10000 ; i++){
//        pois_rand_v2(4.0);
//    }
//    timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
//    std::cout << "| elapsed time : " << timedif << " seconds | \n";
//    time1 = (double) clock();            /* get initial time */
//    time1 = time1 / CLOCKS_PER_SEC;      /*    in seconds    */
//    
//    for (int i = 0 ; i < 10000 ; i++){
//        std::poisson_distribution<int> distribution(4.0);
//        distribution(prng);
//    }
//    timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
//    std::cout << "| elapsed time : " << timedif << " seconds | \n";
//    for (int i = 0 ; i < 10 ; i++){
//        std::cout << pois_rand_v2(4) << '\n';
//    }
    std::map<int, int> hist;
    for (int n = 0; n != 10000; ++n)
        ++hist[pois_rand_v2(4.0)];
 
    for (auto [x, y] : hist)
        std::cout << std::hex << x << ' '
                  << std::string(y / 100, '*') << '\n';
}

//
//// poisson random number generator v2
//// todo: make a macro for factorial
//// todo: can make this into one function and gain efficiencies
//
//float rand_pois(float lambda){
//    std::uniform_real_distribution<> unif_dist(0.0,1.0);
//    std::random_device rd;
//    std::mt19937 prng(rd());
//    float randi = unif_dist(prng);
//    int fac_k = 1;
//    int cdf_n = 0;
//    float p    , p_k;
//    static int k = 0;
//
//
//    for (int j = 0 ; p_k < p ; j++){
//        for (int i = 0 ; i <= k ; i++){
//            for (int jj = k ; jj  > 0 ; jj - 1){
//                fac_k *= jj;
//            }
//            cdf_n += ( ( pow(lambda, k) ) / fac_k);
//        }
//        p_k = cdf_n * exp(-lambda);
//        k++;
//    }
//    return k;
//}

/*

// poisson random number generator v2
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>


// todo: make a macro for factorial
// todo: can make this into one function and gain efficiencies

float rand_pois(float lambda){
    std::uniform_real_distribution<> unif_dist(0.0,1.0);
    std::random_device rd;
    std::mt19937 prng(rd());
    float p = unif_dist(prng);
    int cdf_n;
    float p_k;
    static int k = 1;
    int fac_k = 1;

    for (int j = 0 ; p_k < p ; j++){
        for (int i = 0 ; i <= k ; i++){
            if ((k == 1) || (k == 0)){
                fac_k = 1;
            } else  {
                fac_k = 1;
                for (int jj = k ; jj  > 1 ; jj - 1) fac_k *= jj;
            }
            cdf_n += ( ( pow(lambda, k) ) / fac_k);
        }
        p_k = cdf_n * exp(-lambda);
        k++;
    }
    return k;
}

int main()
{
    std::map<int, int> hist;
    for (int n = 0; n != 10000; ++n)
        ++hist[rand_pois(4.0)];
 
    for (auto [x, y] : hist)
        std::cout << std::hex << x << ' '
                  << std::string(y / 100, '*') << '\n';
}


// poisson random number generator v2
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>

using namespace std;

// todo: make a macro for factorial
// todo: can make this into one function and gain efficiencies

float rand_pois(float lambda){
    std::uniform_real_distribution<> unif_dist(0.0,1.0);
    std::random_device rd;
    std::mt19937 prng(rd());
    float p = unif_dist(prng);
    int cdf_n;
    float p_k;
    static int k = 1;
    int fac_k = 1;

    for (int j = 0 ; p_k <= p ; j++){
        cout << "made it to first loop\n";
        for (int i = 0 ; i <= k ; i++){
            cout << "made it to second loop\n";
            if ((k == 1) || (k == 0)){
                fac_k = 1;
            } else  {
                cout << "made it to third loop\n";
                fac_k = 1;
                for (int jj = k ; jj  >= 1 ; jj - 1) fac_k *= jj;
                cout << "made it to third loop\n";
            }
            cdf_n += ( ( pow(lambda, k) ) / fac_k);
        }
        p_k = cdf_n * exp(-lambda);
        k++;
    }
    return k;
}

int main()
{
    std::map<int, int> hist;
    for (int n = 0; n != 10000; ++n)
        ++hist[rand_pois(4.0)];
 
    for (auto [x, y] : hist)
        std::cout << std::hex << x << ' '
                  << std::string(y / 100, '*') << '\n';
}

*/
