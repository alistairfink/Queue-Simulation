#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <cstdlib>
#include "lamdaFunct.h"
using namespace std;

vector<float> generator(float lambda, int events) {
    srand(time(0)); 
    vector<float> result;
    for(int counter = 0; counter < events; counter++) {
        float rndNum = rand() / ((double) RAND_MAX);
        float num = x_func(rndNum, lambda);
        result.push_back(num);
    }

    return result;
}

int main() {
    generator(0.0, 10);
    return -1;
}

