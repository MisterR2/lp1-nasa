#include <iostream>
#include <vector>
#include "astronaut.h"

#ifndef FLIGHT_H
#define FLIGHT_H


using namespace std;

class Flight
{
private:
    int code;
    vector<Astronaut> passengers;

public:
    Flight(int code);

    int getCode();
    void getPassengers();
    void createPassengers();
};

#endif