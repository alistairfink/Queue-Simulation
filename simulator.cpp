
#include <math.h>
#include <cstdlib>
#include <vector>
#include "lamdaFunct.h"
#include "simulator.h"

using namespace std;


// Event Struct and Functions
struct event init_event(char type, float time, int len){
	
	 Event event;
	
		if (event.type == 'a')
		{
			event.len = generator(lamda,1);
		}
		else
		{
			event.len = len_packet;
		}
		
		return event;
}

void print_event{struct Event E}{
 	cout << "\n Event Type : " << E.type << "\n Event Time : " << E.time << "\n Event Length: %f " << E.len << endl;
}

void print_event_list(vector<Event> vect){
    
	if(vect.empty())
        cout << "No events in the Queuee."\n;
    else
        for (int i = 0; i < vect.size(); i++)                          
            {
                cout << "\n Event Type : " << vect[count].type << "\n Event Time : " << vect[i].time << "\n Event Length: %f " << vect[i].len << endl;
			}
}

 
	//Discrete Event Simulation Functions
 
 struct event observers(int alpha, int duration)
{
 	event e;
	float curr_time=0;
 	float tmp_time;


	while (curr_time <= duration) {
		curr_time += generator(alpha,1);
		
		if (curr_time > duration) {
			break;
		}

		e = init_event('O', current_time, 0);
		return e;
	}

}

 struct event arrivals(float , int , int ){
 	float curr_time = 0;
	event e;

	while (curr_time <= duration) {
		curr_time += generator(lamda,1);
		
		if (curr_time > duration) {
			break;
		}

		e = init_event('A', curr_time, len_packet);
		return e;
	}
}
 }
 
int main()
{
	
	event t_event;
	t_event = init_event('A',5,10);
	print_event(t_event);
	
	return 0;
}
