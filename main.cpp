#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <cstdlib>
#include "lamdaFunct.h"

using namespace std;

int main() {
    vector<float> result = generator(75, 1000);
    for(std::size_t i=0; i<result.size(); ++i) {
        cout << result[i] << endl;
    }

    return -1;
}