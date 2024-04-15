#include "flight.h"

vector<Flight*> Flight::flights;

Flight::Flight(int code)
{
    this->code = code;
    this->status = "Planejado";
    cout << "Cadastrado voo com código: " << this->getCode() << endl;

    flights.push_back(this);
}

int Flight::getCode()
{
    return code;
}

string Flight::getStatus()
{
    return status;
}

void Flight::getPassengers()
{   
    if (passengers.size() == 0)
    {
        cout << "Não há passageiros cadastrados para esse voo" << endl;
    }
    else
    {
        for (Astronaut astronaut : passengers) {
            cout << "Nome: " << astronaut.getName() << " - CPF: " << astronaut.getIdentity() << endl;
    }
    }
    
    
}

void Flight::addPassenger(int flightCode, string astronautID)
{
    auto it = find_if(flights.begin(), flights.end(), [flightCode](Flight* flight) { return flight->getCode() == flightCode; });
    if (it == flights.end()) {
        cout << "Voo com código " << flightCode << " não encontrado." << endl;
        return;
    }

    // Verificar se existe um astronauta com o CPF informado
    if (!Astronaut::isIdUsed(astronautID)) {
        cout << "Astronauta com CPF " << astronautID << " não encontrado." << endl;
        return;
    }

    // Obter o voo e o astronauta correspondentes
    Flight* selectedFlight = *it;
    Astronaut* selectedAstronaut = nullptr;
    for (auto astronaut : Astronaut::getAstronauts()) {
        if (astronaut->getIdentity() == astronautID) {
            selectedAstronaut = astronaut;
            break;
        }
    }

    // Inserir o astronauta no vetor de passageiros do voo
    selectedFlight->passengers.push_back(*selectedAstronaut);

    cout << "Astronauta " << selectedAstronaut->getName() << " adicionado ao voo " << selectedFlight->getCode() << "." << endl;

}

void Flight::listFlights()
{
    if (flights.empty())
            {
                cout << "Não há voos cadastrados." << endl;            
            }
            else
            {
                cout << "Lista de todos os voos:" << endl;
                for (const auto& flight : flights) {
                    cout << "CÓDIGO: " << flight->getCode() << " - STATUS: " << flight->getStatus() << endl;
                    cout << "PASSAGEIROS: " << endl;
                    flight->getPassengers();
                }
            }
}
