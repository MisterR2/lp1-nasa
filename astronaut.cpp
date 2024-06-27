#include <iostream>
#include "astronaut.h"
#include <cstdlib>
#include "flight.h"

using std::cout;
using std::cin;

list<Astronaut*> Astronaut::astronauts;

Astronaut::Astronaut(string id, string name, int age)
{
    this->identity = id;
    this->name = name;
    this->age = age;
    this->alive = true;
    this->available = true;

    cout << "Astronauta cadastrado com sucesso!" << endl;

    astronauts.push_back(this);

}

list<Astronaut *> Astronaut::getAstronauts()
{
    return astronauts;
}

void Astronaut::listAstronauts()
{

    if (astronauts.empty())
    {
        cout << "Não há astronautas cadastrados." << endl;
    }
    else
    {
        cout << "Lista de todos os astronautas:" << endl;
        for (const auto &astronaut : astronauts)
        {
            cout << "NOME: " << astronaut->getName() << " - CPF: " << astronaut->getIdentity() << " - IDADE: " << astronaut->getAge() << " anos" << endl;
            astronaut->listFlights();
        }
    }
}

void Astronaut::setIdentity(int newId)
{   
    this->identity = newId;
}

bool Astronaut::isIdUsed(string rndID)
{
    for (const auto& astronaut : astronauts)
    {
        if (astronaut->getIdentity() == rndID)
        {
            return true;
        }
    }
    return false;
}

string Astronaut::getIdentity(){
    return identity;
};

string Astronaut::getName(){
    return name;
}

void Astronaut::listFlights(){
    bool foundFlights = false;
    
    for (auto& pair : Flight::getFlights()) {
        Flight* flight = pair.second;
        if (flight->getPassengers().find(this->getIdentity()) != flight->getPassengers().end()) {
            if (!foundFlights) {
                std::cout << "Voos deste astronauta:" << std::endl;
                foundFlights = true;
            }
            std::cout << "CÓDIGO: " << flight->getCode() << " - STATUS: " << flight->getStatus() << std::endl;
        }
    }

    if (!foundFlights) {
        cout << "Esse astronauta não participou de voos." << endl;
    }
}

int Astronaut::getAge(){
    return age;
}
