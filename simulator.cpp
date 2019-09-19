#include <math.h>
#include <cstdlib>
#include <iostream>

#include <vector>
#include <time.h>

#include "lamdaFunct.h"
#include "simulator.h"

using namespace std;

struct result_parameters test_result;

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

struct result_parameters simulate(int T, int k, int L, int C, float p ) {

	clock_t s_start, s_end;
	s_start = clock();
	
	srand(time(0));

	int simulation_time = T; 		
	int buffer_size = k;
	int transmission_rate = C;
	float roh = p;	  		
	int len_packet = L;
	
	double total_time;

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

	// Run the simulator
	observers(alpha, simulation_time);
	arrivals(lambda, simulation_time, len_packet);
	
	
	s_end = clock();
	total_time = ((double) (s_end-s_start));
	test_result.total_time = total_time;

	printf("TOTAL TIME: %f seconds\n", total_time);

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
