#include "flight.h"

map<int, Flight*> Flight::flights;

Flight::Flight(int code, bool failed, bool planning, bool in_course, bool finished)
    : code(code), failed(failed), planning(planning), in_course(in_course), finished(finished)
{
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
    else if (finished && !failed)
    {
        return "Finalizado com sucesso";
    }
    else if (finished && failed)
    {
        return "Finalizado com falha";
    }
    else
    {
        return "Status do voo desconhecido";
    }
}

map<string, Astronaut*> Flight::getPassengers()
{
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
        for (const auto& passenger : passengers)
        {
            cout << "CPF: " << passenger.first << " - Nome: " << passenger.second->getName() << " - Status: " << passenger.second->getStatus() << endl;
            passenger.second->listFlights(passenger.second->getIdentity());
        }
    }
}

void Flight::launchFlight(int flightCode)
{
    auto it = flights.find(flightCode);

    if (it == flights.end())
    {
        cout << "Voo com código " << flightCode << " não encontrado." << endl;
        return;
    }

    Flight* selectedFlight = it->second;
    if (selectedFlight->passengers.empty())
    {
        cout << "Não há passageiros cadastrados para esse voo" << endl;
        return;
    }

    bool allowed = true;
    for (auto& passenger : selectedFlight->passengers)
    {
        if (!passenger.second->getAvailable() || !passenger.second->getAlive())
        {
            allowed = false;
            break;
        }
    }

    if (allowed)
    {
        for (auto& passenger : selectedFlight->passengers)
        {
            passenger.second->setAvailable(false);
            passenger.second->insertFlight(selectedFlight);
        }
        selectedFlight->setPlanning(false);
        selectedFlight->setInCourse(true);
        cout << "Voo " << selectedFlight->getCode() << " lançado com sucesso!" << endl;
    }
    else
    {
        cout << "Não foi possível lançar pois há astronautas indisponíveis ou mortos." << endl;
    }
}

void Flight::finishFlight(int flightCode)
{
    auto it = flights.find(flightCode);

    if (it == flights.end())
    {
        cout << "Voo com código " << flightCode << " não encontrado." << endl;
        return;
    }

    Flight* selectedFlight = it->second;
    if (selectedFlight->getStatus() != "Em curso")
    {
        cout << "Esse voo não está em curso." << endl;
        return;
    }else
    {
        for (auto& passenger : selectedFlight->passengers)
        {
            passenger.second->setAvailable(true);
        }
        selectedFlight->setPlanning(false);
        selectedFlight->setInCourse(false);
        selectedFlight->setFinished(true);
        selectedFlight->setFailed(false);
        cout << "Voo " << selectedFlight->getCode() << " finalizado com sucesso!" << endl;
    }
    
    }

void Flight::explodeFlight(int flightCode)
{
    auto it = flights.find(flightCode);

    if (it == flights.end())
    {
        cout << "Voo com código " << flightCode << " não encontrado." << endl;
        return;
    }

    Flight* selectedFlight = it->second;
    
        for (auto& passenger : selectedFlight->passengers)
        {
            passenger.second->setAvailable(false);
            passenger.second->setAlive(false);
        }
        selectedFlight->setPlanning(false);
        selectedFlight->setInCourse(false);
        selectedFlight->setFinished(true);
        selectedFlight->setFailed(true);
        cout << "Voo " << selectedFlight->getCode() << " explodido com sucesso!" << endl;
    }
    

void Flight::setPlanning(bool status)
{
    this->planning = status;
}

void Flight::setInCourse(bool status)
{
    this->in_course = status;
}

void Flight::setFinished(bool status)
{
    this->finished = status;
}

void Flight::setFailed(bool status)
{
    this->failed = status;
}

void Flight::removePassenger(int flightCode, const string& astronautID)
{
    auto it = flights.find(flightCode);

    if (it == flights.end())
    {
        cout << "Voo com código " << flightCode << " não encontrado." << endl;
        return;
    }

    if (!Astronaut::isIdUsed(astronautID))
    {
        cout << "Astronauta com CPF " << astronautID << " não encontrado." << endl;
        return;
    }

    Flight* selectedFlight = it->second;
    auto passengerIt = selectedFlight->passengers.find(astronautID);

    if (passengerIt == selectedFlight->passengers.end())
    {
        cout << "Astronauta com CPF " << astronautID << " não encontrado no voo." << endl;
        return;
    }

    if (selectedFlight->getStatus() == "Planejamento")
    {
        cout << "Astronauta " << passengerIt->second->getName() << " removido do voo " << selectedFlight->getCode() << " com sucesso." << endl;
        selectedFlight->passengers.erase(passengerIt);
    }
    else
    {
        cout << "Não foi possível remover astronauta do voo, pois ele não está em planejamento." << endl;
    }
}

void Flight::addPassenger(int flightCode, const string& astronautID)
{
    auto it = flights.find(flightCode);

    if (it == flights.end())
    {
        cout << "Voo com código " << flightCode << " não encontrado." << endl;
        return;
    }

    if (!Astronaut::isIdUsed(astronautID))
    {
        cout << "Astronauta com CPF " << astronautID << " não encontrado." << endl;
        return;
    }

    Flight* selectedFlight = it->second;
    Astronaut* selectedAstronaut = nullptr;

    for (const auto& astronaut : Astronaut::getAstronauts())
    {
        if (astronaut.second->getIdentity() == astronautID)
        {
            selectedAstronaut = astronaut.second;
            break;
        }
    }

    if (!selectedAstronaut)
    {
        cout << "Astronauta com CPF " << astronautID << " não encontrado." << endl;
        return;
    }

    if (selectedFlight->getStatus() == "Planejamento")
    {
        auto result = selectedFlight->passengers.insert({selectedAstronaut->getIdentity(), selectedAstronaut});
        if (result.second)
        {
            cout << "Astronauta " << selectedAstronaut->getName() << " adicionado ao voo " << selectedFlight->getCode() << "." << endl;
        }
        else
        {
            cout << "Astronauta com CPF " << astronautID << " já está no voo." << endl;
        }
    }
    else
    {
        cout << "Não foi possível adicionar astronauta ao voo, pois ele não está em planejamento." << endl;
    }
}

map<int, Flight*> Flight::getFlights()
{
    return flights;
}

map<int, Flight*> Flight::filterFlightsByStatus(const string& status)
{
    map<int, Flight*> filteredFlights;
    for (const auto& pair : flights)
    {
        Flight* flight = pair.second;
        if (flight->getStatus() == status)
        {
            filteredFlights.insert({flight->getCode(), flight});
        }
    }
    return filteredFlights;
}

void Flight::listFlights(int filter)
{   
    if (flights.empty())
    {
        cout << "Não há voos cadastrados." << endl;
    }
    else
    {
        switch (filter)
        {
        case 1:
            cout << "Lista de todos os voos:" << endl;
            for (const auto& flight : flights)
            {   
                cout << "CÓDIGO: " << flight.first << " - STATUS: " << flight.second->getStatus() << endl;
                cout << "PASSAGEIROS: " << endl;
                flight.second->listPassengers();
                cout << endl;
            }
            break;
        case 2:
            cout << "Lista de todos os voos planejados:" << endl;
            for (const auto& flight : flights)
            {   
                if (flight.second->getStatus() == "Planejamento"){
                    cout << "CÓDIGO: " << flight.first << " - STATUS: " << flight.second->getStatus() << endl;
                    cout << "PASSAGEIROS: " << endl;
                    flight.second->listPassengers();
                    cout << endl;
                }
                
            }
            break;
        case 3:
            cout << "Lista de todos os voos em curso:" << endl;
            for (const auto& flight : flights)
            {   
                if (flight.second->getStatus() == "Em curso"){
                    cout << "CÓDIGO: " << flight.first << " - STATUS: " << flight.second->getStatus() << endl;
                    cout << "PASSAGEIROS: " << endl;
                    flight.second->listPassengers();
                    cout << endl;
                }
                
            }
            break;
        case 4:
            cout << "Lista de todos os voos finalizados:" << endl;
            for (const auto& flight : flights)
            {   
                if (flight.second->getStatus() == "Finalizado com sucesso" || flight.second->getStatus() == "Finalizado com falha"){
                    cout << "CÓDIGO: " << flight.first << " - STATUS: " << flight.second->getStatus() << endl;
                    cout << "PASSAGEIROS: " << endl;
                    flight.second->listPassengers();
                    cout << endl;
                }
            }
            break;
        default:
            cout << "Opção inválida!" << endl;
            break;
        }
        
    }
}
