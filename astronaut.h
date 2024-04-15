#include <iostream>
#include <vector>

#ifndef ASTRONAUT_H
#define ASTRONAUT_H


using namespace std;

class Astronaut
{
private:
    string identity;
    string name;
    int age;
    static vector<Astronaut*> astronauts;

public:
    
    Astronaut(string id, string name, int age);

    string getIdentity();
    string getName();
    int getAge();
    void setIdentity(int newId);

    static vector<Astronaut*> getAstronauts();
    static void listAstronauts();
    static bool isIdUsed(string rndID);
};

#endif