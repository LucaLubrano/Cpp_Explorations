//
//  BCRN.cpp
//  Tau_Leap_Method
//
//  Created by Luca Lubrano Lavadera on 11/3/2025.
//

// todo: make a struct/class to contain the species data
// todo: make a construct for the struct/class for MMC, EK, and MAPK (double EK)
//const int tau = 2;
//const int T = 100;
//const int t0 = 0;
//const float k[3] = {1, 0.1, 0.05};
//const int x0[2] = {100, 0};
//const int nu[3][2] = {{1, 0},{-1, 1},{0, -1}};

//class MMC_BRCN {
//private :
//    float k[3] = {1, 0.1, 0.05};
//    int x0[2] = {100,0};
//    int nu[3][2] = {{1, 0},{-1, 1},{0, -1}};
//    float t0 = 0;
//    float T = 100;
//public :
//    
//    MMC_BRCN(int timesteps)
//      : int popA[timesteps],
//        int popB(timesteps){
//    }
//    
//    float* prop_func(int x[2], const float k[3]){
//        static float propensities[3];
//        if (x[0] < 0) {
//            x[0] = 0;
//        }
//        if (x[1] < 0) {
//            x[1] = 0;
//        }
//        propensities[0] = k[0];
//        propensities[1] = k[1] * x[0];
//        propensities[2] = k[2] * x[1];
//        return propensities;
//    }
//};

struct MMC_BRCN {
    float k[3] = {1, 0.1, 0.05};
    int x0[2] = {100,0};
    int nu[3][2] = {{1, 0},{-1, 1},{0, -1}};
    float* prop_func(int x[2], const float k[3]){
        static float propensities[3];
        if (x[0] < 0) {
            x[0] = 0;
        }
        if (x[1] < 0) {
            x[1] = 0;
        }
        propensities[0] = k[0];
        propensities[1] = k[1] * x[0];
        propensities[2] = k[2] * x[1];
        return propensities;
    }
} ;

struct EK_BRCN {
    float k[3] = {1, 0.1, 0.05};
    int x0[2] = {100,0};
    int nu[3][2] = {{1, 0},{-1, 1},{0, -1}};
    float* prop_func(int x[2], const float k[3]){
        static float propensities[3];
        if (x[0] < 0) {
            x[0] = 0;
        }
        if (x[1] < 0) {
            x[1] = 0;
        }
        propensities[0] = k[0];
        propensities[1] = k[1] * x[0];
        propensities[2] = k[2] * x[1];
        return propensities;
    }
} ;
