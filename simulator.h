#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <math.h>
#include <cstdlib>
#include <vector>

using namespace std;
/*Event Struct and Functions*/

 struct Event{
	float len;
	float time;
	char type;
};

struct Packet {
	float len;
	float time;
	float departure_time;
};

struct result_parameters {
	//Average:
	float lambda;	// packets generated
	float alpha;	// length of a packet in bits
	float roh;		// number of observer events per second
	float avg_packets;
	
	float p_loss;	// packet loss probability M/M/1/K
	float p_idle; 	// proportion of time server is idle
	 
	int len_packet, link_rate, size_buffer;
	
	//number of packet arrivals, packet departures, observers
	int packet_arrivals, packet_departures, packet_observers; 
	
	vector<float> service_time_vect;

	double total_time;
	
	int duration;    
	
	long double total_packets;
};


Event init_event(char type, float time, int len);

void print_event(struct Event E);

void print_event_list(vector<Event> vect);

//DES Functions
Event observers(int alpha, int duration );
Event arrivals(float , int , int );
 
result_parameters simulate(vector<Event> vect, int C);
result_parameters simulate_finite_buffer(vector<Event> events, int buffer_size, int transmission_rate);

#endif
