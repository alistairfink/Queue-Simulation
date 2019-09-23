#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <thread>

#include "lamdaFunct.h"
#include "sorter.h"
#include "simulator.h"

using namespace std;

int main() {
    int lamda = 75;
    int generation_amount = 1000;
    int average_length = 2000;
    vector<float> arrival = generator(lamda, generation_amount);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    vector<float> length = generator_lengths(1.0/average_length, arrival.size());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    vector<float> departure = generator(lamda, generation_amount);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    vector<float> observer = generator(lamda, generation_amount);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    vector<Event> sorted_times = sort_times(arrival, length, departure, observer);
    for (std::size_t i = 0; i < sorted_times.size(); ++i) {
        cout << sorted_times[i].type << " " << sorted_times[i].time << " " << sorted_times[i].len << endl;
    }
    
    return -1;
}

