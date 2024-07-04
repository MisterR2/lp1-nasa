#include <iostream>
#include "astronaut.h"
#include <cstdlib>
#include "flight.h"

using std::cout;
using std::cin;

map<string, Astronaut*> Astronaut::astronauts;

Astronaut::Astronaut(string id, string name, int age)
{
    this->identity = id;
    this->name = name;
    this->age = age;
    this->alive = true;
    this->available = true;

    cout << "Astronauta cadastrado com sucesso!" << endl;

    astronauts[id] = this;
}

map<string, Astronaut *> Astronaut::getAstronauts()
{
    return astronauts;
}

void Astronaut::listAstronauts(int filter)
{
    if (astronauts.empty())
    {
        cout << "Não há astronautas cadastrados." << endl;
    }
    else
    {   
        switch (filter)
        {
        case 1:
            cout << "Lista de todos os astronautas:" << endl;
            for (auto &pair : astronauts)
            {
                Astronaut* astronaut = pair.second;
                cout << "NOME: " << astronaut->getName() << " - CPF: " << astronaut->getIdentity() << " - IDADE: " << astronaut->getAge() << " anos" << " - STATUS:  "<< astronaut->getStatus() << endl;
                astronaut->listFlights(astronaut->getIdentity());
            }
            break;
        case 2:
            cout << "Lista de todos os astronautas disponíveis:" << endl;
            for (auto &pair : astronauts)
            {   
                Astronaut* astronaut = pair.second;
                if (astronaut->getStatus() == "Disponível"){
                    cout << "NOME: " << astronaut->getName() << " - CPF: " << astronaut->getIdentity() << " - IDADE: " << astronaut->getAge() << " anos" << " - STATUS:  "<< astronaut->getStatus() << endl;
                    astronaut->listFlights(astronaut->getIdentity());
                }
                
            }
            break;
        case 3:
            cout << "Lista de todos os astronautas indisponíveis:" << endl;
            for (auto &pair : astronauts)
            {   
                Astronaut* astronaut = pair.second;
                if (astronaut->getStatus() == "Indisponível"){
                    cout << "NOME: " << astronaut->getName() << " - CPF: " << astronaut->getIdentity() << " - IDADE: " << astronaut->getAge() << " anos" << " - STATUS:  "<< astronaut->getStatus() << endl;
                    astronaut->listFlights(astronaut->getIdentity());
                }
                
            }
            break;
        case 4:
            cout << "Lista de todos os voos finalizados:" << endl;
            for (auto &pair : astronauts)
            {   
                Astronaut* astronaut = pair.second;
                if (astronaut->getStatus() == "Morto"){
                    cout << "NOME: " << astronaut->getName() << " - CPF: " << astronaut->getIdentity() << " - IDADE: " << astronaut->getAge() << " anos" << " - STATUS:  "<< astronaut->getStatus() << endl;
                    astronaut->listFlights(astronaut->getIdentity());
                }
                
            }
            break;
        default:
            cout << "Opção inválida!" << endl;
            break;
        }
        cout << "Lista de todos os astronautas:" << endl;
        
    }
}

void Astronaut::setIdentity(string newId)
{   
    if (astronauts.find(newId) == astronauts.end()) {
        astronauts.erase(this->identity);
        this->identity = newId;
        astronauts[newId] = this;
    } else {
        cout << "Erro: Novo ID já está em uso." << endl;
    }
}

void Astronaut::setAvailable(bool status)
{
    this->available = status;
}

void Astronaut::setAlive(bool status)
{
    this->alive = status;
}

void Astronaut::insertFlight(Flight* flight)
{
    this->flights.insert({flight->getCode(), *flight});
}

bool Astronaut::isIdUsed(string rndID)
{
    return astronauts.find(rndID) != astronauts.end();
}

string Astronaut::getIdentity(){
    return identity;
};

string Astronaut::getName(){
    return name;
}

string Astronaut::getStatus()
{
    if (available && alive)
    {
        return "Disponível";
    }
    else if (!available && alive)
    {
        return "Indisponível";
    }
    else if(!alive)
    {
        return "Morto";
    }else
    {
        return "Status Desconhecido";
    }
    
    
}

bool Astronaut::getAvailable()
{
    return available;
}

bool Astronaut::getAlive()
{
    return alive;
}

map<int, Flight> Astronaut::getFlights()
{
    return flights;
}

void Astronaut::listFlights(string identity) {
    auto it = astronauts.find(identity);

    if (it == astronauts.end())
    {
        cout << "Astronauta com cpf " << identity << " não encontrado." << endl;
        return;
    }

    Astronaut* selectedAstronaut = it->second;
    

    if (selectedAstronaut->getFlights().empty())
    {
        cout << "Esse astronauta não participou de voos." << endl;
        cout << endl;
    }
    else
    {
        std::cout << "Voos deste astronauta:" << std::endl;
        for (auto& flight : selectedAstronaut->getFlights()) {
            std::cout << "CÓDIGO: " << flight.first << std::endl;
            cout << endl;
        }
    }
    
    }


int Astronaut::getAge(){
    return age;
}
