//
//  tau_leap.cpp
//  Tau_Leap_Method
//
//  Created by Luca Lubrano Lavadera on 11/3/2025.
//
#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <time.h>
#include "poisrnd.h"
using namespace std;

//------------------------------------------------------------
// Function Prototyping
//------------------------------------------------------------

float* prop_func(float x[2], const float k[3]);
void tau_leap(int x0[2], float k[3], int nu[3][2], float tau, int t0, int T);

/* Helper functions */
void print_TL(void);
void savetofile(void);

//------------------------------------------------------------
// Struct Definitions
//------------------------------------------------------------

/* Species data tracker per timestep*/
// todo: put this in the struct file, make a constructor etc...
//typedef struct{
//    int popA;
//    int popB;
//    int t;
//} SpeciesTimestepData;

//------------------------------------------------------------
// Function Definition
//------------------------------------------------------------

/* Propensity Function */
// todo: define the propensity functions with the data struct/class
float* prop_func(int popA, int popB, const float k[3]){
    static float propensities[3];
    if (popA < 0) {
        popA = 0;
    }
    if (popB < 0) {
        popB = 0;
    }
    propensities[0] = k[0];
    propensities[1] = k[1] * popA;
    propensities[2] = k[2] * popB;
    return propensities;
}
//
///* Tau Leap Simulation Function */
//// todo: make the sizes of the inputs variable ( research to see how this could be done - templates(?))
//// todo: put file output functionality into seperate function (maybe?)
//// current speed ~48 microseconds
//// vector<vector<int>> tau_leap(int x0[2], float k[3], int nu[3][2], float tau, int t0, int T){
//void tau_leap(int x0[2], float k[3], int nu[3][2], float tau, int t0, int T){
////    print_TL();
//    std::default_random_engine generator;
//    const int n = (int)((T - t0)/tau) + 1;
////    const int num_species = (int) sizeof(x0) / sizeof(x0[0]);
//    const float* temp_prop_func = prop_func(x0, k);
////    const int length_a = ((int) sizeof(temp_prop_func) / sizeof(temp_prop_func[0])) + 1;
//    float lambda, reaction_event;
//    float* eval_ptr;
//    float t[n];
//    t[0] = t0;
//    int copy_num[num_species][n];
//    int temp_copy_num[num_species];
//    
////    const int rand_nums[n*3] =
//    
//    for (int i = 0 ; i < num_species ; i++) {
//        copy_num[i][0] = x0[i];
//        temp_copy_num[i] = x0[i];
//    }
//    
//    for (int i = 1 ; i <= n ; i++){
//        
//        t[i] = i * tau;
////        eval_ptr = prop_func(temp_copy_num, k);
//        
//        for (int j = 0 ; j < length_a ; j++){
//        
//            lambda = eval_ptr[j] * tau;
//            std::poisson_distribution<int> distribution(lambda);
//            reaction_event = distribution(generator);
////            reaction_event = 3;
//            
//            for (int jj = 0 ; jj < num_species ; jj++){
////                copy_num[jj][i] += reaction_event * nu[j][jj];
//                temp_copy_num[jj] += reaction_event * nu[j][jj]; // todo: fix this
//            }
//        }
//
//        for (int ii = 0 ; ii < num_species ; ii++){
//            copy_num[ii][i] = temp_copy_num[ii];
//        }
//    }
//}
//void tau_leap_v2(int x0[2], float k[3], int nu[3][2], float tau, int t0, int T){
////    print_TL();
//    std::default_random_engine generator;
//    const int n = (int)((T - t0)/tau) + 1;
////    const float* temp_prop_func = prop_func(x0, k);
////    const int length_a = ((int) sizeof(temp_prop_func) / sizeof(temp_prop_func[0])) + 1;
//    float lambda, reaction_event;
//    float* eval_ptr;
//    float t[n];
//    t[0] = t0;
//    int copy_num[2][n];
//    int temp_copy_num[2];
//
//    
//    for (int i = 0 ; i < 2 ; i++) {
//        copy_num[i][0] = x0[i];
//        temp_copy_num[i] = x0[i];
//    }
//    
//    for (int i = 1 ; i <= n ; i++){
//        
//        t[i] = i * tau;
////        eval_ptr = prop_func(temp_copy_num, k);
//        
//        for (int j = 0 ; j < length_a ; j++){
//        
//            lambda = eval_ptr[j] * tau;
//            std::poisson_distribution<int> distribution(lambda);
//            reaction_event = distribution(generator);
//            temp_copy_num[0] += reaction_event * nu[j][0];
//            temp_copy_num[1] += reaction_event * nu[j][1];
//        }
//
//        copy_num[0][i] = temp_copy_num[0]; copy_num[1][i] = temp_copy_num[1];
//    }
//}

#define LENGTH_A 3
#define NUM_SPECIES 2


void tau_leap_v3(int x0[2], float k[3], int nu[3][2], float tau, int t0, int T){
//    print_TL();
    std::uniform_real_distribution<> unif_dist(0.0,1.0);
    std::random_device rd;
    std::mt19937 prng(rd());
    const int n = (int)((T - t0)/tau) + 1;
    float lambda, reaction_event;
    float* eval_ptr;
    float t[n];
    t[0] = t0;
    int copy_num[2][n];
    copy_num[0][0] = x0[0];
    copy_num[1][0] = x0[1];
    
    for (int i = 1 ; i <= n ; i++){
        t[i] = i * tau;
        eval_ptr = prop_func(copy_num[0][i-1], copy_num[1][i-1], k);
        for (int j = 0 ; j < LENGTH_A ; j++){
            lambda = eval_ptr[j] * tau;
            reaction_event = pois_rand(lambda);
            copy_num[0][i] += reaction_event * nu[j][0];
            copy_num[1][i] += reaction_event * nu[j][1];
        }
    }
}














/* Helper Functions */

void print_TL(void){
    std::cout <<"    ________________   ____ ___  .____     ___________   _____ __________      " << '\n';
    std::cout <<"    \\__    ___/  _  \\ |    |   \\ |    |    \\_   _____/  /  _  \\\\______   \\     " <<'\n';
    std::cout <<"      |    | /  /_\\  \\|    |   / |    |     |    __)_  /  /_\\  \\|     ___/     " << '\n';
    std::cout <<"      |    |/    |    \\    |  /  |    |___  |        \\/    |    \\    |         " << '\n';
    std::cout <<"      |____|\\____|__  /______/   |_______ \\/_______  /\\____|__  /____|         " << '\n';
    std::cout <<"                    \\/                   \\/        \\/         \\/               " << '\n';
}

//void savetofile(void){
//    fstream myfile;
//    myfile.open("mmc_tau_leap_data.csv", ios::out);
//    cout << myfile.is_open() << endl;
//    myfile << copy_num[0] << "," << copy_num[1] << '\n';
//    myfile << copy_num[0] << "," << copy_num[1] << '\n';
//    myfile.close();
//}

//    fstream myfile;
//    myfile.open("mmc_tau_leap_data_v2.csv", ios::out);
//    cout << myfile.is_open() << endl;
//    for (int i = 0 ; i < n ; i++){
//        myfile << copy_num[0][i] << "," << copy_num[1][i] << "," << t[i] << '\n';
//    }
//    myfile.close();
