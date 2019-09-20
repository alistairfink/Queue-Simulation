#ifndef SORTER_H
#define SORTER_H

#include <math.h>
#include <cstdlib>
#include <vector>

#include "simulator.h"

using namespace std;

vector<Event> sort_times(vector<float> arrival, vector<float> length, vector<float> departure, vector<float> observer);

#endif
