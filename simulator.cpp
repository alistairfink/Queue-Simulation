#include <math.h>
#include <cstdlib>
#include <iostream>

#include <vector>
#include <time.h>

#include "lamdaFunct.h"
#include "simulator.h"

using namespace std;

// Event Struct and Functions
 Event init_event(char type, float time, int len){
	
	  Event event;
	  float lambda = 1.0/len;
	  vector<float> tmp = generator(lambda,1);
	
		if (type == 'a')
		{			
			event.len = tmp.pop_back();
		}
		else
		{
			event.len = len;
		}
		event.time = time;
		event.type = type;
		
		return event;
}


void print_event(struct Event E){
 	cout << "\n Event Type : " << E.type << "\n Event Time : " << E.time << "\n Event Length: %f " << E.len << endl;
}

void print_event_list(vector<Event> vect){
    
	if(vect.empty())
        cout << "No events in the Queue.\n";
    else{
    		for (int i = 0; i < vect.size(); i++)                          
	            {
	                cout << "\n Event Type : " << vect[i].type << "\n Event Time : " << vect[i].time << "\n Event Length: %f " << vect[i].len;
				}
	}  
}
 
	//Discrete Event Simulation Functions
 
 Event observers(int alpha, int duration)
{
 	Event e;
	float curr_time=0;
 	float tmp_time;

	while (curr_time <= duration) {
		
		vector<float> tmp;
		tmp = generator(alpha,1);
		float gen_time = tmp.pop_back();
		curr_time += gen_time; 
		
		if (curr_time > duration) {
			break;
		}

		e = init_event('O', curr_time, 0);
		return e;
	}

}

  Event arrivals(float lambda , int len_packet, int duration ){
 	float curr_time = 0;
	Event e;

	while (curr_time <= duration) {
		vector<float> tmp;
		tmp= generator(lambda,1);
		float gen_time = tmp.push_back();
		curr_time += gen_time;
	
		if (curr_time > duration) {
			break;
		}

		e = init_event('A', curr_time, len_packet);
		return e;
	}
}

struct result_parameters simulate(vector<Event> vect, int C) {

	//Initiate counters
	struct result_parameters test_result;
	int arrivals_counter = 0; 
	int observer_counter = 0;
	int departure_counter = 0;
	int curr_service_time=0;
	int last_arrival_time = 0;

	// Run the simulator
	for (int i = 0; i < vect.size; i++) {

		//Arrival Event
		if (vect[i].type == 'a') {
			arrivals_counter++;
			last_arrival_time = vect[i].time;
		}
		//Observer Event
		else if (vect[i].type == 'o') {
			observer_counter++;
		}
		//Departure Event
		else if (vect[i].type == 'd') {
			departure_counter++;
			curr_service_time = (vect[i].len / C)+ last_arrival_time;
			test_result.service_time_vect.push_back(curr_service_time);
		}
		else {
			cout << "invalid Event Type" << endl;
		}
	}
	
	test_result.packet_arrivals = arrivals_counter;
	test_result.packet_observers = observer_counter;
	test_result.packet_departures = departure_counter;

	//calculate departure time  lengBits/tranmission rate+arrival time
	int simulation_time = T; 		
	int transmission_rate = C;
	float roh = p;	  		
	int len_packet = L;
	
	float lambda = (roh / len_packet) * transmission_rate; 
	float alpha = lambda + 5;

	cout<<"T : %d seconds /n"<<endl;
	cout<<"K : %d  /n"<<endl;
	cout<<"C : %d /n"<<endl;
	cout<<"Alpha : %f /n"<<endl;
	cout<<"Roh : %f /n "<<endl;
	cout<<"Lambda %f\n " <<endl;
	cout<<"L : %d /n"<<endl;
	
	test_result.duration = T;
	test_result.alpha = alpha;
	test_result.lambda = lambda;
	test_result.len_packet = len_packet;
	test_result.link_rate = transmission_rate;
	test_result.size_buffer = buffer_size;
	test_result.roh = roh;

	return test_result;
}

int main()
{
	
	Event t_event;
	t_event = init_event('A',5,10);
	print_event(t_event);
	cout<<"test";
	return 0;
}
