#include "flight.h"


map<int, Flight*> Flight::flights;

Flight::Flight(int code, bool failed, bool planning, bool in_course, bool finished) : code(code), failed(failed), finished(finished), planning(planning), in_course(in_course){
    cout << "Cadastrado voo com código: " << this->getCode() << endl;
    flights.insert({this->getCode(), this});
}

int Flight::getCode()
{
    return code;
}

string Flight::getStatus()
{
    if (planning)
    {
        return "Planejamento";
    }
    else if (in_course)
    {
        return "Em curso";
    }
    else if(finished && !failed)
    {
        return "Finalizado com sucesso";
    }
    else if(finished && failed)
    {
        return "Finalizado com fracasso";
    }else
    {
        return "Status do voo desconhecido";
    }
    
}

map<string, Astronaut> Flight::getPassengers() {
    return passengers;
}

void Flight::listPassengers()
{
    if (passengers.empty())
    {
        cout << "Não há passageiros cadastrados para esse voo" << endl;
    }
    else
    {
        map<string, Astronaut>::iterator passenger;
        for (passenger = passengers.begin(); passenger != passengers.end(); ++passenger) {
            cout << "CPF: " << passenger->first << " - Nome: " << passenger->second.getName() << endl;
            passenger->second.listFlights();
    }
    }
}

void Flight::removePassenger(int flightCode, string& astronautID) {   
    auto it = flights.find(flightCode);

    if (it == flights.end()) {
        cout << "Voo com código " << flightCode << " não encontrado." << endl;
        return;
    }

    if (!Astronaut::isIdUsed(astronautID)) {
        cout << "Astronauta com CPF " << astronautID << " não encontrado." << endl;
        return;
    }

    Flight* selectedFlight = it->second;
    auto passengerIt = selectedFlight->passengers.find(astronautID);
    
    if (passengerIt == selectedFlight->passengers.end()) {
        cout << "Astronauta com CPF " << astronautID << " não encontrado no voo." << endl;
        return;
    }

    if (selectedFlight->getStatus() == "Planejamento") {
        cout << "Astronauta " << passengerIt->second.getName() << " removido do voo " << selectedFlight->getCode() << " com sucesso." << endl;
        selectedFlight->passengers.erase(passengerIt);
    } else {
        cout << "Não foi possível remover astronauta do voo, pois ele não está em planejamento." << endl;
    }
}

void Flight::addPassenger(int flightCode, string& astronautID) {
    auto it = flights.find(flightCode);

    if (it == flights.end()) {
        cout << "Voo com código " << flightCode << " não encontrado." << endl;
        return;
    }

    if (!Astronaut::isIdUsed(astronautID)) {
        cout << "Astronauta com CPF " << astronautID << " não encontrado." << endl;
        return;
    }

    Flight* selectedFlight = it->second;
    Astronaut* selectedAstronaut = nullptr;
    for (auto astronaut : Astronaut::getAstronauts()) {
        if (astronaut->getIdentity() == astronautID) {
            selectedAstronaut = astronaut;
            break;
        }
    }


    if (!selectedAstronaut) {
        cout << "Astronauta com CPF " << astronautID << " não encontrado." << endl;
        return;
    }

    if (selectedFlight->getStatus() == "Planejamento") {
        auto result = selectedFlight->passengers.insert({selectedAstronaut->getIdentity(), *selectedAstronaut});
        if (result.second) {
            cout << "Astronauta " << selectedAstronaut->getName() << " adicionado ao voo " << selectedFlight->getCode() << "." << endl;
        } else {
            cout << "Astronauta com CPF " << astronautID << " já está no voo." << endl;
        }
    } else {
        cout << "Não foi possível adicionar astronauta ao voo, pois ele não está em planejamento." << endl;
    }
}

map<int, Flight*> Flight::getFlights() {
    return flights;
}

map<int, Flight *> Flight::filterFlightsByStatus(string &status)
{
    map<int, Flight*> filteredFlights;
    for (auto& pair : flights) {
        Flight* flight = pair.second;
        if (flight->getStatus() == status) {
            filteredFlights.insert({flight->getCode(), flight});
        }
    }
    return filteredFlights;
}

void Flight::listFlights()
{
    if (flights.empty())
            {
                cout << "Não há voos cadastrados." << endl;            
            }
            else
            {
                map<int, Flight*>::iterator flight;
                cout << "Lista de todos os voos:" << endl;
                for (flight = flights.begin(); flight != flights.end(); flight++) {
                    cout << "CÓDIGO: " << flight->first << " - STATUS: " << flight->second->getStatus() << endl;
                    cout << "PASSAGEIROS: " << endl;
                    flight->second->listPassengers();
                }
            }
}
