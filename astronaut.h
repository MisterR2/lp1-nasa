#include <iostream>
#include <vector>
#include <map>

#ifndef ASTRONAUT_H
#define ASTRONAUT_H


using namespace std;

class Flight;

class Astronaut
{
private:
    string identity;
    string name;
    int age;
    bool available;
    bool alive;
    map<int, Flight> flights;

    static map<string, Astronaut*> astronauts;

public:
    Astronaut(string id, string name, int age);
    
    string getIdentity();
    string getName();
    bool getAvailable();
    bool getAlive();
    string getStatus();
    map<int, Flight> getFlights();

    void listFlights(string identity);
    int getAge();
    void setIdentity(string newId);
    void setAvailable(bool status);
    void setAlive(bool status);
    void insertFlight(Flight* flight);

    static map<string, Astronaut*> getAstronauts();
    static void listAstronauts(int filter = 1);
    static bool isIdUsed(string rndID);
};

#endif