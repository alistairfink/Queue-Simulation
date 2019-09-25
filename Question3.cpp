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

void user_input();
void run_simulation(float queue_utilization, int simulation_time);
void run_test_cases();
void run_stability_test();

int main() {
    // Ask user if they want to run the defaults.
    cout << "Run Default Simulation?(y/n) ";
    char response;
    cin >> response;
    if(response == 'y') {
        run_test_cases();
    } else {
        cout << "Run Stability Test?(y/n) ";
        cin >> response;
        if (response == 'y') {
            run_stability_test();
        } else {
            user_input();
        }
    }

    return 0;
}

void run_test_cases() {
    // Default buffer lengths and queue utilizations to simulate
    float queue_utilizations[] = {0.25, 0.35, 0.45, 0.55, 0.65, 0.75, 0.85, 0.95};

    // Print headers at the top of all the results in csv format
    cout << "Queue Utilization, P_Idle, Average Packets in Queue, Arrivals, Departures, Observations, Total Time" << endl;
    for (int j = 0; j < sizeof(queue_utilizations)/sizeof(queue_utilizations[0]); ++j) {
        // Loop through combinations and run sim for each.
        run_simulation(queue_utilizations[j], 1000);
    }
}

void run_stability_test() {
    // Print headers at the top of all the results in csv format
    cout << "Queue Utilization, P_Idle, Average Packets in Queue, Arrivals, Departures, Observations, Total Time" << endl;
    run_simulation(0.5, 1000);
    run_simulation(0.5, 2000);
}

void user_input() {
    for(;;) {
        // Prompt user for queue utilization and length
        cout << "Queue Utilization: ";
        float queue_utilization;
        cin >> queue_utilization;

        // Print headers for csv format and run sim
        cout << "Queue Utilization, P_Idle, Average Packets in Queue, Arrivals, Departures, Observations, Total Time" << endl;
        run_simulation(queue_utilization, 1000);
    }
}

void run_simulation(float queue_utilization, int simulation_time) {
    // Generation Params
    int average_length = 2000;

    // Calculate lambda. queue_utilization*transmission_rate(1mbps)/average_length
    int lambda = queue_utilization*1000000/average_length;
    // Generate arrival, arrival lengths, and observer events, then sort them (combining arrivals and arrival lengths)
    vector<float> arrival = generator_timed(lambda, simulation_time);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    vector<float> length = generator_lengths(1.0/average_length, arrival.size());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    vector<float> departure = generator_timed(lambda, simulation_time);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    vector<float> observer = generator_timed(5*lambda, simulation_time);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Empty vector since we don't use departure events for finite queue and sort by time
    vector<Event> sorted_times = sort_times(arrival, length, departure, observer);

    // Run sim
    result_parameters results = simulate(sorted_times, 1);

    // Print Results in csv format
    cout << queue_utilization << ", "
        << results.p_idle << ", " 
        << results.avg_packets << ", " 
        << results.packet_arrivals << ", " 
        << results.packet_departures << ", " 
        << results.packet_observers << ", " 
        << results.total_time << endl;
}