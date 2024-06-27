#include <iostream>
#include <vector>
#include <list>

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
    list<Flight> flights;

    static list<Astronaut*> astronauts;

public:
    
    Astronaut(string id, string name, int age);
    
    string getIdentity();
    string getName();
    void listFlights();
    int getAge();
    void setIdentity(int newId);

    static list<Astronaut*> getAstronauts();
    static void listAstronauts();
    static bool isIdUsed(string rndID);
};

#endif