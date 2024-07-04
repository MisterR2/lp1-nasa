#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <map>
#include "astronaut.h"

using namespace std;

class Flight
{
private:
    int code;
    map<string, Astronaut*> passengers;
    bool planning;
    bool in_course;
    bool finished;
    bool failed;

    static map<int, Flight*> flights;

public:
    Flight(int code, bool failed = false, bool planning = true, bool in_course = false, bool finished = false);

    int getCode();
    string getStatus();
    map<string, Astronaut*> getPassengers();

    void listPassengers();
    void setPlanning(bool status);
    void setInCourse(bool status);
    void setFinished(bool status);
    void setFailed(bool status);

    static void launchFlight(int flightCode);
    static void finishFlight(int flightCode);
    static void explodeFlight(int flightCode);
    static void removePassenger(int flightCode, const string &astronautID);
    static void addPassenger(int flightCode, const string& astronautID);
    static void listFlights(int filter = 1);
    static map<int, Flight*> getFlights();
    static map<int, Flight*> filterFlightsByStatus(const string& status);
};

#endif
