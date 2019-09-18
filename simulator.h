#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <math.h>
#include <cstdlib>
#include <vector>

/*Event Struct and Functions*/

struct event{
	float len;
	float time;
	char type;
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
	
	double total_time;
	
	int duration;    
	
	long double total_packets;
};


struct event init_event(char type, float time, int len){};

void print_event(struct Event E);

void print_event_list(vector<Event> vect);

//DES Functions
 struct event observers(int alpha, int duration );
 void event arrivals(float , int , int );
 

#endif
