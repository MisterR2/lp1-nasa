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

    static void listAstronauts();
    void setIdentity(int newId);
    static bool isIdUsed(string rndID);
};

#endif