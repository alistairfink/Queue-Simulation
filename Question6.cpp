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
void run_simulation(float queue_utilization, int queue_length, int simulation_time);
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
    int buffer_lengths[] = {10, 25, 50};
    float queue_utilizations[] = {0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.2, 2.4, 2.6, 2.8, 3, 3.2, 3.4, 3.6, 3.8, 4, 4.2, 4.4, 4.6, 4.8, 5, 5.4, 5.8, 6.2, 6.6, 7, 7.4, 7.8, 8.2, 8.6, 9, 9.4, 9.8};

    // Print headers at the top of all the results in csv format
    cout << "Queue Utilization, Buffer Length, P_Loss, P_Idle, Average Packets in Queue, Arrivals, Departures, Observations, Total Time" << endl;
    for (int i = 0; i < sizeof(buffer_lengths)/sizeof(buffer_lengths[0]); ++i) {
        for (int j = 0; j < sizeof(queue_utilizations)/sizeof(queue_utilizations[0]); ++j) {
            // Loop through combinations and run sim for each.
            run_simulation(queue_utilizations[j], buffer_lengths[i], 1000);
        }
    }
}

void run_stability_test() {
    // Print headers at the top of all the results in csv format
    cout << "Queue Utilization, Buffer Length, P_Loss, P_Idle, Average Packets in Queue, Arrivals, Departures, Observations, Total Time" << endl;
    run_simulation(3.6, 25, 1000);
    run_simulation(3.6, 25, 2000);
}

void user_input() {
    for(;;) {
        // Prompt user for queue utilization and length
        cout << "Queue Utilization: ";
        float queue_utilization;
        cin >> queue_utilization;
        cout << "Buffer Length: ";
        int queue_length;
        cin >> queue_length;

        // Print headers for csv format and run sim
        cout << "Queue Utilization, Buffer Length, P_Loss, P_Idle, Average Packets in Queue, Arrivals, Departures, Observations, Total Time" << endl;
        run_simulation(queue_utilization, queue_length, 1000);
        run_simulation(queue_utilization, queue_length, 2000);
    }
}

void run_simulation(float queue_utilization, int queue_length, int simulation_time) {
    // Generation Params
    int average_length = 2000;

    // Calculate lambda. queue_utilization*transmission_rate(1mbps)/average_length
    int lambda = queue_utilization*1000000/average_length;
    // Generate arrival, arrival lengths, and observer events, then sort them (combining arrivals and arrival lengths)
    vector<float> arrival = generator_timed(lambda, simulation_time);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    vector<float> length = generator_lengths(1.0/average_length, arrival.size());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    vector<float> observer = generator_timed(5*lambda, simulation_time);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Empty vector since we don't use departure events for finite queue and sort by time
    std::vector<float> empty_vector;
    vector<Event> sorted_times = sort_times(arrival, length, empty_vector, observer);

    // Run sim
    result_parameters results = simulate_finite_buffer(sorted_times, queue_length, 1);

    // Print Results in csv format
    cout << queue_utilization << ", " 
        << queue_length << ", " 
        << results.p_loss << ", " 
        << results.p_idle << ", " 
        << results.avg_packets << ", " 
        << results.packet_arrivals << ", " 
        << results.packet_departures << ", " 
        << results.packet_observers << ", " 
        << results.total_time << endl;
}