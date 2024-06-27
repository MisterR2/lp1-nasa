#include <iostream>
#include <vector>
#include "astronaut.h"
#include <algorithm>
#include <string>
#include <list>
#include <map>

#ifndef FLIGHT_H
#define FLIGHT_H


using namespace std;
class Flight
{
private:
    int code;
    map<string, Astronaut> passengers;
    bool planning;
    bool in_course;
    bool finished;
    bool failed;
    
    static map<int, Flight*> flights;

    // static map<int, Flight*> flights;

public:
    Flight(int code, bool failed = false, bool planning = true, bool in_course = false, bool finished = false);

    int getCode();
    string getStatus();
    map<string, Astronaut> getPassengers();

    void createPassengers();
    void listPassengers();

    static void removePassenger(int flightCode, string& astronautID);
    static void addPassenger(int flightCode, string& astronautID);
    static void listFlights();
    static map<int, Flight*> getFlights();
    static map<int, Flight*> filterFlightsByStatus(string& status);
};

#endif