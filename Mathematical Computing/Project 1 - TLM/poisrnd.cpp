// poisson random number generator

#include <random>
#include <iostream>
#include <math.h>


// todo: make a macro for factorial
// todo: can make this into one function and gain efficiencies

int seed = 513;

std::uniform_random_bit_generator<unsigned> unif_dist(0,1);
std::random_device rd;
std::mt19937 prng(rd());		

float rand_pois(float lambda);
float probability_pois(int k, float lambda);
float quantile_pois(float p, float lambda);
float cumulative_pois(int n, float lambda);

float rand_pois(float lambda){
	float randi = unif_dist(prng);
	float randp = quantile_pois(randi, lambda);
	return randp; 
}


float probability_pois(int k, float lambda){
	static int fac_k = 1;
	float p;
	for (k ; k  > 0 ; k - 1){
		fac_k *= k;
	}

	// Can pull this exponential multiplication out of the cumulative loop
	p = ( ( lambda^k * exp(-lambda) ) / fac_k);

	return p 
}		


// todo: make this function not suck
float quantile_pois(float p, float lambda){
	int k = 0;
	float p_k = 0;
	for (k ; p_k < p ; k++){
		// todo: integrate the cdf here so no redundant for loops
		p_k = cumulative_pois(k, lambda);
	} 
	return k;
}

float cumulative_pois(int n, float lambda){
	static cdf_n = 0;
	for (int i = 0 ; i <= n ; i++){
		cdf_n += probability_pois(n, lambda);
	}
	return cdf_n;
}

/*
That's just converting the formula given on the Wikipedia page.
If you want others, that's the place to start looking;
in general, you use the uniform variable to pick a point on the
vertical axis of the cumulative density function of the
distribution you want (assuming it's continuous), and invert
the CDF to get the random value with the desired distribution.
*/

/* 
Sum (k=0, n) e^(-lambda) frac{lambda^k}{factorial(k)} 
== sum p_k(lambda)

p(lambda) = frac{lambda^k * e^-lambda}{factorial(k)}
*/

/////////////////////////////////////////////////////////////////////

/*

// poisson random number generator

#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <math.h>

float rand_pois(float lambda, float randi);
float probability_pois(int k, float lambda);
float quantile_pois(float p, float lambda);
float cumulative_pois(int n, float lambda);

int main()
{
    int seed = 513;
    std::uniform_real_distribution<> unif_dist(0.0,1.0);
    std::random_device rd;
    std::mt19937 prng(rd());
    float randi;
    std::map<int, int> hist;
    for (int n = 0; n != 10000; ++n){
        randi = unif_dist(prng);
        ++hist[rand_pois(4,randi)];
    }
    for (auto [x, y] : hist)
        std::cout << std::hex << x << ' '
                  << std::string(y / 100, '*') << '\n';
}
// todo: make a macro for factorial
// todo: can make this into one function and gain efficiencies
float rand_pois(float lambda, float randi){
// 	float randi = unif_dist(prng);
	float randp = quantile_pois(randi, lambda);
	return randp; 
}

float probability_pois(int k, float lambda){
	static int fac_k = 1;
	float p;
	for (k ; k  > 0 ; k - 1){
		fac_k *= k;
	}

	// Can pull this exponential multiplication out of the cumulative loop
	p = ( ( pow(lambda,k) * exp(-lambda) ) / fac_k);

	return p;
}		

// todo: make this function not suck
float quantile_pois(float p, float lambda){
	int k = 0;
	float p_k = 0;
	for (k ; p_k < p ; k++){
		// todo: integrate the cdf here so no redundant for loops
		p_k = cumulative_pois(k, lambda);
	} 
	return k;
}

float cumulative_pois(int n, float lambda){
	static float cdf_n = 0;
	for (int i = 0 ; i <= n ; i++){
		cdf_n += probability_pois(n, lambda);
	}
	return cdf_n;
}

/*
That's just converting the formula given on the Wikipedia page.
If you want others, that's the place to start looking;
in general, you use the uniform variable to pick a point on the
vertical axis of the cumulative density function of the
distribution you want (assuming it's continuous), and invert
the CDF to get the random value with the desired distribution.
*/

/* 
Sum (k=0, n) e^(-lambda) frac{lambda^k}{factorial(k)} 
== sum p_k(lambda)

p(lambda) = frac{lambda^k * e^-lambda}{factorial(k)}
*/



*/