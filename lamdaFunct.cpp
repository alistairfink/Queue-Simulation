#include <math.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <random>
#include <time.h>

#include"lamdaFunct.h"

using namespace std;

float x_func(float u, float lamda){
	// Compute the Inverse of the exponential cumulatice distribution
	float k = -1.0/lamda;
	return k*log(1-u);
}

vector<float> generator(float lambda, int events) {
    srand(time(0)); 
    vector<float> result;
    for(int counter = 0; counter < events; counter++) {
		// Generate random number and pass that and lambda into x_func to get x. Push x to vector.
        float rndNum = rand() / ((double) RAND_MAX);
        float num = x_func(rndNum, lambda);
        // Add inter arrival time to total
        result.push_back(num);
    }

    return result;
}

vector<float> generator_timed(float lambda, float total_time) {
    srand(time(0)); 
    vector<float> result;
    float curr_time = 0;
    while(curr_time <= total_time) {
		// Generate random number and pass that and lambda into x_func to get x. Push x to vector.
        float rndNum = rand() / ((double) RAND_MAX);
        // If rndNum is 1 then regenerate otherwise will get a domain error in the log function.
        while(rndNum == 1) {
            rndNum = rand() / ((double) RAND_MAX);
        }

        float num = x_func(rndNum, lambda);
        curr_time += num;
        result.push_back(curr_time);
    }

    return result;
}

vector<float> generator_lengths(float lambda, int events) {
    srand(time(0)); 
    vector<float> result;
    for(int counter = 0; counter < events; counter++) {
        // Generate random number and pass that and lambda into x_func to get x. Push x to vector.
        float rndNum = rand() / ((double) RAND_MAX);
        float num = x_func(rndNum, lambda);
        result.push_back(num);
    }

    return result;
}