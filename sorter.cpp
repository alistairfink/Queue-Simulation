#include <math.h>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <iostream>

#include "sorter.h"
#include "simulator.h"

using namespace std;

vector<event> sort_times(vector<float> arrival, vector<float> departure, vector<float> observer) {
    std::size_t arrival_counter = 0;
    std::size_t departure_counter = 0;
    std::size_t observer_counter = 0;

    vector<event> result;
    // Keep looping until no more events 
    while(arrival_counter < arrival.size() || departure_counter < departure.size() || observer_counter < observer.size()) {
        if(arrival_counter < arrival.size() && 
            (departure_counter >= departure.size() || arrival[arrival_counter] <= departure[departure_counter]) &&
            (observer_counter >= observer.size() || arrival[arrival_counter] <= observer[observer_counter])) {
            // If arrival is lowest then add arrival to result
            event arrival_event = {
                0,
                arrival[arrival_counter],
                'a'
            };
            result.push_back(arrival_event);
            arrival_counter++;
        } else if(departure_counter < departure.size() &&
            (arrival_counter >= arrival.size() || departure[departure_counter] <= arrival[arrival_counter]) &&
            (observer_counter >= observer.size() || departure[departure_counter] <= observer[observer_counter])) {
            // If departure is lowest then add departure to result
            event departure_event = {
                0,
                departure[departure_counter],
                'd'
            };
            result.push_back(departure_event);
            departure_counter++;
        } else {
            // If neither arrival or departure is lowest then it has to be observer
            event observer_event = {
                0,
                observer[observer_counter],
                'o'
            };
            result.push_back(observer_event);
            observer_counter++;
        }
    }

    return result;
}