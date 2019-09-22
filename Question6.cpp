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
    for(;;) {
        // Prompt user for queue utilization and length
        cout << "Queue Utilization: ";
        float queue_utilization;
        cin >> queue_utilization;
        cout << "Queue Length: ";
        int queue_length;
        cin >> queue_length;
        // Generation Params
        int simulation_time = 1000;
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
        // Empyt vector since we don't use departure events for finite queue
        std::vector<float> empty_vector;
        vector<Event> sorted_times = sort_times(arrival, length, empty_vector, observer);

        result_parameters results = simulate_finite_buffer(sorted_times, 10, 1);

        cout << "------------------------------------" << endl <<
            "P Loss: " << results.p_loss << endl <<
            "P Idle: " << results.p_idle << endl <<
            "Average Packets in Queue: " << results.avg_packets << endl << 
            "Arrivals: " << results.packet_arrivals << endl <<
            "Departures: " << results.packet_departures << endl << 
            "Observations: " << results.packet_observers << endl <<
            "Total Time: " << results.total_time << endl << endl;
    }

    return -1;
}

