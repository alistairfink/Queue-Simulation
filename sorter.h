#ifndef SORTER_H
#define SORTER_H

#include <math.h>
#include <cstdlib>
#include <vector>

#include "simulator.h"

using namespace std;

vector<event> sort_times(vector<float> arrival, vector<float> departure, vector<float> observer);

#endif
