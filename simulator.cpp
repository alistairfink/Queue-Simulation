#include <math.h>
#include <cstdlib>
#include <iostream>

#include <vector>
#include <queue>
#include <time.h>

#include "lamdaFunct.h"
#include "simulator.h"

using namespace std;

result_parameters simulate(vector<Event> vect, int C) {
	//Initiate counters
	result_parameters test_result;
	int arrivals_counter = 0; 
	int observer_counter = 0;
	int departure_counter = 0;
	int curr_service_time=0;
	int last_arrival_time = 0;

	unsigned long long int packets_in_buffer = 0;
	float idle_time = 0.0;
	float prev_event = 0.0;

	std::queue<Packet> buffer;
	int i = 0;

	// Multiply transmission rate out so I'm comparing bits to bits vs bits to mbits.
	int transmission_rate = C*1000000;

	// Run the simulator
	while(!buffer.empty() || i < vect.size()) {
		// If next event to process is in vect then process that otherwise process the front of the queue.
		if(i < vect.size() && (buffer.empty() || vect[i].time < buffer.front().departure_time)) {
			//Arrival Event
			if (vect[i].type == 'a') {
				// Itterate arrival counter
				arrivals_counter++;

				// Instantiate new packet to be pushed into buffer.
				Packet new_packet = {
					vect[i].len,
					vect[i].time,
					0
    			};

    			// If the buffer is empty then departure time is calculated based on the packet length else 
    			// need to factor in based on the departure time of the packet at the back of the buffer.
    			if(buffer.empty()) {
    				new_packet.departure_time = vect[i].time + vect[i].len / transmission_rate;
    			} else {
    				new_packet.departure_time = buffer.back().departure_time + vect[i].len / transmission_rate;
    			}

    			buffer.push(new_packet);
			}
			//Observer Event
			else if (vect[i].type == 'o') {
				// Itterate observer counter
				observer_counter++;

				// Add number of packets for avg packets calculation later.
				packets_in_buffer += buffer.size();

				// If no packets in buffer then get time since last event and add that time to total idle time for later percentage idle time calc.
				if(buffer.size() == 0) {
					idle_time += vect[i].time - prev_event;
				}
			}
			else {
				cout << "invalid Event Type" << endl;
			}

			prev_event = vect[i].time;
			i++;
		} else {
			// Pop packet off queue and increment departure counter.
			departure_counter++;
			prev_event = buffer.front().departure_time;
			buffer.pop();
		}
	}
	
	// Input metrics into results struct
	test_result.packet_arrivals = arrivals_counter;
	test_result.packet_observers = observer_counter;
	test_result.packet_departures = departure_counter;

	test_result.link_rate = transmission_rate;
	// Avg Packets in buffer is sum of packets in buffer at each observation event / number of observation events.
	test_result.avg_packets = packets_in_buffer / float(observer_counter);
	// Idle time is percentage of total time that the system was idle.
	test_result.p_idle = idle_time / prev_event;
	test_result.total_time = prev_event;

	return test_result;
}

result_parameters simulate_finite_buffer(vector<Event> events, int buffer_size, int transmission_rate) {
	// Initialize buffer and itterator.
	std::queue<Packet> buffer;
	std::size_t i = 0;

	// Multiply transmission rate out so I'm comparing bits to bits vs bits to mbits.
	transmission_rate *= 1000000;

	// Initialize counters and stats
	int packets_in_queue = 0;
	int num_arrivals = 0;
	int num_departures = 0;
	int num_observations = 0;
	int num_dropped = 0;

	float prev_time = 0;
	float idle_time = 0;

	// Start simulation
	while(!buffer.empty() || i < events.size()) {
		// If next closest event is in events vector then process that. Else departure is closest to current time so process that.
		if(i < events.size() && (buffer.empty() || events[i].time < buffer.front().departure_time)) {
			// Arrivals and Observations are handled differently.
			if(events[i].type == 'a') {
				// Increment Arrival Counter
				num_arrivals++;

				// If buffer is full then drop the packet.
				if(buffer.size() == buffer_size) {
					num_dropped++;
				} else {
					// Create new packet and calculate the departure time then add to queue.
					Packet new_packet = {
						events[i].len,
						events[i].time,
						0
        			};

        			// If the buffer is empty then departure time is calculated based on the packet length else 
        			// need to factor in based on the departure time of the packet at the back of the buffer.
        			if(buffer.empty()) {
        				new_packet.departure_time = events[i].time + events[i].len / transmission_rate;
        			} else {
        				new_packet.departure_time = buffer.back().departure_time + events[i].len / transmission_rate;
        			}

        			buffer.push(new_packet);
				}
			} else {
				// Increment observations counter and 
				num_observations++;
				// If buffer is empty then record the time since the previous event and add to idle time.
				if(buffer.empty()) {
					idle_time += events[i].time - prev_time;
				}

				// Average number of packets in buffer????????????????????????????????????
				packets_in_queue += buffer.size();
			}

			// prev_time is the current time then itterate the event itterator
			prev_time = events[i].time;
			i++;
		} else {
			// Pop packet off queue and increment departure counter.
			num_departures++;
			prev_time = buffer.front().departure_time;
			buffer.pop();
		}
	}

	// Initialize result structure and do all the calculations then return.
	result_parameters results = {};
	results.avg_packets = float(packets_in_queue)/float(num_observations);
	// p_loss is ratio of dropped to toal number of arrivals/packets.
	results.p_loss = float(num_dropped)/float(num_arrivals);
	// p_idle is ratio of time queue was idle.
	results.p_idle = idle_time/prev_time;
	results.packet_arrivals = num_arrivals;
	results.packet_departures = num_departures;
	results.packet_observers = num_observations;
	// prev_time of last event so total time elapsed.
	results.total_time = prev_time;
	return results;
}