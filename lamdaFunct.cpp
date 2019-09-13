#include <math.h>
#include<cstdlib>
#include<vector>
#include<iostream>
#include <random>
#include <time.h>

#include"lamdaFunct.h"

using namespace std;

float x_func(float u, float lamda){
	float k = -1.0/lamda;
	return k*log(1-u);
}

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

int main(){

	float x = 0.2;

	float ans =0;
	float lamda = 1/75;


	ans = x_func(x,lamda);

	cout<< ans<<endl;

	return 0;
}
