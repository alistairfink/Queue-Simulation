#ifndef LAMDAFUNCT_H
#define LAMDAFUNCT_H

#include <math.h>
#include <cstdlib>
#include <vector>

using namespace std;

float x_func(float u, float lamda);
vector<float> generator(float lambda, int events);
vector<float> generator_timed(float lambda, float total_time);
vector<float> generator_lengths(float lambda, int events);

#endif
