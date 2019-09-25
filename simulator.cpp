#include <math.h>
#include <cstdlib>
#include <iostream>

#include <vector>
#include <queue>
#include <time.h>

#include "lamdaFunct.h"
#include "simulator.h"

using namespace std;

// Event Struct and Functions
//  Event init_event(char type, float time, int len){
	
// 	  Event event;
// 	  float lambda = 1.0/len;
// 	  vector<float> tmp = generator(lambda,1);
	
// 		if (type == 'a')
// 		{			
// 			event.len = tmp.pop_back();
// 		}
// 		else
// 		{
// 			event.len = len;
// 		}
// 		event.time = time;
// 		event.type = type;
		
// 		return event;
// }


// void print_event(struct Event E){
//  	cout << "\n Event Type : " << E.type << "\n Event Time : " << E.time << "\n Event Length: %f " << E.len << endl;
// }

// void print_event_list(vector<Event> vect){
    
// 	if(vect.empty())
//         cout << "No events in the Queue.\n";
//     else{
//     		for (int i = 0; i < vect.size(); i++)                          
// 	            {
// 	                cout << "\n Event Type : " << vect[i].type << "\n Event Time : " << vect[i].time << "\n Event Length: %f " << vect[i].len;
// 				}
// 	}  
// }
 
// 	//Discrete Event Simulation Functions
 
//  Event observers(int alpha, int duration)
// {
//  	Event e;
// 	float curr_time=0;
//  	float tmp_time;

// 	while (curr_time <= duration) {
		
// 		vector<float> tmp;
// 		tmp = generator(alpha,1);
// 		float gen_time = tmp.pop_back();
// 		curr_time += gen_time; 
		
// 		if (curr_time > duration) {
// 			break;
// 		}

// 		e = init_event('O', curr_time, 0);
// 		return e;
// 	}

// }

//   Event arrivals(float lambda , int len_packet, int duration ){
//  	float curr_time = 0;
// 	Event e;

// 	while (curr_time <= duration) {
// 		vector<float> tmp;
// 		tmp= generator(lambda,1);
// 		float gen_time = tmp.push_back();
// 		curr_time += gen_time;
	
// 		if (curr_time > duration) {
// 			break;
// 		}

// 		e = init_event('A', curr_time, len_packet);
// 		return e;
// 	}
// }

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
	// Run the simulator
	int i = 0;

	// Multiply transmission rate out so I'm comparing bits to bits vs bits to mbits.
	int transmission_rate = C*1000000;

	while(!buffer.empty() || i < vect.size()) {
		if(i < vect.size() && (buffer.empty() || vect[i].time < buffer.front().departure_time)) {
			//Arrival Event
			if (vect[i].type == 'a') {
				arrivals_counter++;
				last_arrival_time = vect[i].time;

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
				observer_counter++;
				packets_in_buffer += buffer.size();
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
	
	test_result.packet_arrivals = arrivals_counter;
	test_result.packet_observers = observer_counter;
	test_result.packet_departures = departure_counter;

	//calculate departure time  lengBits/tranmission rate+arrival time
	// int simulation_time = T;
	// float roh = p;	  		
	// int len_packet = L;
	
	// float lambda = (roh / len_packet) * transmission_rate; 
	// float alpha = lambda + 5;

	// test_result.duration = T;
	// test_result.alpha = alpha;
	// test_result.lambda = lambda;
	// test_result.len_packet = len_packet;
	test_result.link_rate = transmission_rate;
	test_result.avg_packets = packets_in_buffer / float(observer_counter);
	test_result.p_idle = idle_time / prev_event;
	test_result.total_time = prev_event;
	// test_result.size_buffer = buffer_size;
	// test_result.roh = roh;

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

// int main()
// {
	
// 	Event t_event;
// 	t_event = init_event('A',5,10);
// 	print_event(t_event);
// 	cout<<"test";
// 	return 0;
// }
