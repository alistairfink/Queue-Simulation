#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <cstdlib>
#include "lamdaFunct.h"

using namespace std;

int main() {
	// Generate values and print them.
	vector<float> result = generator(75, 1000);
	float total = 0;
	for (std::size_t i = 0; i < result.size(); ++i) {
		cout << result[i] << endl;
		total += result[i];
	}

	float mean = total / 1000.0;
	cout << "Mean: " << mean << endl;

	float variance = 0;
	for (std::size_t i = 0; i < result.size(); ++i) {
		variance += (result[i] - mean)*(result[i] - mean);
	}

	cout << "Variance: " << variance / 1000 << endl;
	return -1;
}