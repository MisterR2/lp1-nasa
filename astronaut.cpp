#include <iostream>
#include "astronaut.h"
#include <cstdlib>

using std::cout;
using std::cin;

vector<Astronaut*> Astronaut::astronauts;

Astronaut::Astronaut(string id, string name, int age)
{
    this->identity = id;
    this->name = name;
    this->age = age;

    cout << "Astronauta cadastrado com sucesso!" << endl;

    astronauts.push_back(this);

}

vector<Astronaut *> Astronaut::getAstronauts()
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
};

int Astronaut::getAge(){
    return age;
}
