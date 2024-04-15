#include <iostream>
#include <vector>
#include "astronaut.h"
#include <algorithm>

#ifndef FLIGHT_H
#define FLIGHT_H


using namespace std;

class Flight
{
private:
    int code;
    vector<Astronaut> passengers;
    string status;

    static vector<Flight*> flights;

public:
    Flight(int code);

    int getCode();
    string getStatus();
    void getPassengers();
    void createPassengers();
    
    static void addPassenger(int code, string id);
    static void listFlights();
};

#endif