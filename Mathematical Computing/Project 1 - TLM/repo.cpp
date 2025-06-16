//
//  repo.cpp
//  Poisson_Random_Number
//
//  Created by Luca Lubrano Lavadera on 15/3/2025.
//

//
//float rand_pois(float lambda){
//    std::uniform_real_distribution<> unif_dist(0.0,1.0);
//    std::random_device rd;
//    std::mt19937 prng(rd());
//    
//    const float p = unif_dist(prng);
//    float cdf_n = 0;
//    float p_k = 0;
//    int k = -1;
//    int fac_k = 0;
//
//    while (p_k <= p){
//        k++;
//        fac_k = 1; cdf_n = 0;
//        for (int i = 0 ; i <= k ; i++){
//            if ((i == 1) || (i == 0)){
//                fac_k = 1;
//            } else  {
//                fac_k = 1;
//                for (int jj = i ; jj >= 1 ; jj--) {
//                    fac_k *= jj;
//                }
//            }
//            cdf_n += exp(-lambda) * (pow(lambda, k) / fac_k) ;
//            cout << cdf_n << " | " << p << " | " << i <<'\n' ;
//        }
//        p_k = cdf_n ;
//        
//        if ( ( k == 0 ) && (p_k >= p) ){
//            break;
//        }
//        
//    }
//    return k;
//}
